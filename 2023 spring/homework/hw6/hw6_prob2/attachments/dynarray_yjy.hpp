#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP
#include <string>

#include <cstddef>
#include <stdexcept>

class Dynarray 
{
    // using namespace std;
public:
using size_type = std::size_t;
using value_type = int;
using pointer = int *;
using reference = int &;
using const_pointer = const int *;
using const_reference = const int &;
static constexpr size_type npos = static_cast<std::size_t>(-1);

    int *m_storage;
    std::size_t m_length;
    // std::string m_label;

    Dynarray()
        : m_storage(nullptr), m_length(0) {}
    Dynarray(std::size_t n,int x)
        : m_storage(new int[n]), m_length(n) 
        {
            for(std::size_t i = 0;i < n;i++)
            {
                m_storage[i] = x;
            }
        }
    void swap(Dynarray &other)
    {
        std::swap(m_length, other.m_length);
        std::swap(m_storage, other.m_storage);
    }
    Dynarray &operator= (const Dynarray &other)
    {
        Dynarray(other).swap(*this);
        return *this;
    }
    Dynarray(const int *begin, const int *end)
        : m_storage(new int[end - begin]), m_length(end - begin)
        {
            for(std::size_t i = 0;i < m_length; i++)
            {
                m_storage[i] = begin[i];
            }
        }
    explicit Dynarray(std::size_t n)
        : m_storage(new int[n]{}), m_length(n) {}
    ~Dynarray() 
    {
        delete[] m_storage;
    }
    std::size_t size() const 
    {
        return m_length;
    }
    bool empty() const 
    {
        return m_length == 0;
    }
    int &at(std::size_t i) 
    {
        if(i>=m_length)
        {
            throw std::out_of_range{"Dynarray index out of range!"};
        }
        return m_storage[i];
    }
    const int &at(std::size_t i) const 
    {
        if(i>=m_length)
        {
            throw std::out_of_range{"Dynarray index out of range!"};
        }
        return m_storage[i];
    }
    Dynarray(const Dynarray &other) // copy constructor
        : m_storage(new int[other.size()]), m_length(other.size()) 
    {
        for (std::size_t i = 0; i < other.size(); ++i)
            m_storage[i] = other.at(i);
    }

    Dynarray(Dynarray&& other) noexcept
        : m_storage(other.m_storage)
        , m_length(other.m_length)
    {
        other.m_length = 0;
        other.m_storage = nullptr;
    }

    Dynarray &operator=(Dynarray&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_storage;
            m_length = other.m_length;
            m_storage= other.m_storage;
            other.m_length = 0;
            other.m_storage = nullptr;
        }
        return *this;
    }

    Dynarray concat(const Dynarray &a, const Dynarray &b) 
    {
        Dynarray result(a.size() + b.size());
        for (size_type i = 0; i != a.size(); ++i)
            result.at(i) = a.at(i);
        for (size_type i = 0; i != b.size(); ++i)
            result.at(a.size() + i) = b.at(i);
        return result;
    }

    size_type find(int x, size_type pos = 0)  const
    {
        for(size_type i = pos;i < m_length;i++)
        {
            if(m_storage[i] == x)
            {
                // return i+pos;
                return i;
            }
        }
        // return const std::size_t Dynarray::nops;
        return Dynarray::npos;
    }

};
#endif // DYNARRAY_HPP