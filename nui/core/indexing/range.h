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

#ifndef NUI_CORE_INDEXING_RANGE_H_
#define NUI_CORE_INDEXING_RANGE_H_

// IWYU pragma: private, include "nui/core/indexing/indexing.h"
// IWYU pragma: friend "nui/core/indexing/.*\.h"

#include "nui/core/basics/basics.h"

namespace nui {

template <typename Index>
class IndexRange {
 public:
  template <typename IteratorIndexType>
  class IndexRangeIterator {
    friend class IndexRange;

   public:
    IteratorIndexType operator*() const { return i_; }
    const IndexRangeIterator& operator++() {
      ++i_;
      return *this;
    }
    IndexRangeIterator operator++(int) {
      IndexRangeIterator copy(*this);
      ++i_;
      return copy;
    }

    bool operator==(const IndexRangeIterator& other) const {
      return i_ == other.i_;
    }
    bool operator!=(const IndexRangeIterator& other) const {
      return i_ != other.i_;
    }

   protected:
    explicit IndexRangeIterator(Index start) : i_(start.idx()) {}

   private:
    std::size_t i_ = 0UL;
  };

  // Construct empty range
  IndexRange() {}

  // Construct range of Index values from 0 to end - 1.
  explicit IndexRange(Index end) : start_(0), end_(end) {}

  // Construct range of Index values from start to end - 1.
  explicit IndexRange(Index start, Index end) : start_(start), end_(end) {}

  // Get beginning of range.
  IndexRangeIterator<Index> begin() const {
    return IndexRangeIterator<Index>(start_);
  }

  // Get end of range.
  IndexRangeIterator<Index> end() const {
    return IndexRangeIterator<Index>(end_);
  }

  // Swap two ranges.
  void swap(IndexRange<Index>& other) noexcept {
    using std::swap;
    swap(start_, other.start_);
    swap(end_, other.end_);
  }

 private:
  Index start_ = 0;
  Index end_ = 0;
};

// Swap two ranges.
template <typename Index>
void swap(IndexRange<Index>& a, IndexRange<Index>& b) noexcept {
  a.swap(b);
}
}  // namespace nui

#endif  // NUI_CORE_INDEXING_RANGE_H_
