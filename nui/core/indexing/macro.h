// MIT License
//
// Copyright (c) 2023 Matthias Heinz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef NUI_CORE_INDEXING_MACRO_H_
#define NUI_CORE_INDEXING_MACRO_H_

#include "nui/core/basics/basics.h"

// IWYU pragma: private, include "nui/core/indexing/indexing.h"
// IWYU pragma: friend "nui/core/indexing/.*\.h"

// This is a huge macro to create an index type.
//
// The goal of these index types is to have unique, incompatible index types
// that all still have nice features out of the box. We can use these to create
// indices that reflect very specific use-cases and can be transformed into
// other indices via explicit function calls.
//
// The features supported by an index type created like this are:
// - Tombstone Invalid() for invalid values.
// - Default construction to 0.
// - Implicit construction from size_t.
// - Explicit conversion to size_t via idx().
// - In-place and generic addition with itself (also implicitly size_t).
// - Swap (member and nonmember).
// - Full set of comparisons.
// - Formatting via fmt/spdlog in the style of size_t/integers.
//
// The correct use of the macro is illustrated by GenericIndex below:
//
// namespace nui {
// class GenericIndex;
// }
// // Docstrings here...
// NUI_MAKE_INDEX_TYPE(GenericIndex);
//
// NOTE: These types are not implicitly convertible to size_t to avoid problems
// with ambiguous overloads. This has the nice side effect that (even though
// double implcit conversion is not allowed) there is now no way for 2 of such
// index types to be accidentally converted into eachother.
#define NUI_MAKE_INDEX_TYPE(IndexType)                                        \
  namespace nui {                                                             \
  class IndexType {                                                           \
   public:                                                                    \
    /* Tombstone for invalid indices. */                                      \
    constexpr static IndexType Invalid() noexcept { return SIZE_MAX; }        \
    /* Default ctor initializes to value 0. */                                \
    constexpr IndexType() noexcept {}                                         \
    /* Standard ctor from size_t index. */                                    \
    constexpr IndexType(std::size_t i) noexcept /* NOLINT(runtime/explicit)*/ \
        : i_(i) {}                                                            \
    /* Explicitly get size_t index. */                                        \
    constexpr std::size_t idx() const noexcept { return i_; }                 \
    /* Increment index in place by other index. */                            \
    IndexType& operator+=(IndexType other) noexcept {                         \
      i_ += other.i_;                                                         \
      return *this;                                                           \
    }                                                                         \
    /* Swap with other index. */                                              \
    void swap(IndexType& other) noexcept {                                    \
      using std::swap;                                                        \
      swap(i_, other.i_);                                                     \
    }                                                                         \
                                                                              \
   private:                                                                   \
    std::size_t i_ = 0UL;                                                     \
  };                                                                          \
  /* Swap two indices. */                                                     \
  inline void swap(IndexType& a, IndexType& b) noexcept { a.swap(b); }        \
  /* Add two indices. */                                                      \
  constexpr inline IndexType operator+(IndexType a, IndexType b) noexcept {   \
    return a.idx() + b.idx();                                                 \
  }                                                                           \
  /* Compare two indices. */                                                  \
  constexpr inline bool operator<(IndexType a, IndexType b) noexcept {        \
    return a.idx() < b.idx();                                                 \
  }                                                                           \
  /* Compare two indices. */                                                  \
  constexpr inline bool operator>(IndexType a, IndexType b) noexcept {        \
    return a.idx() > b.idx();                                                 \
  }                                                                           \
  /* Compare two indices. */                                                  \
  constexpr inline bool operator<=(IndexType a, IndexType b) noexcept {       \
    return a.idx() <= b.idx();                                                \
  }                                                                           \
  /* Compare two indices. */                                                  \
  constexpr inline bool operator>=(IndexType a, IndexType b) noexcept {       \
    return a.idx() >= b.idx();                                                \
  }                                                                           \
  /* Compare two indices. */                                                  \
  constexpr inline bool operator==(IndexType a, IndexType b) noexcept {       \
    return a.idx() == b.idx();                                                \
  }                                                                           \
  /* Compare two indices. */                                                  \
  constexpr inline bool operator!=(IndexType a, IndexType b) noexcept {       \
    return a.idx() != b.idx();                                                \
  }                                                                           \
  } /* namespace nui */                                                       \
  /* Indices are formatable like size_t or int. */                            \
  template <>                                                                 \
  struct fmt::formatter<nui::IndexType> : fmt::formatter<std::size_t> {       \
    auto format(const nui::IndexType& a, format_context& ctx) const {         \
      return fmt::formatter<std::size_t>::format(a.idx(), ctx);               \
    }                                                                         \
  };

namespace nui {
class GenericIndex;
}  // namespace nui

// A generic index that is not to be used for anything useful.
NUI_MAKE_INDEX_TYPE(GenericIndex);

#endif  // NUI_CORE_INDEXING_MACRO_H_
