#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>

#include "cat.hpp"
#include "echo.hpp"
#include "pipeline.hpp"
#include "tail.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ";  // TODO: дописать справку
    }

    pipeline pl(argv[1]);
    pl.start_processing();

    return 0;
}

