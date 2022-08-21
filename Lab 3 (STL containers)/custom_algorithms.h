#include <vector>
#include <iostream>
#include <algorithm>

#pragma once

namespace custom_algorithms {
    template<typename T, typename Iterator>
    bool all_of(Iterator begin, Iterator end, T predicate) {
        for (auto i = begin; i != end; ++i) {
            if (!predicate(*i)) return false;
        }

        return true;
    }

    template<typename T, typename Iterator>
    bool any_of(Iterator begin, Iterator end, T predicate) {
        for (auto i = begin; i != end; ++i) {
            if (predicate(*i)) return true;
        }

        return false;
    }

    template<typename T, typename Iterator>
    bool none_of(Iterator begin, Iterator end, T predicate) {
        for (auto i = begin; i != end; ++i) {
            if (predicate(*i)) return false;
        }

        return true;
    }

    template<typename T, typename Iterator>
    bool one_of(Iterator begin, Iterator end, T predicate) {
        int counter = 0;
        for (auto i = begin; i != end; ++i) {
            if (predicate(*i)) ++counter;
        }

        if (counter == 1) return true;
        else return false;
    }

    template<typename T, typename Iterator>
    bool is_sorted(Iterator begin, Iterator end, T predicate) {
        auto i = begin, j = begin; ++j;
        while (j != end) {
            if (!predicate(*i, *j)) return false;
            ++i;
            ++j;
        }

        return true;
    }

    template<typename T, typename Iterator>
    bool is_partitioned(Iterator begin, Iterator end, T predicate) {
        int index_1 = -1, index_2 = -1;
        for (auto i = begin; i != end; ++i) {
            ++index_1;
            if (!predicate(*i)) break;
        }

        for (auto i = begin; i != end; ++i) {
            ++index_2;
            if (index_2 >= index_1) {
                if (predicate(*i)) return false;
            }
        }

        return true;
    }

    template<typename T, typename Iterator>
    Iterator find_not(Iterator begin, Iterator end, T value) {
        for (auto i = begin; i != end; ++i) {
            if ((*i) != value) return i;
        }

        return end;
    }

    template<typename T, typename Iterator>
    Iterator find_backward(Iterator begin, Iterator end, T value) {
        for (auto i = end; i != begin; --i) {
            if ((*i) == value) return i;
        }

        return end;
    }

    template<typename T, typename Iterator>
    bool is_palindrome_unary(Iterator begin, Iterator end, T predicate) {
        std::vector<bool> status_regular, status_buffer, status_inverted;
        for (auto i = begin; i != end; ++i) {
            status_regular.push_back(predicate(*i));
        }

        status_buffer = status_regular;
        std::reverse(status_buffer.begin(), status_buffer.end());
        status_inverted = status_buffer;
        if (status_regular == status_inverted) return true;
        else return false;
    }

    template<typename T, typename Iterator>
    bool is_palindrome_binary(Iterator begin, Iterator end, T predicate) {
        --end;
        while (begin != end) {
            if (!predicate(*begin, *end)) return false;
            ++begin;
            --end;
        }

        return true;
    }

    template<typename T>
    bool greater(T value_1, T value_2) {
        return value_1 < value_2;
    }

    template<typename T>
    bool less(T value_1, T value_2) {
        return value_1 > value_2;
    }

    template<typename T>
    bool is_equal(T value_1, T value_2) {
        return value_1 == value_2;
    }

    template<typename T>
    bool is_zero(T value) {
        return value == 0;
    }

    template<typename T>
    bool is_even(T value) {
        if (value % 2 == 0) return true;
        else return false;
    }
}
