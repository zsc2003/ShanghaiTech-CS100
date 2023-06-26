#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>
#include <cstdlib>

class Dynarray {
public:
/*  ----------- newly added below -----------------*/
    using size_type = std::size_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using const_pointer = const int*;
    using const_reference = const int&;
    static const size_type npos = static_cast<std::size_t>(-1);
    // using npos = -1;
    // using npos = static_cast<std::size_t>(-1);

    size_type find(value_type x, size_type start = 0) const
    {
        for (size_type i = start; i < length; ++i)
            if (this->data[i] == x)
                return i;
        return npos;
    }

    Dynarray(Dynarray&& other) noexcept
     : length(other.length), data(other.data) 
    {
        other.length = 0;
        other.data = nullptr;
    }

    Dynarray &operator=(Dynarray&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data = other.data;
            other.length = 0;
            other.data = nullptr;
        }
        return *this;
    }

    
/*  ----------- newly added above -----------------*/

    Dynarray() : length(0), data(nullptr) {}

    explicit Dynarray(size_type n) : length(n), data(new value_type[n])
    {
        for(size_type i = 0; i != n; ++i)
            data[i] = 0;
    }

    Dynarray(size_type n, value_type x) : length(n), data(new value_type[n])
    {
        for (size_type i = 0; i != n; ++i)
            data[i] = x;
    }

    Dynarray(const_pointer begin, const_pointer end) : length(end - begin), data(new value_type[end - begin])
    {
        for (size_type i = 0; i != length; ++i)
            data[i] = begin[i];
    }

    Dynarray(const Dynarray& other) : length(other.length), data(new value_type[other.length])
    {
        for (size_type i = 0; i != length; ++i)
            data[i] = other.data[i];
    }

    Dynarray &operator=(const Dynarray& other)
    {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new value_type[length];
            for (size_type i = 0; i != length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    
    ~Dynarray()
    {
        delete[] data;
    }

    size_type size() const
    {
        return length;
    }

    bool empty() const
    {
        return length == 0;
    }
    
    reference at(size_type i)
    {
        if (i >= length)
            throw std::out_of_range("index out of range");
        return data[i];
    }

    const_reference at(size_type i) const
    {
        if (i >= length)
            throw std::out_of_range("index out of range");
        return data[i];
    }

private:
    size_type length;
    pointer data;
};

#endif // DYNARRAY_HPP