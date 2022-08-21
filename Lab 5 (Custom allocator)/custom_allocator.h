#include <cmath>
#include <vector>

#include "alloc_exception.h"

#pragma once

#define CAPACITY 130944
#define BLOCKS_AMOUNT 1280

template<typename T>
class Custom_allocator {
private:
    T*                              mem_given;
    const unsigned long long int    num_of_blocks = BLOCKS_AMOUNT,
                                    size = CAPACITY * sizeof(T);
    std::vector<std::pair<int,
    std::pair<int, bool>>>          mem_blocks;

public:
    typedef T                       value_type;
    typedef T*                      pointer;
    typedef T&                      reference;
    typedef const T*                const_pointer;
    typedef const T&                const_reference;
    typedef size_t                  size_type;

    Custom_allocator() {
        int offset = 0, cur_power = 0;
        mem_given = static_cast<pointer> (malloc(size));
        if (mem_given == nullptr) {
            throw Allocator_exception();
        }

        std::cout << std::endl << "Allocated " << size << " bytes at "
        << mem_given << "." << std::endl;

        const int quartet = num_of_blocks / 10, separation = num_of_blocks / 128;
        for (int i = 0; i < separation; ++i) {
            for (int j = 0; j < quartet; ++j) {
                mem_blocks.emplace_back(pow(2, cur_power), std::make_pair(offset, false));
            }

            ++cur_power;
        }

        for (int i = 1; i < num_of_blocks; ++i) {
            offset = mem_blocks[i - 1].second.first + mem_blocks[i].first;
            mem_blocks[i].second.first = offset;
        }
    }

    Custom_allocator(Custom_allocator& other) {
        mem_given = other.mem_given;
        mem_blocks = other.mem_blocks;
        num_of_blocks = other.num_of_blocks;
        size = other.size;
    }

    pointer allocate(size_type num_of_elements) {
        /* pointer result_unit = mem_given + (cur_unit * sizeof(value_type));
        cur_unit += num_of_elements;
        if (cur_unit > size) {
            throw Allocator_exception();
        }

        return result_unit; // Linear version */

        pointer result_unit = nullptr;
        for (int i = 0; i < num_of_blocks; ++i) {
            if (!(mem_blocks[i].second.second) && mem_blocks[i].first == num_of_elements) {
                result_unit = mem_given + mem_blocks[i].second.first;
                mem_blocks[i].second.second = true;
                return result_unit;
            }
        }

        throw Allocator_exception();
    }

    void deallocate(pointer begin, size_type num_of_elements) {
        /* if (cur_unit > 0 && cur_unit > num_of_elements) {
            cur_unit -= num_of_elements;
        } // Linear version */

        pointer result_unit = nullptr;
        for (int i = 0; i < num_of_blocks; ++i) {
            result_unit = mem_given + mem_blocks[i].second.first;
            if (begin == result_unit) {
                mem_blocks[i].second.second = false;
                return ;
            }
        }

        throw Allocator_exception();
    }

    ~Custom_allocator() {
        free(mem_given);
        std::cout << std::endl << "Successfully deallocated " << size << " bytes at "
        << mem_given << "." << std::endl;
    }
};