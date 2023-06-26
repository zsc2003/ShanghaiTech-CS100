#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>
#include <cstdlib>

class Dynarray {
public:
    using size_type = std::size_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using const_pointer = const int*;
    using const_reference = const int&;
    static const std::size_t npos = static_cast<std::size_t>(-1);

private:
    int *m_storage;
    std::size_t m_length;

public:
    // Default constructor
    Dynarray() : m_storage(nullptr), m_length(0) {}

    // Constructor with size parameter
    explicit Dynarray(std::size_t n) : m_storage(new int[n]{}), m_length(n) {}

    Dynarray(std::size_t n, int x) : m_storage(new int[n]), m_length(n) {
        for (std::size_t i = 0; i < n; i++) {
            m_storage[i] = x;
        }
    }
    // Dynarray(begin, end)
    Dynarray(const_pointer begin, const_pointer end) : m_storage(new int[end - begin]), m_length(end - begin) {
        for (size_type i = 0; i != m_length; ++i)
            m_storage[i] = begin[i];
    }


    // A function to obtain its length (size).
    std::size_t size() const {
        return m_length;
    }


    // A function telling whether it is empty.
    bool empty() const {
        return m_length == 0;
    }
    // Copy constructor
    Dynarray(const Dynarray &other)
        : m_storage(new int[other.m_length]), m_length(other.m_length) {
        for (size_type i = 0; i != m_length; ++i)
            m_storage[i] = other.m_storage[i];
    }

    // Copy assignment operator
    Dynarray &operator=(const Dynarray &other) {
        if (this != &other) {
            int *temp = new int[other.m_length];
            for (size_type i = 0; i != m_length; ++i)
                m_storage[i] = other.m_storage[i];
            delete[] m_storage;
            m_storage = temp;
            m_length = other.m_length;
        }
        return *this;
    }

    // Move constructor
    Dynarray(Dynarray&& other) noexcept : m_storage(other.m_storage), m_length(other.m_length) {
        other.m_storage = nullptr;
        other.m_length = 0;
    }    

    // Move assignment operator
    Dynarray &operator=(Dynarray &&other) noexcept {
        if (this != &other) {
            delete[] m_storage;
            m_storage = other.m_storage;
            m_length = other.m_length;
            other.m_storage = nullptr;
            other.m_length = 0;
        }
        return *this;
    }
    
    // Element access operator
    int &operator[](std::size_t i) {
        if (i >= m_length) {
            throw std::out_of_range("Dynarray index out of range!");
        }
        return m_storage[i];
    }

    // Const element access operator
    const int &operator[](std::size_t i) const {
        if (i >= m_length) {
            throw std::out_of_range("Dynarray index out of range!");
        }
        return m_storage[i];
    }

    // Element access function returning reference
    int &at(std::size_t i) {
        if (i >= m_length) {
            throw std::out_of_range("Dynarray index out of range!");
        }
        return m_storage[i];
    }

    // Const element access function returning reference
    const int &at(std::size_t i) const {
        if (i >= m_length) {
            throw std::out_of_range("Dynarray index out of range!");
        }
        return m_storage[i];
    }

    // Find
    std::size_t find(int x, std::size_t pos = 0) const noexcept {
        for (std::size_t i = pos; i < m_length; ++i) {
            if (m_storage[i] == x) {
                return i;
            }
        }
        return npos;
    }

    // Destructor
    ~Dynarray() {
        delete[] m_storage;
        m_storage = nullptr;
        m_length = 0;
    }
};

#endif // DYNARRAY_HPP