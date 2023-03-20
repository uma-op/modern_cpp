#pragma once

#include <fstream>
#include <istream>
#include <vector>

template <typename T>
class record {
protected:
    bool _valid;

public:
    using primary_key_t = T;

    record() : _valid(true) {}

    bool is_valid() const {
        return _valid;
    }

    void invalidate() {
        _valid = false;
    }

    bool operator<(const record& rhs) const {
        return primary_key() < rhs.primary_key();
    }

    void parse_int(std::istream& in, char* buf, size_t buf_size, int& field, char delim) {
        if (!_valid)
            return;

        in.getline(buf, buf_size, delim);

        if (buf[0] == '\\' && buf[1] == 'N') {
            field = 0;
            return;
        }

        try {
            field = std::stoi(buf);
        } catch (...) {
            _valid = false;
        }
    }

    void parse_float(std::istream& in, char* buf, size_t buf_size, float& field, char delim) {
        if (!_valid)
            return;

        in.getline(buf, buf_size, delim);

        if (buf[0] == '\\' && buf[1] == 'N') {
            field = 0;
            return;
        }

        try {
            field = std::stof(buf);
        } catch (...) {
            _valid = false;
        }
    }

    void parse_string(std::istream& in, char* buf, size_t buf_size, std::string& field, char delim) {
        if (!_valid)
            return;

        in.getline(buf, buf_size, delim);

        if (in.gcount() == 0 && in.eof()) {
            _valid = false;
        } else {
            field.assign(buf);
        }
    }

    virtual primary_key_t primary_key() const = 0;
};

template <typename record_t>
class table {
protected:
    bool _valid;

    std::vector<std::string> _signature;
    
    std::ifstream _in;
    std::ifstream::pos_type _start_pos;
    
    typename record_t::primary_key_t _max_record;

public:
    explicit table(std::string filename) : 
        _valid(true),
        _signature(),
        _in(filename),
        _start_pos(),
        _max_record() {

        std::string column;

        for (std::string expected_column : _signature) {
            _in >> column;

            if (column != expected_column) {
                _valid = false;
                return;
            }
        }

        _start_pos = _in.tellg();
    }

    bool is_valid() const {
        return _valid;
    }

    record_t query_record(typename record_t::primary_key_t pk) {
        if (pk < _max_record) {
            _in.seekg(_start_pos);
            _max_record = 0;
        }

        record_t r(_in);
        for (; r.primary_key() != pk && r.is_valid(); r = record_t(_in))
            if (r.primary_key() > _max_record)
                _max_record = r.primary_key();

        return r;
    }
};

