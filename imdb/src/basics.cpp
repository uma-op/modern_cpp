#include "basics.hpp"

#include <fstream>
#include <iostream>
#include <string>

basics_record::basics_record()  : 
    record<int>(),
    _tconst(),
    _title_type(),
    _primary_title(),
    _original_title(),
    _is_adult(),
    _start_year(),
    _end_year(),
    _runtime_minutes(),
    _genres() {}

basics_record::basics_record(std::istream& in) :
    basics_record::basics_record() {

    parse_tconst(in, _tconst, '\t');
    parse_string(in, _title_type, '\t');
    parse_string(in, _primary_title, '\t');
    parse_string(in, _original_title, '\t');
    parse_int(in, _is_adult, '\t');
    parse_string(in, _start_year, '\t');
    parse_string(in, _end_year, '\t');
    parse_int(in, _runtime_minutes, '\t');
    parse_string(in, _genres, '\n');
}

basics_record::basics_record(int pk) :
    basics_record() {

    _tconst = pk;
}

const int& basics_record::tconst() const {
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

int basics_record::primary_key() const {
    return _tconst;
}

basics_table::basics_table(std::string filename) :
    table<basics_record>(filename) {

    _signature = {
        "tconst", "titleType", "primaryTitle",
        "originalTitle", "isAdult", "startYear",
        "endYear", "runtimeMinutes", "genres"
    };

    std::string column;

    for (std::string expected_column : _signature) {
        _in >> column;

        if (column != expected_column) {
            std::cout << "Invalid ratings signature: expect: " << expected_column << " got: " << column << '\n';
            _valid = false;
            return;
        }
    }

    _in.get();

    _start_pos = _in.tellg();
}

