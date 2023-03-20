#pragma once

#include "table.hpp"
#include "basics.hpp"

#include <fstream>
#include <istream>
#include <set>
#include <string>
#include <vector>

class ratings_record : public record<int> {
private:
    int _tconst;
    float _average_rating;
    int _num_votes;

public:
    ratings_record();
    explicit ratings_record(std::istream& in);
    explicit ratings_record(int pk);

    const int& tconst() const;
    const float& average_rating() const;
    const int& num_votes() const;

    void parse_tconst(std::istream& in, char* buf, size_t buf_size, int& field, char delim);

    int primary_key() const;
};

class ratings_table : public table<ratings_record> {
private:
    class rating_cmp {
    public:
        bool operator()(const ratings_record& lhs, const ratings_record& rhs) const;
    };
public:
    explicit ratings_table(std::string filename);

    std::set<ratings_record, rating_cmp> top(basics_table& bt);
};

