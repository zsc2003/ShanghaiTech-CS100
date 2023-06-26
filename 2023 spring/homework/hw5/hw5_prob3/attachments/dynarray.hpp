#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>

class Dynarray {
private:
    std::size_t length;
    int* data;

public:
    Dynarray() : length(0), data(nullptr) {}

    explicit Dynarray(std::size_t n) : length(n), data(new int[n])
    {
        for(std::size_t i = 0; i != n; ++i)
            data[i] = 0;
    }

    Dynarray(std::size_t n, int x) : length(n), data(new int[n])
    {
        for (std::size_t i = 0; i != n; ++i)
            data[i] = x;
    }

    Dynarray(const int* begin, const int* end) : length(end - begin), data(new int[end - begin])
    {
        for (std::size_t i = 0; i != length; ++i)
            data[i] = begin[i];
    }

    Dynarray(const Dynarray& other) : length(other.length), data(new int[other.length])
    {
        for (std::size_t i = 0; i != length; ++i)
            data[i] = other.data[i];
    }

    Dynarray &operator=(const Dynarray& other)
    {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new int[length];
            for (std::size_t i = 0; i != length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    
    ~Dynarray()
    {
        delete[] data;
    }

    std::size_t size() const
    {
        return length;
    }

    bool empty() const
    {
        return length == 0;
    }
    
    int& at(std::size_t i)
    {
        if (i >= length)
            throw std::out_of_range("index out of range");
        return data[i];
    }

    const int& at(std::size_t i) const
    {
        if (i >= length)
            throw std::out_of_range("index out of range");
        return data[i];
    }
};

#endif // DYNARRAY_HPP