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

#ifndef NUI_CORE_BASICS_VECTOR_TRICKS_H_
#define NUI_CORE_BASICS_VECTOR_TRICKS_H_

// IWYU pragma: private, include "nui/core/basics/basics.h"
// IWYU pragma: friend "nui/core/basics/.*\.h"

#include <algorithm>  // IWYU pragma: keep
#include <cstddef>    // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

namespace nui {

// Check if two vectors contain same elements in same order.
template <typename T>
bool AreVectorsEqual(const std::vector<T>& a, const std::vector<T>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (std::size_t i = 0; i < a.size(); i += 1) {
    if (a[i] != b[i]) {
      return false;
    }
  }

  return true;
}

// Check if vector contains unique elements.
template <typename T>
bool AreVectorElementsUnique(std::vector<T> a) {
  if (a.size() == 0) {
    return true;
  }
  std::sort(a.begin(), a.end());

  for (std::size_t i = 1; i < a.size(); i += 1) {
    if (a[i] == a[i - 1]) {
      return false;
    }
  }

  return true;
}

// Check if two vectors contain same elements (in arbitrary order).
template <typename T>
bool DoVectorsContainSameElements(
    const std::vector<T>& a,
    const std::vector<T>& b) {
  if (a.size() != b.size()) {
    return false;
  }

  std::vector<T> a_copy(a);
  std::vector<T> b_copy(b);
  std::sort(a_copy.begin(), a_copy.end());
  std::sort(b_copy.begin(), b_copy.end());

  return AreVectorsEqual(a_copy, b_copy);
}
}  // namespace nui

#endif  // NUI_CORE_BASICS_VECTOR_TRICKS_H_
