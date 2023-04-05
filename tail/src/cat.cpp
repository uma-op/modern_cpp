#include <fstream>
#include <iostream>

#include "cat.hpp"
#include "translate.hpp"

cat::cat(const std::string& filename) :
    _filename(filename),
    _next_op(new translate(std::cout.rdbuf())) {}

void cat::process_line(const std::string& str) {
    _next_op->process_line(str);
}

void cat::handle_end_of_input() {
    std::ifstream fs(_filename);
    std::string line;

    while (std::getline(fs, line))
        _next_op->process_line(line);
    
    _next_op->handle_end_of_input();
}

void cat::set_next_operation(operation_interface* op) {
    if (!op)
        return;
        
    _next_op = op;
}

