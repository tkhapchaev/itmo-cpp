#include <iostream>
#include <iterator>

#pragma once

template <typename T>
    class Circular_buffer {
    private:
        T * data;
        size_t size;
        size_t capacity;
        unsigned int head;
        unsigned int tail;

        class Iterator: public std::iterator < std::random_access_iterator_tag, T > {
            private: 
                T * current_object;

            public: 
                Iterator(T * begin) {
                    current_object = begin;
                };

                Iterator(const Iterator & other) {
                    current_object = other.current_object;
                };

                T & operator * () {
                    return *current_object;
                };

                T & operator++(int) {
                    return *current_object++;
                };

                T & operator--(int) {
                    return *current_object--;
                };

                T & operator++() {
                    return *++current_object;
                };

                T & operator--() {
                    return *--current_object;
                };

                T & operator + (int value) {
                    return *(current_object + value);
                };

                T & operator - (int value) {
                    return *(current_object - value);
                };

                bool operator == (const Iterator & other) {
                    return current_object == other.current_object;
                };

                bool operator != (const Iterator & other) {
                    return current_object != other.current_object;
                };

                bool operator > (const Iterator & other) {
                    return current_object > other.current_object;
                };

                bool operator < (const Iterator & other) {
                    return current_object < other.current_object;
                };

                bool operator >= (const Iterator & other) {
                    return current_object >= other.current_object;
                };

                bool operator <= (const Iterator & other) {
                    return current_object <= other.current_object;
                };
        };

    public:
        Circular_buffer(const unsigned int & capacity_input) {
            capacity = capacity_input;
            data = new T[capacity];
            size = 0;
            head = 0;
            tail = 0;
        }

        Circular_buffer(const Circular_buffer & other) {
            capacity = other.capacity;
            data = other.data;
            size = other.size;
            head = other.head;
            tail = other.tail;
        }

        Iterator begin() {
            return data;
        };

        Iterator end() {
            return data + size;
        };

        void reserve(const unsigned int & new_capacity) {
            if (new_capacity != capacity) {
                capacity = new_capacity;
                delete[] data;
                data = new T[new_capacity];
                size = 0;
                head = 0;
                tail = 0;
            }
        }

        T operator[](const unsigned int & index) {
            return data[index % size];
        }

        void insert(const unsigned int & index, T & object) {
            if (index < size && data[index] != object) data[index] = object;
        }

        void erase(const unsigned int & index) {
            if (index < size) data[index] = T();
        }

        void push_back(const T & object) {
            if (size <= capacity) {
                if (size != capacity) ++size;
                data[tail] = object;
                tail = (tail + 1) % capacity;
            }
        }

        void push_front(const T & object) {
            if (size <= capacity) {
                if (size != capacity) ++size;
                if (head == 0) {
                    head = capacity - 1;
                    size = capacity;
                } else head = (head - 1) % capacity;
                data[head] = object;
            }
        }

        void pop_back() {
            if (size != 0) {
                if (tail == 0) {
                    tail = capacity - 1;
                    data[tail] = T();
                } else {
                    tail = (tail - 1) % capacity;
                    data[tail] = T();
                }

                --size;
            }
        }

        void pop_front() {
            if (size != 0) {
                data[head] = T();
                head = (head + 1) % capacity;
                --size;
            }
        }

        T & front() {
            return data[head];
        }

        T & back() {
            if (tail == 0) {
                return data[capacity - 1];
            } else return data[tail - 1];
        }

        bool empty() {
            if (size == 0) return true;
            else return false;
        }

        size_t & get_size() {
            return size;
        }

        size_t & get_capacity() {
            return capacity;
        }

        void print() {
            for (auto i = this -> begin(); i != data + capacity; ++i) {
                std::cout << ( * i) << " ";
            }

            std::cout << std::endl;
        }

        void print_orderly() {
            int i = head, j = -1, k = 0, counter = 0;
            if (head > tail) {
                counter = tail + (capacity - head);
            } else if (head < tail) {
                counter = tail - head;
            } else if (head == tail) counter = 0;

            while (k < counter) {
                if (i >= capacity) {
                    ++j;
                    std::cout << * (data + j) << " ";
                } else std::cout << * (data + i) << " ";
                
                ++i;
                ++k;
            }

            std::cout << std::endl;
        }

        ~Circular_buffer() { delete[] data; };
    };
