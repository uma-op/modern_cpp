#pragma once

#include <memory>
#include <string>

class operation_interface {
public:
    using opptr_t = std::unique_ptr<operation_interface>;

    virtual ~operation_interface() = 0;

    virtual void process_line(const std::string& str) = 0;
    virtual void handle_end_of_input() = 0;
    virtual void set_next_operation(opptr_t op) = 0;

};

