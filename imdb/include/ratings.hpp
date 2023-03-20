#pragma once

#include "table.hpp"

#include <fstream>
#include <istream>
#include <set>
#include <string>
#include <vector>

class ratings_record : record<int> {
private:
    bool _valid;

    int _tconst;
    float _average_rating;
    int _num_votes;

public:
    ratings_record();
    explicit ratings_record(std::istream& in);

    const int& tconst() const;
    const float& average_rating() const;
    const int& num_votes() const;

    void parse_tconst(std::istream& in, char* buf, size_t buf_size, int& field, char delim);

    int primary_key() const;
};

class ratings_table : table<int> {
public:
    explicit ratings_table(std::string filename);

};

