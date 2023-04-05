#pragma once

#include <memory>
#include <string>
#include <vector>

#include "operation_interface.hpp"

class echo: public operation_interface {
public:
    explicit echo(const std::string& str);

    void process_line(const std::string& str) override;
    void handle_end_of_input() override;
    void set_next_operation(operation_interface* op) override;

private:
    std::string _str;
    operation_interface* _next_op;

};

