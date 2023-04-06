#pragma once

#include <memory>
#include <string>
#include <vector>

#include "operation_interface.hpp"

class echo: public operation_interface {
public:
    explicit echo();
    explicit echo(const std::string& str);

    ~echo();

    void process_line(const std::string& str) override;
    void handle_end_of_input() override;
    void set_next_operation(opptr_t op) override;

private:
    std::string _str;
    opptr_t _next_op;

};

