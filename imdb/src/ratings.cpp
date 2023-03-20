#include "ratings.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <utility>

ratings_record::ratings_record() :
    record<int>(),
    _tconst(),
    _average_rating(),
    _num_votes() {}

ratings_record::ratings_record(std::istream& in) :
    ratings_record::ratings_record() {

    char* buf = new char[256];
    
    parse_tconst(in, buf, 256, _tconst, '\t');
    parse_float(in, buf, 256, _average_rating, '\t');
    parse_int(in, buf, 256, _num_votes, '\n');

    delete [] buf;
}

const int& ratings_record::tconst() const {
    return _tconst;
}

const float& ratings_record::average_rating() const {
    return _average_rating;
}

const int& ratings_record::num_votes() const {
    return _num_votes;
}

int ratings_record::primary_key() const {
    return _tconst;
}

void ratings_record::parse_tconst(std::istream& in, char* buf, size_t buf_size, int& field, char delim) {
    if (!_valid)
        return;

    in.getline(buf, buf_size, delim);

    try {
        field = std::stoi(buf + 2);
    } catch (...) {
        _valid = false;
    }
}

ratings_table::ratings_table(std::string filename) : 
    table<int>(filename) {

    _signature = {
        "tconst", "averageRating", "numVotes"
    };

    std::string column;

    for (std::string expected_column : _signature) {
        _in >> column;

        if (column != expected_column) {
            _valid = false;
            return;
        }
    }
}

