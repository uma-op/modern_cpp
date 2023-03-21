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
        ("basics,b", po::value<std::string>(), "specify the basics file")
        ("ratings,r", po::value<std::string>(), "specify the records file")
        ("akas,a", po::value<std::string>(), "specify the akas file")
        ("minutes,m", po::value<int>(), "max movie minutes")
    ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    basics_table bt(vm["basics"].as<std::string>());
    ratings_table rt(vm["ratings"].as<std::string>());
    akas_table at(vm["akas"].as<std::string>());
    
    std::map<int, basics_record> brs = rt.top(bt, vm["minutes"].as<int>());
    std::vector<akas_record> ars;
    
    for (std::pair<int, basics_record> br : brs) {
        ars = at.query_where(br.second.tconst());

        akas_record ar_ru = ars[0];

        for (akas_record ar : ars)
            if (ar.language() == "ru" || ar.language() == "RU")
                ar_ru = ar;
        std::cout << br.second.original_title() << '|' << ar_ru.title() << std::endl;    
    }

    return 0;
}
