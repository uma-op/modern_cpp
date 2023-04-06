#include <sstream>
#include <string>
#include <utility>

#include "cat.hpp"
#include "echo.hpp"
#include "operation_interface.hpp"
#include "pipeline.hpp"
#include "tail.hpp"

pipeline::pipeline() :
    _begin(new echo()),
    _end(_begin.get()) {}

pipeline::pipeline(const std::string& str) :
    pipeline() {
    
    std::stringstream s(str);
    std::string cmd, arg;
    char sep;

    while (s >> cmd) {
        s >> arg;

        if (cmd == "ehco")
            add_operation(std::make_unique<echo>(arg));
        else if (cmd == "cat")
            add_operation(std::make_unique<cat>(arg));
        else if (cmd == "tail")
            add_operation(std::make_unique<tail>(std::stoi(arg)));

        s >> sep;
    }
    
}

void pipeline::add_operation(operation_interface::opptr_t op) {
    operation_interface* temp = op.get();
    _end->set_next_operation(std::move(op));
    _end = temp;
}

void pipeline::start_processing() {
    _begin->handle_end_of_input();
}

