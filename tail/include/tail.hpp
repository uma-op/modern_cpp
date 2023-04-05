#pragma once

#include <memory>
#include <vector>

#include "operation_interface.hpp"

class tail: public operation_interface {
public:
    using buffer_t = std::unique_ptr<std::vector<std::string>>;

    void process_line(const std::string& str) override;
    void handle_end_of_input() override;
    void set_next_operation(operation_interface* op) override;

private:
    buffer_t _buf;
    operation_interface* _next_op;
    
};

