#pragma once

#include <memory>
#include <vector>

#include "operation_interface.hpp"

class tail: public operation_interface {
public:
    explicit tail(size_t n);

    ~tail();

    void process_line(const std::string& str) override;
    void handle_end_of_input() override;
    void set_next_operation(opptr_t op) override;

private:
    class cyclic_buffer {
    public:
        explicit cyclic_buffer(size_t capacity);

        std::string read();
        void write(const std::string& str);

        bool empty();
        bool full();

    private:
        std::vector<std::string> _buf;
        size_t _cap, _size;
        size_t _wid, _rid;

    };

    cyclic_buffer _buf;
    opptr_t _next_op;
    
};

