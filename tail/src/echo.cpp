#include <iostream>
#include <string>

#include "echo.hpp"
#include "translate.hpp"

echo::echo(const std::string& str) :
    _str(str),
    _next_op(new translate(std::cout.rdbuf())) {}

void echo::process_line(const std::string& str) {}

void echo::handle_end_of_input() {
    _next_op->process_line(_str);
    _next_op->handle_end_of_input();
}

void echo::set_next_operation(operation_interface* op) {
    if (!op)
        return;

    _next_op = op;
}

