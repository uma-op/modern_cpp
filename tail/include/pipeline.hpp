#pragma once

#include <string>

#include "operation_interface.hpp"

class pipeline {
public:

    explicit pipeline();
    explicit pipeline(const std::string& str);

    void add_operation(operation_interface::opptr_t op);
    void start_processing();

private:
    operation_interface::opptr_t _begin;
    operation_interface* _end;

};

