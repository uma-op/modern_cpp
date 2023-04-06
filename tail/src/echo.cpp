#include <iostream>
#include <string>
#include <utility>

#include "echo.hpp"
#include "translate.hpp"

echo::echo() :
    _str(""),
    _next_op(std::make_unique<translate>(std::cout.rdbuf())) {}

echo::echo(const std::string& str) :
    echo() {
    _str.assign(str);
}

echo::~echo() {}

void echo::process_line(const std::string& str) {}

void echo::handle_end_of_input() {
    _next_op->process_line(_str);
    _next_op->handle_end_of_input();
}

void echo::set_next_operation(opptr_t op) {
    if (!op)
        return;

    _next_op = std::move(op);
}

