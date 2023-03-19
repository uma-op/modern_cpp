#pragma once

#include <cstddef>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class preemptive_heap {
private:
    T *_data;
    size_t _size, _cap;

    void sift_up(size_t i) {
        while (i > 0) {
            if (Compare{}(_data[i], _data[(i - 1) / 2]))
                break;

            T t = _data[(i - 1) / 2];
            _data[(i - 1) / 2] = _data[i];
            _data[i] = t;
            i = (i - 1) / 2;
        }
    }
    
    public:
        preemptive_heap(size_t cap) : _data(new T[cap + 1]), _size(0), _cap(cap) {}

        ~preemptive_heap() {
            delete [] _data;
        }

        void insert(T elem) {
            _data[_size] = elem;
            sift_up(_size);
            _size = (_size == _cap ? _cap : _size + 1);
        }
};
