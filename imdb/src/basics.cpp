#include "basics.hpp"

#include <exception>
#include <iostream>
#include <fstream>
#include <istream>
#include <locale>

basics_record::basics_record(std::istream& in) {
    in 
        >> _tconst >> _title_type >> _primary_title 
        >> _original_title >> _is_adult >> _start_year
        >> _end_year >> _runtime_minutes;
}

bool basics_record::is_valid() {
    return _valid;
}

bool basics_record::operator<(const basics_record& rhs) const {
    return _tconst < rhs._tconst;
}

basics_table::basics_table(std::string filename) : 
    _data(), 
    _filename(filename),
    _signature({
               "tconst", "titleType", "primatyTitle", "originalTitle", "isAdult",
               "startYear", "endYear", "runtimeMinutes", "genres"
               }) {

    std::ifstream in(filename);
    in.imbue(std::locale(in.getloc(), new space));
    
    std::string column;

    for (std::string expected_column : _signature) {
        in >> column;

        if (column != expected_column) {
            _valid = false;
            return;
        }
    }
    
    for (basics_record* br = new basics_record(in); br->is_valid(); br = new basics_record(in))
        _data.insert(br);
}

bool basics_table::is_valid() {
    return _valid;
}

