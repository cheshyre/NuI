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

#include "nui/core/indexing/conversion.h"

#include "catch2/catch_test_macros.hpp"

#include "nui/core/basics/basics.h"
#include "nui/core/indexing/indexing.h"

NUI_MAKE_INDEX_TYPE(IA);
NUI_MAKE_INDEX_TYPE(IB);

using nui::IA;
using nui::IB;

using Table = nui::IndexConversion<IA, IB>;
using InputVector = std::vector<IA>;

TEST_CASE("IndexConversion, Test default ctor.") {
  const Table table;

  REQUIRE(table.TableSize() == 0);
  REQUIRE(table.InputIndices().size() == 0);
  REQUIRE(table.MemoryLoad() == 0);
  REQUIRE(table.CheckInvariants());
}

TEST_CASE("IndexConversion, Test normal construction.") {
  const InputVector input = {1, 5, 8, 11};
  const Table table(input);

  REQUIRE(nui::AreVectorsEqual(table.InputIndices(), input));
  REQUIRE(table.TableSize() >= 12);
  REQUIRE(table.MemoryLoad() > 0);
}
