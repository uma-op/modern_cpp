#include "basics.hpp"
#include "heap.hpp"

#include <fstream>
#include <iostream>
#include <string>

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

bool basics_record::is_valid() const {
    return _valid;
}

bool basics_record::is(const std::string& tconst) const {
    return _tconst == tconst;
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

const std::string& basics_record::tconst() const {
    return _tconst;
}

const std::string& basics_record::title_type() const {
    return _title_type;
}

const std::string& basics_record::primary_title() const {
    return _primary_title;
}

const std::string& basics_record::original_title() const {
    return _original_title;
}

const int& basics_record::is_adult() const {
    return _is_adult;
}

const std::string& basics_record::start_year() const {
    return _start_year;
}

const std::string& basics_record::end_year() const {
    return _end_year;
}

const int& basics_record::runtime_minutes() const {
    return _runtime_minutes;
}

const std::string& basics_record::genres() const {
    return _genres;
}


basics_table::basics_table(std::string filename) :
    _valid(true),
    _data(), 
    _in(filename),
    _signature({
               "tconst", "titleType", "primaryTitle", "originalTitle", "isAdult",
               "startYear", "endYear", "runtimeMinutes", "genres"
               }) {

    std::string column;

    for (std::string expected_column : _signature) {
        _in >> column;

        if (column != expected_column) {
            _valid = false;
            return;
        }
    }
}

bool basics_table::is_valid() {
    return _valid;
}

basics_record basics_table::query_record(std::string tconst) {
    std::ifstream::pos_type pos = _in.tellg();

    basics_record br(_in);
    while (br.is_valid() && !br.is(tconst))
        br = basics_record(_in);
    
    _in.seekg(pos);

    return br;
}

