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

    parse_tconst(in, _title_id, '\t');
    parse_int(in, _ordering, '\t');
    parse_string(in, _title, '\t');
    parse_string(in, _region, '\t');
    parse_string(in, _language, '\t');
    parse_string(in, _types, '\t');
    parse_string(in, _attributes, '\t');
    parse_int(in, _is_original_title, '\n');
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

std::vector<akas_record> akas_table::query_where(int tconst) {
    std::vector<akas_record> ars;
    if (tconst < _max_record.first) {
        _in.seekg(_start_pos);
        _max_record = {};
    }

    akas_record r(_in);

    for (;r.title_id() != tconst; r = akas_record(_in)) {
        if (r.primary_key() > _max_record)
            _max_record = r.primary_key();
    }

    for (;r.title_id() == tconst; r = akas_record(_in)) {
        if (r.primary_key() > _max_record)
            _max_record = r.primary_key();
        ars.push_back(r);
    }

    return ars;
}

