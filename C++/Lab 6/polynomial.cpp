#include "polynomial.h"

#pragma once

inline constexpr int Polynomial::value(const int point) {
    int result = 0, exponentiation = 1;
    for (auto &cur_pair : coefficients) {
        for (int i = 0; i < cur_pair.second; ++i) {
            exponentiation *= point;
        }

        result += cur_pair.first * exponentiation;
        exponentiation = 1;

        //result += cur_pair.first * pow(point, cur_pair.second);
    }

    return result;
};

inline std::ostream& operator<<(std::ostream& stream, const Polynomial& output) {
    int i = 0;
    for (auto &cur_pair : output.coefficients) {
        if (cur_pair.first != 0 && cur_pair.second != 0) {
            if (cur_pair.first > 0 && i > 0) {
                stream << " + " << cur_pair.first << "x^" << "(" << cur_pair.second << ")";
            }

            if (cur_pair.first < 0 && i > 0) {
                stream << " - " << abs(cur_pair.first) << "x^" << "(" << cur_pair.second << ")";
            }

            if (cur_pair.first > 0 && i == 0) {
                stream << cur_pair.first << "x^" << "(" << cur_pair.second << ")";
            }

            if (cur_pair.first < 0 && i == 0) {
                stream << "- " << abs(cur_pair.first) << "x^" << "(" << cur_pair.second << ")";
            }
        }

        if (cur_pair.first != 0 && cur_pair.second == 0) {
            if (cur_pair.first > 0 && i > 0) {
                stream << " + " << cur_pair.first;
            }

            if (cur_pair.first < 0 && i > 0) {
                stream << " - " << abs(cur_pair.first);
            }

            if (cur_pair.first > 0 && i == 0) {
                stream << cur_pair.first;
            }

            if (cur_pair.first < 0 && i == 0) {
                stream << "- " << abs(cur_pair.first);
            }
        }

        ++i;
    }

    return stream;
}
