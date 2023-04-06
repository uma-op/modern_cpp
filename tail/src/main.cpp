#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>

#include "cat.hpp"
#include "echo.hpp"
#include "tail.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ";  // TODO: дописать справку
    }

    std::stringstream buf(argv[1]);
    std::string token;

    operation_interface* begin;
    operation_interface* end = new echo("");
    begin = end;
    operation_interface* temp;

    std::string cmd, arg;

    while (buf >> cmd) {
        buf >> arg;

        if (cmd == "cat") {
            temp = new cat(arg);
        } else if (cmd == "echo") {
            temp = new echo(arg);
        } else if (cmd == "tail") {
            temp = new tail(static_cast<size_t>(std::stoi(arg)));
        }

        end->set_next_operation(temp);
        end = temp;
        buf >> cmd;  // separator
    }

    begin->handle_end_of_input();

    return 0;
}

