#include "polynomial.cpp"

int main() {
    Polynomial example;
    std::cout << example << std::endl;
    const int X = 3;
    std::cout << "Polynomial value in point " << X << ": " << example.value(X) << "." << std::endl;
}
