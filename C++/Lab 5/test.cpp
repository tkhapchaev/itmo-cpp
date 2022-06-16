#include <iostream>

#include <chrono>
#include <list>
#include <set>

#include "custom_allocator.h"

#pragma once

void test_vector() {
    try {
        std::cout << std::endl << "(!) Testing custom allocator with vector:" << std::endl;
        std::vector<int, Custom_allocator<int>> example_vector;
        example_vector.resize(256);

        for (int i = 0; i <= 256; ++i) {
            example_vector[i] = i;
        }

        for (int i = 257; i <= 270; ++i) {
            example_vector.push_back(i);
        }

        for (auto &j: example_vector) {
            std::cout << j << " ";
        }
    }

    catch (Allocator_exception&) {
        std::cout << "Oops... Something went wrong!" << std::endl;
    }
}

void test_vector_std() {
    std::vector<int> example_vector;
    example_vector.resize(256);

    for (int i = 0; i <= 256; ++i) {
        example_vector[i] = i;
    }

    for (int i = 257; i <= 270; ++i) {
        example_vector.push_back(i);
    }
}

void test_list() {
    try {
        std::cout << std::endl << "(!) Testing custom allocator with list:" << std::endl;
        std::list<int, Custom_allocator<int>> example_list;

        for (int i = 0; i <= 64; ++i) {
            example_list.push_back(i);
        }

        for (auto& j: example_list) {
            std::cout << j << " ";
        }
    }

    catch (Allocator_exception&) {
        std::cout << "Oops... Something went wrong!" << std::endl;
    }
}

void test_list_std() {
    std::list<int> example_list;

    for (int i = 0; i <= 64; ++i) {
        example_list.push_back(i);
    }
}

void test_set() {
    try {
        std::cout << std::endl << "(!) Testing custom allocator with set:" << std::endl;
        std::set<double, std::greater<>, Custom_allocator<double>> example_set;

        for (int i = 0; i <= 10; ++i) {
            double value = static_cast<double> (i) / 10;
            example_set.insert(value);
        }

        for (auto& j: example_set) {
            std::cout << j << "  ";
        }
    }

    catch (Allocator_exception&) {
        std::cout << "Oops... Something went wrong!" << std::endl;
    }
}

void test_set_std() {
    std::set<double, std::greater<>> example_set;

    for (int i = 0; i <= 10; ++i) {
        double value = static_cast<double> (i) / 10;
        example_set.insert(value);
    }
}

void start_testing() {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    test_vector();
    auto end = high_resolution_clock::now();
    auto duration_custom = duration_cast<milliseconds> (end - start).count();

    start = high_resolution_clock::now();
    test_vector_std();
    end = high_resolution_clock::now();
    auto duration_std = duration_cast<milliseconds> (end - start).count();

    if (duration_std == 0) {
        ++duration_std;
    }

    std::cout << "Using custom allocator: " << duration_custom << " ms, using standard allocator: "
    << duration_std << " ms." << std::endl;

    start = high_resolution_clock::now();
    test_list();
    end = high_resolution_clock::now();
    duration_custom = duration_cast<milliseconds> (end - start).count();

    start = high_resolution_clock::now();
    test_list_std();
    end = high_resolution_clock::now();
    duration_std = duration_cast<milliseconds> (end - start).count();

    if (duration_std == 0) {
        ++duration_std;
    }

    std::cout << "Using custom allocator: " << duration_custom << " ms, using standard allocator: "
    << duration_std << " ms." << std::endl;

    start = high_resolution_clock::now();
    test_set();
    end = high_resolution_clock::now();
    duration_custom = duration_cast<milliseconds> (end - start).count();

    start = high_resolution_clock::now();
    test_set_std();
    end = high_resolution_clock::now();
    duration_std = duration_cast<milliseconds> (end - start).count();

    if (duration_std == 0) {
        ++duration_std;
    }

    std::cout << "Using custom allocator: " << duration_custom << " ms, using standard allocator: "
    << duration_std << " ms." << std::endl;
}