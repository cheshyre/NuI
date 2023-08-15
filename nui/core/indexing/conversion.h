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

#ifndef NUI_CORE_INDEXING_CONVERSION_H_
#define NUI_CORE_INDEXING_CONVERSION_H_

// IWYU pragma: private, include "nui/core/indexing/indexing.h"
// IWYU pragma: friend "nui/core/indexing/.*\.h"

#include "nui/core/basics/basics.h"
#include "nui/core/indexing/range.h"

namespace nui {

template <typename IndexIn, typename IndexOut>
class IndexConversion {
 private:
  static IndexIn GetIndexUpperBound(const std::vector<IndexIn>& indices) {
    if (indices.size() == 0) {
      return IndexIn();
    }
    return *std::max_element(indices.begin(), indices.end()) + 1;
  }

  static std::vector<IndexOut> MakeLookupTable(
      const std::vector<IndexIn>& indices,
      IndexIn lim) {
    std::vector<IndexOut> lookup(lim.idx(), IndexOut::Invalid());

    for (std::size_t i_idx = 0; i_idx < indices.size(); i_idx += 1) {
      // This condition should always be met.
      if (indices[i_idx] < lim) {
        lookup[indices[i_idx].idx()] = IndexOut(i_idx);
      }
    }

    return lookup;
  }

 public:
  // Construct empty conversion table.
  IndexConversion() {}

  // Construct conversion table for indices.
  explicit IndexConversion(const std::vector<IndexIn>& indices)
      : indices_(indices) {}

  // Construct conversion table for indices.
  explicit IndexConversion(std::vector<IndexIn>&& indices)
      : indices_(std::move(indices)) {}

  // Construct conversion table for indices with max_val provided for table
  // size.
  //
  // If max_val is too small to hold all indices, it is ignored.
  explicit IndexConversion(const std::vector<IndexIn>& indices, IndexIn max_val)
      : indices_(indices),
        lim_(std::max(max_val + 1, GetIndexUpperBound(indices))) {}

  // Construct conversion table for indices with max_val provided for table
  // size.
  //
  // If max_val is too small to hold all indices, it is ignored.
  explicit IndexConversion(std::vector<IndexIn>&& indices, IndexIn max_val)
      : indices_(std::move(indices)),
        lim_(std::max(max_val + 1, GetIndexUpperBound(indices))) {}

  // Get size of table.
  IndexIn TableSize() const { return lim_; }

  // Get reference to indices.
  const std::vector<IndexIn>& InputIndices() const { return indices_; }

  // Get range of out indices.
  IndexRange<IndexOut> OutputIndices() const {
    return IndexRange<IndexOut>(indices_.size());
  }

  // Get input index corresponding to output index.
  IndexIn SourceIndex(IndexOut out) const { return indices_[out.idx()]; }

  // Get input index corresponding to output index.
  //
  // Performs a safe bounds check and returns IndexIn::Invalid() if not
  // fulfilled.
  IndexIn SourceIndexSafe(IndexOut out) const {
    if (out >= indices_.size()) {
      return IndexIn::Invalid();
    }
    return SourceIndex(out);
  }

  // Convert input index to output.
  //
  // Invalid conversions will be == IndexOut::Invalid().
  // If in >= TableSize(), this will probably segfault.
  IndexOut Convert(IndexIn in) const { return lookup_table_[in.idx()]; }

  // Convert input index to output.
  //
  // Invalid conversions will be == IndexOut::Invalid().
  // This performs a safe bounds check.
  IndexOut ConvertSafe(IndexIn in) const {
    if (in < TableSize()) {
      return Convert(in);
    }
    return IndexOut::Invalid();
  }

  // Check if input index is valid in conversion table.
  //
  // If in >= TableSize(), this will probably segfault.
  int IsValid(IndexIn in) const {
    return lookup_table_[in.idx()] != IndexOut::Invalid();
  }

  // Check if input index is valid in conversion table.
  //
  // This performs a safe bounds check.
  int IsValidSafe(IndexIn in) const {
    if (in < TableSize()) {
      return IsValid(in);
    }
    return 0;
  }

  // Check that indices are unique.
  bool AreIndicesUnique() const {
    std::size_t valid_count = 0UL;
    for (const auto& x : lookup_table_) {
      if (x != IndexOut::Invalid()) {
        valid_count += 1;
      }
    }
    return indices_.size() == valid_count;
  }

  // Check that lookups actually correspond to correct indices.
  bool AreLookupsCorrect() const {
    bool correct = true;
    for (std::size_t i_in = 0; i_in < indices_.size(); i_in += 1) {
      if (lookup_table_[indices_[i_in].idx()] != i_in) {
        correct = false;
      }
    }
    return correct;
  }

  // Check that invariants among data members are fulfilled.
  bool CheckInvariants() const {
    return AreIndicesUnique() && AreLookupsCorrect() &&
           (TableSize() == lookup_table_.size());
  }

  // Get size of table in dynamic memory.
  std::size_t MemoryLoad() const {
    return indices_.size() * sizeof(IndexIn) +
           lookup_table_.size() * sizeof(IndexOut);
  }

  // Swap with other table.
  void swap(IndexConversion<IndexIn, IndexOut>& other) noexcept {
    using std::swap;
    swap(indices_, other.indices_);
    swap(lim_, other.lim_);
    swap(lookup_table_, other.lookup_table_);
  }

 private:
  std::vector<IndexIn> indices_;
  IndexIn lim_ = GetIndexUpperBound(indices_);
  std::vector<IndexOut> lookup_table_ = MakeLookupTable(indices_, lim_);
};

// Swap two conversion tables.
template <typename IndexIn, typename IndexOut>
void swap(
    IndexConversion<IndexIn, IndexOut>& a,
    IndexConversion<IndexIn, IndexOut>& b) noexcept {
  a.swap(b);
}

}  // namespace nui

#endif  // NUI_CORE_INDEXING_CONVERSION_H_
