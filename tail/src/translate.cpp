#include <string>

#include "translate.hpp"

translate::translate(std::basic_streambuf<char>* buf) : 
    _out(buf) {}

void translate::process_line(const std::string& str) {
    _out << str << '\n';
}

void translate::handle_end_of_input() {
    _out.flush();
}

void translate::set_next_operation(operation_interface* op) {}

