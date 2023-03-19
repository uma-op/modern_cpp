#include "basics.hpp"
#include "ratings.hpp"

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("input-file,I", po::value<std::vector<std::string>>(), "specify the input file")
        ("minutes,m", po::value<int>(), "max movie minutes")
    ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("input-file"))
        for (std::string filename : vm["input-file"].as<std::vector<std::string>>())
            std::cout << "Filename: " << filename << '\n';

    ratings_table rt(vm["input-file"].as<std::vector<std::string>>()[0]);

    std::set<ratings_record>::const_iterator b = rt.cbegin();
    std::set<ratings_record>::const_iterator e = rt.cend();

    for (; b != e; b++)
        std::cout << b->tconst() << ' ' << b->average_rating() << ' ' << b->num_votes() << std::endl;

    return 0;
}
