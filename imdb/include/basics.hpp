#pragma once

#include <fstream>
#include <set>
#include <string>
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

    bool is_valid() const;
    bool is(const std::string& tconst) const;

    bool operator<(const basics_record& rhs) const;

    void parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim);
    void parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim);

    const std::string& tconst() const;
    const std::string& title_type() const;
    const std::string& primary_title() const;
    const std::string& original_title() const;
    const int& is_adult() const;
    const std::string& start_year() const;
    const std::string& end_year() const;
    const int& runtime_minutes() const;
    const std::string& genres() const;

};

class basics_table {
private:
    bool _valid;

    std::set<basics_record> _data;
    std::ifstream _in;
    std::vector<std::string> _signature;
    
public:
    explicit basics_table(std::string filename); 
    bool is_valid();

    basics_record query_record(std::string tconst);
    
};

