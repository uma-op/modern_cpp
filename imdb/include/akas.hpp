#pragma once

#include <fstream>
#include <set>
#include <string>
#include <vector>

class akas_record {
private:
    bool _valid;

    std::string _title_id;
    int _ordering;
    std::string _title;
    std::string _region;
    std::string _language;
    std::string _types;
    std::string _attributes;
    int _is_original_title;

public:
    akas_record();
    explicit akas_record(std::istream& in);
    bool is_valid();

    bool operator<(const akas_record& rhs) const;

    void parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim);
    void parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim);

    const std::string& tconst() const;
    const float& average_rating() const;
    const int& num_votes() const;

};

class akas_table {
private:
    bool _valid;

    std::set<akas_record> _data;
    std::ifstream _in;
    std::vector<std::string> _signature;

public:
    explicit akas_table(std::string filename);
    bool is_valid();

    void insert_record(const akas_record& ar);

    std::set<akas_record>::const_iterator cbegin() const;
    std::set<akas_record>::const_iterator cend() const;

};

