#include <iostream>
#include <list>
#include <forward_list>
#include <chrono>
#include <fstream>
#include <vector>
#include "/home/kupalnic/CLionProjects/laba_container/subforwardlist.h"

template<typename Container>
double measure_pop_front_time(size_t size) {
    Container container;
    for (size_t i = 0; i < size; ++i) {
        container.push_front(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        container.pop_front();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    return duration.count() / size;
}

double average_pop_front_time(size_t size, bool use_std_list, bool use_forward_list) {
    double total_time = 0.0;
    const int iterations = 10;

    for (int i = 0; i < iterations; ++i) {
        if (use_std_list) {
            total_time += measure_pop_front_time<std::list<int>>(size);
        } else if (use_forward_list) {
            total_time += measure_pop_front_time<std::forward_list<int>>(size);
        } else {
            total_time += measure_pop_front_time<Subforwardlist>(size);
        }
    }

    return total_time / iterations;
}

int main() {
    std::vector<size_t> sizes;
    for (size_t size = 10000; size <= 1000000; size += 10000) {
        sizes.push_back(size);
    }

    std::ofstream outfile("4.txt");

    for (size_t size : sizes) {
        double avg_std_list_time = average_pop_front_time(size, true, false);
        double avg_forward_list_time = average_pop_front_time(size, false, true);
        double avg_subforwardlist_time = average_pop_front_time(size, false, false);
        
        outfile << size << " " << avg_std_list_time << " " << avg_forward_list_time << " " << avg_subforwardlist_time << "\n";
    }

    outfile.close();

    return 0;
}