#pragma once

#include "heap.hpp"

#include <fstream>
#include <istream>
#include <string>
#include <set>
#include <vector>

class basics_record {
private:
    bool _valid;

    std::string _tconst;
    std::string _title_type;
    std::string _primary_title;
    std::string _original_title;
    int _is_adult;
    std::string _start_year;
    std::string _end_year;
    int _runtime_minutes;
    std::string _genres;

public:
    basics_record();
    explicit basics_record(std::istream& in);
    bool is_valid();

    bool operator<(const basics_record& rhs) const;

    void parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim);
    void parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim);
};

class basics_table {
private:
    bool _valid;

    std::set<basics_record> _data;
    std::string _filename;
    std::vector<std::string> _signature;
    
public:
    basics_table();
    explicit basics_table(std::string filename); 
    bool is_valid();
};

