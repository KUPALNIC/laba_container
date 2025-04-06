#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <type_traits>

// Генератор случайных чисел
template<typename T>
T generate_random() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 1000000);
    return static_cast<T>(dis(gen));
}

// Специализация для пар (map)
template<typename Container>
typename std::enable_if<std::is_same<Container, std::map<int, int>>::value,
                       typename Container::value_type>::type
generate_element() {
    return std::make_pair(generate_random<int>(), generate_random<int>());
}

// Специализация для остальных контейнеров
template<typename Container>
typename std::enable_if<!std::is_same<Container, std::map<int, int>>::value,
                       typename Container::value_type>::type
generate_element() {
    return generate_random<typename Container::value_type>();
}

// Заполнение forward_list
template<typename T>
void fill_container_impl(std::forward_list<T>& container, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        container.push_front(generate_element<std::forward_list<T>>());
    }
}

// Заполнение vector и list
template<typename Container>
typename std::enable_if<std::is_same<Container, std::vector<int>>::value ||
                       std::is_same<Container, std::list<int>>::value>::type
fill_container_impl(Container& container, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        container.push_back(generate_element<Container>());
    }
}

// Заполнение set
template<typename T>
void fill_container_impl(std::set<T>& container, size_t size) {
    while (container.size() < size) {
        container.insert(generate_element<std::set<T>>());
    }
}

// Заполнение map
template<typename K, typename V>
void fill_container_impl(std::map<K, V>& container, size_t size) {
    while (container.size() < size) {
        container.insert(generate_element<std::map<K, V>>());
    }
}

template<typename Container>
void fill_container(Container& container, size_t size) {
    fill_container_impl(container, size);
}

// Обработчик для map
template<typename Container>
typename std::enable_if<std::is_same<Container, std::map<int, int>>::value>::type
process_element(typename Container::iterator& it) {
    it->second += 1;
}

// Обработчик для set
template<typename Container>
typename std::enable_if<std::is_same<Container, std::set<int>>::value>::type
process_element(typename Container::iterator& it) {
    volatile auto temp = *it;
    (void)temp;
}

// Обработчик для остальных контейнеров
template<typename Container>
typename std::enable_if<!std::is_same<Container, std::map<int, int>>::value &&
                       !std::is_same<Container, std::set<int>>::value>::type
process_element(typename Container::iterator& it) {
    *it += 1;
}

// Получение размера контейнера
template<typename Container>
typename std::enable_if<!std::is_same<Container, std::forward_list<int>>::value, size_t>::type
get_container_size(const Container& container) {
    return container.size();
}

template<typename Container>
typename std::enable_if<std::is_same<Container, std::forward_list<int>>::value, size_t>::type
get_container_size(const Container& container) {
    return std::distance(container.begin(), container.end());
}

template<typename Container>
double measure_traversal(Container& container, int iterations = 5) {
    double total_time = 0;

    for (int iter = 0; iter < iterations; ++iter) {
        auto start = std::chrono::high_resolution_clock::now();

        for (auto it = container.begin(); it != container.end(); ++it) {
            process_element<Container>(it);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        total_time += diff.count();
    }

    return (total_time / iterations) / get_container_size(container);
}

template<typename Container>
void benchmark_container(const std::string& name, const std::vector<size_t>& sizes, std::ofstream& outFile) {
    outFile << name << "\n";
    outFile << "size,time_ns\n";

    for (size_t size : sizes) {
        Container container;
        fill_container(container, size);

        double avg_time = measure_traversal(container) * 1e9; // Конвертация в наносекунды
        outFile << size << "," << std::fixed << std::setprecision(2) << avg_time << "\n";
    }
    outFile << "\n"; // Пустая строка между контейнерами
}

int main() {
    // Создаем вектор размеров от 1000 до 50000 с шагом 1000
    std::vector<size_t> sizes;
    for (size_t size = 10000; size <= 500000; size += 10000) {
        sizes.push_back(size);
    }

    std::ofstream outFile("6.txt");

    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        return 1;
    }

    benchmark_container<std::vector<int>>("vector", sizes, outFile);
    benchmark_container<std::forward_list<int>>("forward_list", sizes, outFile);
    benchmark_container<std::list<int>>("list", sizes, outFile);
    benchmark_container<std::map<int, int>>("map", sizes, outFile);
    benchmark_container<std::set<int>>("set", sizes, outFile);

    outFile.close();
    return 0;
}