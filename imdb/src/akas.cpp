#include "akas.hpp"
#include "table.hpp"

akas_record::akas_record() :
    record<std::pair<int, int>>(),
    _title_id(),
    _ordering(),
    _title(),
    _region(),
    _language(),
    _types(),
    _attributes(),
    _is_original_title() {}

akas_record::akas_record(std::istream& in) :
    akas_record() {

    char* buf = new char[1024];

    parse_tconst(in, buf, 1024, _title_id, '\t');
    parse_int(in, buf, 1024, _ordering, '\t');
    parse_string(in, buf, 1024, _title, '\t');
    parse_string(in, buf, 1024, _region, '\t');
    parse_string(in, buf, 1024, _language, '\t');
    parse_string(in, buf, 1024, _types, '\t');
    parse_string(in, buf, 1024, _attributes, '\t');
    parse_int(in, buf, 1024, _is_original_title, '\n');
    
    delete [] buf;
}

const int& akas_record::title_id() const {
    return _title_id;
}

const int& akas_record::ordering() const {
    return _ordering;
}

const std::string& akas_record::title() const {
    return _title;
}

const std::string& akas_record::region() const {
    return _region;
}

const std::string& akas_record::language() const {
    return _language;
}

const std::string& akas_record::types() const {
    return _types;
}

const std::string& akas_record::attributes() const {
    return _attributes;
}

const int& akas_record::is_original_title() const {
    return _is_original_title;
}

void akas_record::parse_tconst(std::istream& in, char* buf, size_t buf_size, int& field, char delim) {
    if (!is_valid())
        return;

    in.getline(buf, buf_size, delim);

    try {
        field = std::stoi(buf + 2);
    } catch (...) {
        invalidate();
    }
}

akas_record::primary_key_t akas_record::primary_key() const {
    return {_title_id, _ordering};
}

akas_table::akas_table(std::string filename) :
    table<akas_record>(filename) {

    _signature = {
        "titleId", "ordering", "title",
        "region", "language", "types",
        "attributes", "isOriginalTitle" 
    };

    std::string column;

    for (std::string expected_column : _signature) {
        _in >> column;

        if (column != expected_column) {
            _valid = false;
            return;
        }
    }

    _in.get();

    _start_pos = _in.tellg();
}

