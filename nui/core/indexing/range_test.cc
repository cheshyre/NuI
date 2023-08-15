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

#include "nui/core/indexing/range.h"

#include "catch2/catch_template_test_macros.hpp"
#include "catch2/catch_test_macros.hpp"

#include "nui/core/basics/basics.h"
#include "nui/core/indexing/indexing.h"

NUI_MAKE_INDEX_TYPE(IA);
NUI_MAKE_INDEX_TYPE(IB);

using nui::IA;
using nui::IB;
using nui::IndexRange;

TEMPLATE_TEST_CASE(
    "IndexRange, Test default ctor.",
    "[IndexRange][template]",
    IA,
    IB) {
  IndexRange<TestType> range;

  REQUIRE(range.begin() == range.end());
  REQUIRE(*range.begin() == 0);
}

TEMPLATE_TEST_CASE(
    "IndexRange, Test end only range ctor.",
    "[IndexRange][template]",
    IA,
    IB) {
  for (TestType end_val : {4, 8, 12}) {
    std::size_t loop_counter = 0UL;
    for (const auto i : IndexRange(end_val)) {
      REQUIRE(i == loop_counter);
      loop_counter += 1;
    }
    REQUIRE(loop_counter == end_val);
  }
}

TEMPLATE_TEST_CASE(
    "IndexRange, Test start and end range ctor.",
    "[IndexRange][template]",
    IA,
    IB) {
  for (TestType start_val : {0, 1, 2, 3}) {
    for (TestType end_val : {4, 8, 12}) {
      std::size_t loop_counter = 0UL;
      for (const auto i : IndexRange(start_val, end_val)) {
        REQUIRE(i == loop_counter + start_val);
        loop_counter += 1;
      }
      REQUIRE(loop_counter + start_val == end_val);
    }
  }
}

TEMPLATE_TEST_CASE(
    "IndexRange, Test nested start and end range ctor.",
    "[IndexRange][template]",
    IA,
    IB) {
  for (TestType start_val : {0, 1, 2, 3}) {
    for (TestType end_val : {4, 8, 12}) {
      std::size_t loop_counter = 0UL;
      for (const auto i : IndexRange(start_val, end_val)) {
        std::size_t inner_loop_counter = 0UL;
        for (const auto j : IndexRange(start_val, end_val)) {
          REQUIRE(j == inner_loop_counter + start_val);
          inner_loop_counter += 1;
        }
        REQUIRE(inner_loop_counter + start_val == end_val);
        REQUIRE(i == loop_counter + start_val);
        loop_counter += 1;
      }
      REQUIRE(loop_counter + start_val == end_val);
    }
  }
}
