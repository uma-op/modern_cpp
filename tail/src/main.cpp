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
        std::cout
            << "Usage: \n"
            << "    tail '[INSTRUCTION [| INSTRUCTION ...]]' \n\n"
            << "    INCTRUCTION\n"
            << "        echo    <some strign>   - transits 'some string' to next operation\n"
            << "        cat     <filename.txt>  - transits own input and content of 'filename.txt' to next operation\n"
            << "        tail    <N>             - transits last 'N' strings of input to next operation\n";

        return 0;
    }


    pipeline pl(argv[1]);
    pl.start_processing();

    return 0;
}

