#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "/home/kupalnic/CLionProjects/laba_container/sv.h"

template<typename Container>
double measure_erase_time(size_t size) {
    Container container;
    for (size_t i = 0; i < size; ++i) {
        container.push_back(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    container.erase(container.begin() + size / 2);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count();
}

double average_erase_time(size_t size, bool use_std_vector) {
    double total_time = 0.0;
    const int iterations = 10;

    for (int i = 0; i < iterations; ++i) {
        if (use_std_vector) {
            total_time += measure_erase_time<std::vector<int>>(size);
        } else {
            total_time += measure_erase_time<subvector>(size);
        }
    }

    return total_time / iterations;
}

int main() {
    std::vector<size_t> sizes;
    for (size_t size = 10000; size <= 1000000; size += 10000) {
        sizes.push_back(size);
    }

    std::ofstream outfile("2.txt");

    for (size_t size : sizes) {
        double avg_std_vector_time = average_erase_time(size, true);
        double avg_sub_vector_time = average_erase_time(size, false);

        outfile << size << " " << avg_std_vector_time << " " << avg_sub_vector_time << "\n";
    }

    outfile.close();

    return 0;
}