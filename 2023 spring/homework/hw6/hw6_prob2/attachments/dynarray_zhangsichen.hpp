#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

class Dynarray
{
	int *content;
	std::size_t length;

public:
	Dynarray() : content(new int[0]) {}

	explicit Dynarray(std::size_t n) : content(new int[n]{}), length(n) {}

	Dynarray(unsigned int n, int x) : content(new int[n]{}), length(n)
	{
		for (size_t i = 0; i < n; i++)
		{
			at(i) = x;
		}
	}
	Dynarray(const int *p, const int *q) : content(new int[q - p]{}), length(q - p)
	{
		for (size_t i = 0; i < length; i++)
		{
			content[i] = *p;
			p++;
		}
	}
	Dynarray(const Dynarray &b) : content(new int[b.size()]{}), length(b.size())
	{
		for (std::size_t i = 0; i != b.size(); ++i)
			content[i] = b.at(i);
	}
	Dynarray &operator=(const Dynarray &b)
	{
		content = new int[b.size()];
		for (std::size_t i = 0; i != b.size(); ++i)
			content[i] = b.at(i);
		length = b.size();
		return *this;
	}
	Dynarray(Dynarray &&b) noexcept : content(b.content), length(b.length)
	{
		b.content = NULL;
		b.length = 0;
	}
	Dynarray &operator=(Dynarray &&other) noexcept
	{
		if (this != &other)
		{
			delete[] content;
			content = other.content;
			length = other.length;
			other.content = NULL;
			other.length = 0;
		}
		return *this;
	}
	~Dynarray()
	{
		delete[] content;
	}
	using size_type = std::size_t;
	using value_type = int;
	using pointer = int *;
	using reference = int &;
	using const_pointer = const int *;
	using const_reference = const int &;

	static const std::size_t npos = static_cast<std::size_t>(-1);

	std::size_t size() const
	{
		return length;
	}
	bool empty() const
	{
		return (length == 0);
	}
	int &at(std::size_t i)
	{
		return content[i];
	}
	const int &at(std::size_t i) const
	{
		return content[i];
	}
	size_t find(int x) const
	{
		for (size_t i = 0; i < length; i++)
		{
			if (content[i] == x)
			{
				return i;
			}
		}
		return npos;
	}
	size_t find(int x, std::size_t pos) const
	{
		for (size_t i = pos; i < length; i++)
		{
			if (content[i] == x)
			{
				return i;
			}
		}
		return npos;
	}
};

#endif // DYNARRAY_HPP
