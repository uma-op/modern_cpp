#pragma once

#include <ostream>
#include <string>

#include "operation_interface.hpp"

class translate: public operation_interface {
public:
    explicit translate(std::basic_streambuf<char>* buf);

    ~translate();

    void process_line(const std::string& str) override;
    void handle_end_of_input() override;
    void set_next_operation(opptr_t op) override; 

private:
    std::ostream _out;

};

