#ifndef CS100_MEMCHECK_HPP
#define CS100_MEMCHECK_HPP

#include <cstdlib>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <unordered_set>

namespace memcheck {

namespace detail {

  // This allocator uses malloc() and free() to manage memory.
  template <typename Tp>
  class Mallocator {
   public:
    using value_type = Tp;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = Tp *;
    using reference = Tp &;
    using const_pointer = Tp const *;
    using const_reference = Tp const &;

    constexpr Mallocator() noexcept = default;
    constexpr Mallocator(const Mallocator &) noexcept = default;
    template <typename U>
    constexpr Mallocator(const Mallocator<U> &) noexcept {}
    ~Mallocator() = default;
    pointer address(reference x) const noexcept {
      return std::addressof(x);
    }
    const_pointer address(const_reference x) const noexcept {
      return std::addressof(x);
    }
    pointer allocate(size_type n) {
      auto ptr = std::malloc(n * sizeof(Tp));
      if (!ptr)
        throw std::bad_alloc{};
      return static_cast<pointer>(ptr);
    }
    void deallocate(pointer p, size_type) {
      std::free(p);
    }
    template <typename U, typename... Args>
    void construct(U *p, Args &&...args) noexcept(
        std::is_nothrow_constructible<U, Args...>::value) {
      new (static_cast<void *>(p)) U(std::forward<Args>(args)...);
    }
    template <typename U>
    void destroy(U *p) noexcept(std::is_nothrow_destructible<U>::value) {
      p->~U();
    }
    constexpr size_type max_size() const noexcept {
#if PTRDIFF_MAX < SIZE_MAX
      return std::size_t(PTRDIFF_MAX) / sizeof(Tp);
#else
      return std::size_t(-1) / sizeof(Tp);
#endif
    }
  };

  std::unordered_set<void *, std::hash<void *>, std::equal_to<void *>,
                     Mallocator<void *>>
      new_recorder, array_recorder;

} // namespace detail

inline bool all_deallocated() {
  return detail::new_recorder.empty() && detail::array_recorder.empty();
}

inline void add_new(void *ptr) {
  detail::new_recorder.insert(ptr);
}

inline void add_new_array(void *ptr) {
  detail::array_recorder.insert(ptr);
}

inline void remove_new(void *ptr) {
  detail::new_recorder.erase(ptr);
}

inline void remove_new_array(void *ptr) {
  detail::array_recorder.erase(ptr);
}

} // namespace memcheck

void *operator new(std::size_t size) {
  if (size == 0)
    size = 1;
  while (true) {
    auto ptr = std::malloc(size);
    if (ptr) {
      memcheck::add_new(ptr);
      return ptr;
    }
    auto global_handler = std::get_new_handler();
    if (global_handler)
      global_handler();
    else
      throw std::bad_alloc{};
  }
}

void *operator new[](std::size_t size) {
  if (size == 0)
    size = 1;
  while (true) {
    auto ptr = std::malloc(size);
    if (ptr) {
      memcheck::add_new_array(ptr);
      return ptr;
    }
    auto global_handler = std::get_new_handler();
    if (global_handler)
      global_handler();
    else
      throw std::bad_alloc{};
  }
}

void *operator new(std::size_t size, const std::nothrow_t &) noexcept {
  if (size == 0)
    size = 1;
  auto ptr = std::malloc(size);
  if (ptr)
    memcheck::add_new(ptr);
  return ptr;
}

void *operator new[](std::size_t size, const std::nothrow_t &) noexcept {
  if (size == 0)
    size = 1;
  auto ptr = std::malloc(size);
  if (ptr)
    memcheck::add_new_array(ptr);
  return ptr;
}

void operator delete(void *ptr) noexcept {
  if (!ptr)
    return;
  memcheck::remove_new(ptr);
  free(ptr);
}

void operator delete[](void *ptr) noexcept {
  if (!ptr)
    return;
  memcheck::remove_new_array(ptr);
  free(ptr);
}

void operator delete(void *ptr, const std::nothrow_t &) noexcept {
  ::operator delete(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t &) noexcept {
  ::operator delete[](ptr);
}

// C++14 sized-deallocation
#if __cpp_sized_deallocation
void operator delete(void *ptr, std::size_t) noexcept {
  ::operator delete(ptr);
}
void operator delete[](void *ptr, std::size_t) noexcept {
  ::operator delete[](ptr);
}
#endif

#endif // CS100_MEMCHECK_HPP
