#pragma once

#include <fstream>
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
    bool _is_adult;
    std::string _start_year;
    std::string _end_year;
    int _runtime_minutes;
    std::string _genres;

public:
    explicit basics_record(std::istream& in);
    bool is_valid();

    bool operator<(const basics_record& rhs) const;
};

class basics_table {
private:
    struct space : std::ctype<char> {
        space() : std::ctype<char>() {}
        static mask const* table() {
            static mask rc[table_size];
            rc['\t'] = std::ctype_base::space;
            rc['\n'] = std::ctype_base::space;
            return rc;
        }
    };

    bool _valid;

    std::set<basics_record*> _data;
    std::string _filename;
    std::vector<std::string> _signature;
    
public:
    explicit basics_table(std::string filename); 
    bool is_valid();
};

