#pragma once

struct Allocator_exception : public std::bad_alloc {
public:
    explicit Allocator_exception() = default;

    Allocator_exception(Allocator_exception& other) = default;

    ~Allocator_exception() override = default;
};