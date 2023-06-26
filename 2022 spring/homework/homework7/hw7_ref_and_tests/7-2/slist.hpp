#ifndef CS100_HW_SLIST_HPP
#define CS100_HW_SLIST_HPP

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

// Note: as has been pointed out in the problem description, the only
// constructor of the value-type T that is available to you is the
// copy-constructor. You should NOT assume T to be default-constructible or
// copy-assignable. You should NOT assume T to be constructible from an integer,
// or something like 'NULL', etc.
template <typename T>
struct Slist_node {
  T value;
  Slist_node<T> *next;
  // Use nullptr instead of NULL in C++. NULL may cause unexpected results.
  Slist_node(const T &v, Slist_node<T> *p = nullptr) : value(v), next(p) {}

  // The following constructors are from some of your codes, which, if called,
  // will definitely cause compile-error. If you have defined constructors like
  // these, please delete them.

  // Sect 1: default constructors
  // There is no reasonable way to enable default-construction of Slist_node,
  // because it contains a member ('value') that might not be
  // default-constructible.
  // Slist_node() {}
  // Slist_node() = default;
  // Slist_node() { whatever you write here }

  // Sect 2: constructors without initializer-lists.
  // Slist_node(const T &v, Slist_node<T> *p) {
  //   value = v;
  //   next = p;
  // }
  // Slist_node(const T &v) {
  //   value = v;
  //   next = nullptr;
  // }

  // Sect 3: initializing 'value' with 0, NULL, or some other strange things
  // Slist_node() : value(0), ... (whatever here)
  // Slist_node() : value(NULL), ......
  // Slist_node(Slist_node<T> *p) : value(NULL), next(p) {}
};

template <typename T>
class Slist;

template <typename T, bool is_const>
class Slist_iterator {
  using node_t = Slist_node<T>;

 public:
  using value_type = T;
  using difference_type = typename Slist<T>::difference_type;
  using pointer = typename std::conditional<is_const, T const *, T *>::type;
  using reference = typename std::conditional<is_const, T const &, T &>::type;
  using iterator_category = std::forward_iterator_tag;

 private:
  using self_t = Slist_iterator<T, is_const>;

  node_t *m_cur;

 public:
  Slist_iterator(node_t *pos = nullptr) : m_cur(pos) {}

  template <typename Other,
            typename = typename std::enable_if<
                is_const &&
                std::is_same<Other, Slist_iterator<T, false>>::value>::type>
  Slist_iterator(const Other &oi) : m_cur(oi.base()) {}

  node_t *base() const {
    return m_cur;
  }

  self_t next() const {
    return self_t(m_cur->next);
  }

  reference operator*() const {
    return m_cur->value;
  }

  pointer operator->() const {
    return std::addressof(operator*());
  }

  self_t &operator++() {
    m_cur = m_cur->next;
    return *this;
  }

  self_t operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
  }
};

