#include <iostream>
#include <string>

#include "tail.hpp"
#include "translate.hpp"

tail::cyclic_buffer::cyclic_buffer(size_t capacity) :
    _buf(capacity),
    _cap(capacity),
    _size(0),
    _wid(0),
    _rid(0) {}

std::string tail::cyclic_buffer::read() {
    if (empty())
        return std::string(nullptr);

    std::string str = _buf[_rid++];
    _rid = (_rid == _cap ? 0 : _rid);
    _size--;

    return str;
}

void tail::cyclic_buffer::write(const std::string& str) {
    _buf[_wid++] = str;
    _wid = (_wid == _cap ? 0 : _wid);
    _size++;

    if (full()) {
        _rid = _wid;
        _size = _cap;
    }
}

bool tail::cyclic_buffer::empty() {
    return _size == 0;
}

bool tail::cyclic_buffer::full() {
    return _size >= _cap;
}

tail::tail(size_t n) :
    _buf(n),
    _next_op(new translate(std::cout.rdbuf())) {}

void tail::process_line(const std::string& str) {
    _buf.write(str);
}

void tail::handle_end_of_input() {
    while (!_buf.empty())
        _next_op->process_line(_buf.read());
    
    _next_op->handle_end_of_input();
}

void tail::set_next_operation(operation_interface* op) {
    if (!op)
        return;

    _next_op = op;
}

