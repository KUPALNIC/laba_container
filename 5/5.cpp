#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <chrono>
#include <fstream>

template<typename Container, typename ValueType>
double measure_insert_time(size_t size) {
    Container container;
    for (size_t i = 0; i < size; ++i) {
        container.insert(ValueType(i));
    }

    auto start = std::chrono::high_resolution_clock::now();
    container.insert(ValueType(size));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count();
}

template<>
double measure_insert_time<std::map<int, int>, std::pair<const int, int>>(size_t size) {
    std::map<int, int> container;
    for (size_t i = 0; i < size; ++i) {
        container.insert(std::make_pair(i, i));
    }

    auto start = std::chrono::high_resolution_clock::now();
    container.insert(std::make_pair(size, size));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count();
}

template<>
double measure_insert_time<std::multimap<int, int>, std::pair<const int, int>>(size_t size) {
    std::multimap<int, int> container;
    for (size_t i = 0; i < size; ++i) {
        container.insert(std::make_pair(i, i));
    }

    auto start = std::chrono::high_resolution_clock::now();
    container.insert(std::make_pair(size, size));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count();
}

double average_insert_time(size_t size, const std::string& container_type) {
    double total_time = 0.0;
    const int iterations = 10;

    for (int i = 0; i < iterations; ++i) {
        if (container_type == "set") {
            total_time += measure_insert_time<std::set<int>, int>(size);
        } else if (container_type == "map") {
            total_time += measure_insert_time<std::map<int, int>, std::pair<const int, int>>(size);
        } else if (container_type == "multiset") {
            total_time += measure_insert_time<std::multiset<int>, int>(size);
        } else if (container_type == "multimap") {
            total_time += measure_insert_time<std::multimap<int, int>, std::pair<const int, int>>(size);
        }
    }

    return total_time / iterations;
}

int main() {
    std::vector<size_t> sizes;
    for (size_t size = 100; size <= 50000; size += 1000) {
        sizes.push_back(size);
    }

    std::ofstream outfile("/home/kupalnic/CLionProjects/laba_container/5/insert_times.txt");

    for (size_t size : sizes) {
        double avg_set_time = average_insert_time(size, "set");
        double avg_map_time = average_insert_time(size, "map");
        double avg_multiset_time = average_insert_time(size, "multiset");
        double avg_multimap_time = average_insert_time(size, "multimap");

        std::cout << "Size: " << size << " | set: " << avg_set_time << " us | map: " << avg_map_time << " us | multiset: " << avg_multiset_time << " us | multimap: " << avg_multimap_time << " us" << std::endl;

        outfile << size << " " << avg_set_time << " " << avg_map_time << " " << avg_multiset_time << " " << avg_multimap_time << "\n";
    }

    outfile.close();
    return 0;
}