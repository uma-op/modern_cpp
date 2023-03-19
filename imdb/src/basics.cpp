#include "basics.hpp"
#include "heap.hpp"

#include <exception>
#include <iostream>
#include <fstream>
#include <istream>
#include <locale>
#include <sstream>

basics_record::basics_record()  : 
    _valid(true),
    _tconst(),
    _title_type(),
    _primary_title(),
    _original_title(),
    _is_adult(),
    _start_year(),
    _end_year(),
    _runtime_minutes(),
    _genres() {}

basics_record::basics_record(std::istream& in) : basics_record::basics_record() {

    char* buf = new char[256];

    parse_string(in, buf, 256, _tconst, '\t');
    parse_string(in, buf, 256, _title_type, '\t');
    parse_string(in, buf, 256, _primary_title, '\t');
    parse_string(in, buf, 256, _original_title, '\t');
    parse_int(in, buf, 256, _is_adult, '\t');
    parse_string(in, buf, 256, _start_year, '\t');
    parse_string(in, buf, 256, _end_year, '\t');
    parse_int(in, buf, 256, _runtime_minutes, '\t');
    parse_string(in, buf, 256, _genres, '\n');

    delete [] buf;
}

bool basics_record::is_valid() {
    return _valid;
}

bool basics_record::operator<(const basics_record& rhs) const {
    return _tconst < rhs._tconst;
}

void basics_record::parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim) {
    if (!_valid)
        return;

    in.getline(buf, buf_size, delim);

    try {
        field = std::stoi(buf);
    } catch (...) {
        _valid = false;
    }
}

void basics_record::parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim) {
    if (!_valid)
        return;

    in.getline(buf, buf_size, delim);

    if (in.gcount() == 0) {
        _valid = false;
    } else {
        field.assign(buf);
    }
}


basics_table::basics_table() :
    _valid(true),
    _data(), 
    _filename(),
    _signature({
               "tconst", "titleType", "primaryTitle", "originalTitle", "isAdult",
               "startYear", "endYear", "runtimeMinutes", "genres"
               }) {}

basics_table::basics_table(std::string filename) : basics_table::basics_table() {
    _filename = filename;

    std::ifstream in(filename);
    std::string column;

    for (std::string expected_column : _signature) {
        in >> column;

        if (column != expected_column) {
            _valid = false;
            return;
        }
    }
    
    for (basics_record br(in); br.is_valid(); br = basics_record(in))
        _data.insert(br);
}

bool basics_table::is_valid() {
    return _valid;
}

