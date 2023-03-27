#pragma once

#include "table.hpp"

#include <fstream>
#include <set>
#include <string>
#include <vector>

class basics_record : public record<int> {
private:
    int _tconst;
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
    explicit basics_record(int pk);

    const int& tconst() const;
    const std::string& title_type() const;
    const std::string& primary_title() const;
    const std::string& original_title() const;
    const int& is_adult() const;
    const std::string& start_year() const;
    const std::string& end_year() const;
    const int& runtime_minutes() const;
    const std::string& genres() const;

    int primary_key() const;
};

class basics_table : public table<basics_record> {
public:
    explicit basics_table(std::string filename); 
};

