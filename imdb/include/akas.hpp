#pragma once

#include "table.hpp"

#include <fstream>
#include <set>
#include <string>
#include <vector>

class akas_record : public record<std::pair<int, int>> {
private:
    int _title_id;
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

    const int& title_id() const;
    const int& ordering() const;
    const std::string& title() const;
    const std::string& region() const;
    const std::string& language() const;
    const std::string& types() const;
    const std::string& attributes() const;
    const int& is_original_title() const;

    primary_key_t primary_key() const;
};

class akas_table : table<akas_record> {
public:
    explicit akas_table(std::string filename);

    std::vector<akas_record> query_where(int tconst);
};

