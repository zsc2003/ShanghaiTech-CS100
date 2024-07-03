#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Given a vector of strings @c strings, reduce this vector so that each
 * string appears only once. After the function call, @c strings contains the
 * same set of elements (possibly sorted) as the original vector, but each
 * element appears only once.
 *
 * @param strings The given vector of strings.
 */
void dropDuplicates(std::vector<std::string> strings) {
  // FIXME: The type of the parameter `strings` may be incorrect.
  // TODO: Implement this function.
}

/**
 * @brief Given a vector of strings @c strings and a nonnegative integer @c k,
 * partition the vector into two parts (with the elements rearranged) so that
 * the first part contains all the strings with length no greater than @c k and
 * the second part contains the rest of the strings. Return an iterator just
 * past the last element of the first part.
 *
 * @param strings The given vector of strings.
 * @return An iterator just past the last element of the first part. In
 * particular, if the second part is not empty, the returned iterator will refer
 * to the first element of the second part.
 */
auto partitionByLength(std::vector<std::string> strings, std::size_t k) {
  // FIXME: The type of the parameter `strings` may be incorrect.
  // TODO: Implement this function.
}

/**
 * @brief Generate all the permutations of {1, 2, ..., n} in lexicographical
 * order, and print them to @c os.
 *
 */
void generatePermutations(int n, const std::ostream &os) {
  // FIXME: The type of the parameter `os` may be incorrect.

  std::vector<int> numbers(n);

  // TODO: Fill `numbers` with {1, 2, ..., n}.

  do {
    // TODO: Print the numbers, separated by a space.

    os << '\n';
  } while (/* TODO: Generate the next permutation */);
}
