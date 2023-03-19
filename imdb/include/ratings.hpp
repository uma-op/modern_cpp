#pragma once

#include "heap.hpp"

#include <istream>
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
};

class ratings_table {
private:
    bool _valid;

    preemptive_heap<ratings_record> _data;
    std::string _filename;
    std::vector<std::string> _signature;

public:
    ratings_table();
    explicit ratings_table(std::string filename);
    bool is_valid();
};

