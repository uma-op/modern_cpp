#include "ratings.hpp"
#include "basics.hpp"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

ratings_record::ratings_record() :
    record<int>(),
    _tconst(),
    _average_rating(),
    _num_votes() {}

ratings_record::ratings_record(std::istream& in) :
    ratings_record::ratings_record() {

    char* buf = new char[1024];
    
    parse_tconst(in, buf, 1024, _tconst, '\t');
    parse_float(in, buf, 1024, _average_rating, '\t');
    parse_int(in, buf, 1024, _num_votes, '\n');

    delete [] buf;
}

ratings_record::ratings_record(int pk) :
    ratings_record::ratings_record() {
    
    _tconst = pk;
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
    if (!is_valid())
        return;

    in.getline(buf, buf_size, delim);
    
    try {
        field = std::stoi(buf + 2);
    } catch (...) {
        invalidate();
    }
}

ratings_table::ratings_table(std::string filename) : 
    table<ratings_record>(filename) {

    _signature = {
        "tconst", "averageRating", "numVotes"
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

bool ratings_table::rating_cmp::operator()(const ratings_record& lhs, const ratings_record& rhs) const {
    if (lhs.average_rating() < rhs.average_rating())
        return true;
    else if (lhs.average_rating() > rhs.average_rating())
        return false;

    return lhs.tconst() < rhs.tconst();
}

std::map<int, basics_record> ratings_table::top(basics_table& bt, int minutes) {
    std::map<int, basics_record> brs;
    std::set<ratings_record, rating_cmp> rrs;

    basics_record br;
    
    _in.seekg(_start_pos);

    for (ratings_record rr = ratings_record(_in); rr.is_valid(); rr = ratings_record(_in)) {
        br = bt.query_record(rr.primary_key());

        if (!br.is_valid() 
            || br.is_adult() == 1 
            || br.runtime_minutes() > minutes 
            || br.title_type() != "movie" 
            || rr.num_votes() < 1000)
            continue;

        rrs.insert(rr);
        brs.insert({rr.primary_key(), br});

        if (rrs.size() > 10) {
            brs.erase(rrs.begin()->primary_key());
            rrs.erase(rrs.begin());
        }
    }

    return brs;
}

