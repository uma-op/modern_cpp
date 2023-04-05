#pragma once

#include <string>

class operation_interface {
public:
    virtual void process_line(const std::string& str) = 0;
    virtual void handle_end_of_input() = 0;
    virtual void set_next_operation(operation_interface* op) = 0;

};

