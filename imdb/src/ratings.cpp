#include "ratings.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>

ratings_record::ratings_record() :
    _valid(true),
    _tconst(),
    _average_rating(),
    _num_votes() {}

ratings_record::ratings_record(std::istream& in) :
    _valid(true),
    _tconst(),
    _average_rating(),
    _num_votes() {

    char* buf = new char[256];
    
    parse_string(in, buf, 256, _tconst, '\t');
    parse_float(in, buf, 256, _average_rating, '\t');
    parse_int(in, buf, 256, _num_votes, '\n');

    delete [] buf;
}

bool ratings_record::is_valid() {
    return _valid;
}

bool ratings_record::operator<(const ratings_record& rhs) const {
    return _average_rating < rhs._average_rating;
}

void ratings_record::parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim) {
    if (!_valid)
        return;

    in.getline(buf, buf_size, delim);

    try {
        field = std::stoi(buf);
    } catch (...) {
        _valid = false;
    }
}

void ratings_record::parse_float(std::istream& in, char* buf, size_t buf_size, float& field, char delim) {
    if (!_valid)
        return;

    in.getline(buf, buf_size, delim);

    try {
        field = std::stof(buf);
    } catch (...) {
        _valid = false;
    }
}

void ratings_record::parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim) {
    if (!_valid)
        return;

    in.getline(buf, buf_size, delim);

    if (in.gcount() == 0) {
        _valid = false;
    } else {
        field.assign(buf);
    }
}

ratings_table::ratings_table(std::string filename) : 
    _valid(true),
    _data(10),
    _in(filename),
    _signature({
               "tconst", "averageRating", "numVotes"
               })  {

    std::string column;

    for (std::string expected_column : _signature) {
        _in >> column;

        if (column != expected_column) {
            _valid = false;
            return;
        }
    }
    
    for (ratings_record br(_in); br.is_valid(); br = ratings_record(_in))
        _data.insert(br);
}

bool ratings_table::is_valid() {
    return _valid;
}

