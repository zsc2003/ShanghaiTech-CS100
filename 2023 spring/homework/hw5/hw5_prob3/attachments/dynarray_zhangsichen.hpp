#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 

#include <cstddef>
#include <stdexcept>

class Dynarray {
		int *a, *b;
		std::size_t length;
	public:
		Dynarray()
			: a(new int[0]) {}

		Dynarray(std::size_t n)
			: a(new int[n] {}), length(n) {}

		Dynarray(unsigned int n, int x)
			: a(new int[n] {
			x
		}), length(n) {}

		Dynarray(int begin, int end) {
			length = end - begin;
			a = (new int[length]);
			for (int i = 0; i <= end - begin; i++) {
				a[i] = end + i;
			}
		}

		Dynarray(const Dynarray &b)
			: a(new int[b.size()] {}), length(b.size()) {
			for (std::size_t i = 0; i != b.size(); ++i)
				a[i] = b.at(i);
			}
		~Dynarray() {
			delete[] a;
		}

		std::size_t size() const {
				return length;
			}
		bool empty() const {
				return length != 0;
			}
		int &at(std::size_t i) {
				return a[i];
			}
		const int &at(std::size_t i) const {
				return a[i];
			}
	
};

#endif // DYNARRAY_HPP
