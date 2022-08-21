#include "custom_algorithms.h"
#include "circular_buffer.h"
#include <iostream>

int main() {
    using namespace custom_algorithms;

    Circular_buffer<int> example(4);
    example.push_back(2);
    example.push_front(1);
    std::cout << std::endl;
    example.print();
    std::cout << "Current ring buffer size: " << example.get_size() << std::endl;
    std::cout << "\"Head\" element: " << example.front() << ", \"tail\" element: " << example.back() << std::endl;
    example.print_orderly();
    std::cout << std::endl;

    Circular_buffer<int> example_2(7);
    example_2.push_back(11);
    example_2.push_back(12);
    example_2.push_back(13);
    example_2.push_back(14);
    example_2.push_back(15);
    example_2.push_back(16);
    example_2.push_back(17);
    example_2.push_back(5);
    example_2.push_back(6);
    example_2.push_back(7);
    example_2.push_back(11);
    example_2.print();
    std::cout << "Current ring buffer size: " << example_2.get_size() << std::endl;
    std::cout << "\"Head\" element: " << example_2.front() << ", \"tail\" element: " << example_2.back() << std::endl;
    example_2.print_orderly(); std::cout << std::endl;

    std::cout << "\"One of\": " << custom_algorithms::one_of(example_2.begin(), example_2.end(), is_zero<int>) << std::endl;
    std::cout << "\"Any of\": " << custom_algorithms::any_of(example_2.begin(), example_2.end(), is_even<int>) << std::endl;
    std::cout << "\"None of\": " << custom_algorithms::none_of(example_2.begin(), example_2.end(), is_zero<int>) << std::endl;
    std::cout << "\"Is sorted\": " << custom_algorithms::is_sorted(example_2.begin(), example_2.end(), greater<int>) << std::endl;
    std::cout << "\"Is partitioned\": " << custom_algorithms::is_partitioned(example_2.begin(), example_2.end(), is_even<int>) << std::endl;
    std::cout << "\"Is palindrome\": " << custom_algorithms::is_palindrome_binary(example_2.begin(), example_2.end(), greater<int>) << std::endl << std::endl;

    example_2.pop_back();
    example_2.pop_back();
    example_2.print();
    std::cout << "Current ring buffer size: " << example_2.get_size() << std::endl;
    std::cout << "\"Head\" element: " << example_2.front() << ", \"tail\" element: " << example_2.back() << std::endl;
    example_2.print_orderly();

    std::vector<int> example_3 = {2, 3, 4, 5, 4, 3, 2};
    std::cout << std::endl;
    for(auto &i: example_3) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "\"One of\": " << custom_algorithms::one_of(example_3.begin(), example_3.end(), is_even<int>) << std::endl;
    std::cout << "\"Find backward\": " << *custom_algorithms::find_backward(example_3.begin(), example_3.end(), 4) << std::endl;
    std::cout << "\"All of\": " << custom_algorithms::none_of(example_3.begin(), example_3.end(), is_zero<int>) << std::endl;
    std::cout << "\"Is sorted\": " << custom_algorithms::is_sorted(example_3.begin(), example_3.end(), greater<int>) << std::endl;
    std::cout << "\"Is palindrome\": " << custom_algorithms::is_palindrome_binary(example_3.begin(), example_3.end(), is_equal<int>) << std::endl;
}
