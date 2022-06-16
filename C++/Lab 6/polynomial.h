#include <iostream>
#include <array>

//#include <cmath>

#pragma once

struct Polynomial {
private:
    static constexpr std::array<std::pair<const int, const int>, 4> coefficients = {
            std::make_pair(4, 3),
            std::make_pair(3, 2),
            std::make_pair(2, 1),
            std::make_pair(1, 0)
    };

public:
    inline static constexpr int value(const int point);

    inline friend std::ostream &operator<<(std::ostream &stream, const Polynomial &output);
};
