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

#include "nui/core/indexing/macro.h"

#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"

#include "fmt/core.h"

#include "nui/core/indexing/indexing.h"

NUI_MAKE_INDEX_TYPE(TestIndex1);
NUI_MAKE_INDEX_TYPE(TestIndex2);

using nui::GenericIndex;
using nui::TestIndex1;
using nui::TestIndex2;

TEST_CASE("GenericIndex, Default ctor is 0.") {
  const GenericIndex i;
  REQUIRE(i == 0);
  REQUIRE(i == GenericIndex(0));
  REQUIRE(i.idx() == 0);
  REQUIRE(i != GenericIndex::Invalid());
}

TEST_CASE("TestIndex1, Default ctor is 0.") {
  const TestIndex1 i;
  REQUIRE(i == 0);
  REQUIRE(i == TestIndex1(0));
  REQUIRE(i.idx() == 0);
  REQUIRE(i != TestIndex1::Invalid());
}

TEST_CASE("TestIndex2, Default ctor is 0.") {
  const TestIndex2 i;
  REQUIRE(i == 0);
  REQUIRE(i == TestIndex2(0));
  REQUIRE(i.idx() == 0);
  REQUIRE(i != TestIndex2::Invalid());
}