template <typename T, bool C1, bool C2>
inline bool operator==(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename T, bool C1, bool C2>
inline bool operator!=(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
class Slist {
  using node_t = Slist_node<T>;

 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using const_pointer = T const *;
  using const_reference = T const &;

  using iterator = Slist_iterator<T, false>;
  using const_iterator = Slist_iterator<T, true>;

 private:
  node_t *m_head;
  size_type m_length;

  static node_t *s_create_node(const value_type &value,
                               node_t *next = nullptr) {
    return new node_t(value, next);
  }

  static void s_destroy_node(node_t *node) {
    delete node;
  }

  // A recursive way of implementing the copy constructor.
  // This function copies the linked-list with nodes beginning with 'head'.
  static node_t *s_copy_from(node_t *head) {
    if (!head)
      return nullptr;
    // First copy the node pointed by 'head',
    // And then copy the nodes after head.
    return s_create_node(head->value, s_copy_from(head->next));
  }

  // A recursive way of implementing the destructor.
  // This function destroys the linked-list with nodes beginning with 'head'.
  static void s_delete_from(node_t *head) {
    if (!head)
      return;
    s_delete_from(head->next);
    s_destroy_node(head);
  }

 public:
  Slist() : m_head(nullptr), m_length(0) {}

  // The copy-constructor calls the helper function 's_copy_from'.
  Slist(const Slist &other)
      : m_head(s_copy_from(other.m_head)), m_length(other.m_length) {}

  // 'swap' only needs to swap m_head and m_length, without copying the nodes
  void swap(Slist &other) {
    using std::swap;
    swap(m_head, other.m_head);
    swap(m_length, other.m_length);
  }

  Slist &operator=(const Slist &other) {
    // copy-and-swap is born self-assignment-safe and exception-safe.
    // You don't need to check whether this != &other.
    Slist(other).swap(*this);
    return *this;
  }

  // The following are the move-constructor and move-assignment operators of
  // Slist<T>. These functions are not required in the homework problem. By the
  // time you have learned the rvalue references and move semantics, you may try
  // to implement them on yourself and take the following as a reference.

  // Move-constructor of Slist. (Not required in the homework problem)
  Slist(Slist &&other) noexcept // Move operations must be noexcept.
      : m_head(other.m_head), m_length(other.m_length) {
    // The 'moved-from' object must be in valid state, so that it can be
    // correctly destructed.
    other.m_head = nullptr;
    other.m_length = 0;
  }

  // Move-assignment operator of Slist. (Not required in the homework problem)
  Slist &operator=(Slist &&other) noexcept {
    if (this != &other) {
      clear();
      m_head = other.m_head;
      m_length = other.m_length;
      other.m_head = nullptr;
      other.m_length = 0;
    }
    return *this;
  }

  // The destructor calls the helper function 's_delete_from'
  ~Slist() {
    s_delete_from(m_head);
  }

  void push_front(const value_type &value) {
    auto node = s_create_node(value, m_head);
    m_head = node;
    ++m_length;
  }

  void pop_front() {
    auto node = m_head;
    m_head = m_head->next;
    s_destroy_node(node);
    --m_length;
  }

  iterator insert_after(const_iterator pos, const value_type &value) {
    auto cur_node = pos.base();
    auto node = s_create_node(value, cur_node->next);
    cur_node->next = node;
    ++m_length;
    return iterator(node);
  }

  void erase_after(const_iterator pos) {
    auto cur_node = pos.base();
    auto next = cur_node->next;
    cur_node->next = next->next;
    s_destroy_node(next);
    --m_length;
  }

  size_type size() const {
    return m_length;
  }

  bool empty() const {
    return size() == 0;
  }

  void clear() {
    s_delete_from(m_head);
    m_head = nullptr;
    m_length = 0;
  }

  iterator begin() {
    return iterator(m_head);
  }

  iterator end() {
    return iterator(nullptr);
  }

  // The following two functions are needed, because we should be able to use
  // const_iterators to iterate a const object.
  const_iterator begin() const {
    return const_iterator(m_head);
  }

  const_iterator end() const {
    return const_iterator(nullptr);
  }

  // It was not until C++11 that cbegin and cend were added into the standard.
  const_iterator cbegin() const {
    return begin();
  }

  const_iterator cend() const {
    return end();
  }
};

template <typename T>
inline bool operator==(const Slist<T> &lhs, const Slist<T> &rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(lhs.begin(), lhs.end(), rhs.begin());
  // You may also use std::equal(lhs.begin(), lhs.end(), rhs.begin(),
  // rhs.end()).
}

template <typename T>
inline bool operator<(const Slist<T> &lhs, const Slist<T> &rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

template <typename T>
inline bool operator!=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline bool operator>(const Slist<T> &lhs, const Slist<T> &rhs) {
  return rhs < lhs;
}

template <typename T>
inline bool operator<=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
inline bool operator>=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs < rhs);
}

#endif // CS100_HW_SLIST_HPP