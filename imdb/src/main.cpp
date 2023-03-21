#include "akas.hpp"
#include "basics.hpp"
#include "ratings.hpp"

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include <iostream>
#include <ostream>
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

    basics_table bt(vm["input-file"].as<std::vector<std::string>>()[0]);
    ratings_table rt(vm["input-file"].as<std::vector<std::string>>()[1]);
    akas_table at(vm["input-file"].as<std::vector<std::string>>()[2]);
    
    std::map<int, basics_record> brs = rt.top(bt);
    std::vector<akas_record> ars;
    
    for (std::pair<int, basics_record> br : brs) {
        ars = at.query_where(br.second.tconst());

        akas_record ar_ru = ars[0];

        for (akas_record ar : ars)
            if (ar.language() == "ru" || ar.language() == "RU")
                ar_ru = ar;
        std::cout << br.second.original_title() << ' ' << ar_ru.title() << ' ' << ar_ru.language() << std::endl;    
    }

    return 0;
}
