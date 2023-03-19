#pragma once

#include <fstream>
#include <istream>
#include <set>
#include <string>
#include <vector>

class ratings_record {
private:
    bool _valid;

    std::string _tconst;
    float _average_rating;
    int _num_votes;

public:
    ratings_record();
    explicit ratings_record(std::istream& in);
    bool is_valid();

    bool operator<(const ratings_record& rhs) const;

    void parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim);
    void parse_float(std::istream& in, char* buf, size_t buf_size, float& field, char delim);
    void parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim);

    const std::string& tconst() const;
    const float& average_rating() const;
    const int& num_votes() const;
};

class ratings_table {
private:
    bool _valid;

    std::set<ratings_record> _data;
    std::ifstream _in;
    std::vector<std::string> _signature;

public:
    explicit ratings_table(std::string filename);
    bool is_valid();

    void insert_record(const ratings_record& rr);

    std::set<ratings_record>::const_iterator cbegin() const;
    std::set<ratings_record>::const_iterator cend() const;
};

