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

inline InputVector MakeInputVectorOfSize(std::size_t i) {
  InputVector vec;
  vec.reserve(i);

  for (const InputVector::value_type val :
       {162, 508, 896, 212, 70,  733, 805, 590, 934, 23,  149, 357, 521,
        397, 380, 712, 367, 332, 298, 725, 769, 404, 118, 400, 852, 426,
        642, 564, 871, 572, 5,   918, 11,  966, 996, 296, 486, 566, 952,
        487, 726, 600, 111, 144, 145, 363, 89,  217, 782, 779, 424, 156,
        626, 582, 284, 596, 471, 403, 358, 202, 336, 286, 228, 240, 721,
        651, 330, 266, 742, 516, 345, 375, 87,  201, 450, 37,  872, 931,
        682, 63,  806, 932, 847, 644, 466, 750, 423, 669, 10,  877, 910,
        674, 128, 880, 188, 965, 717, 813, 509, 874}) {
    if (vec.size() == i) {
      continue;
    }
    vec.push_back(val);
  }

  return vec;
}

TEST_CASE("IndexConversion, Test default ctor.") {
  const Table table;

  REQUIRE(table.TableSize() == 0);
  REQUIRE(table.InputIndices().size() == 0);
  REQUIRE(table.MemoryLoad() == 0);
  REQUIRE(table.CheckInvariants());
}

TEST_CASE("IndexConversion, Test normal construction (sorted).") {
  const InputVector input = {1, 5, 8, 11};
  const Table table(input);

  REQUIRE(nui::AreVectorsEqual(table.InputIndices(), input));
  REQUIRE(table.TableSize() >= 12);
  REQUIRE(table.MemoryLoad() > 0);
  REQUIRE(table.CheckInvariants());
}

TEST_CASE("IndexConversion, Test normal construction (unsorted).") {
  const InputVector input = {5, 1, 8, 11};
  const Table table(input);

  REQUIRE(nui::AreVectorsEqual(table.InputIndices(), input));
  REQUIRE(table.TableSize() >= 12);
  REQUIRE(table.MemoryLoad() > 0);
  REQUIRE(table.CheckInvariants());
}

TEST_CASE("IndexConversion, Test output indices.") {
  for (const std::size_t input_size : {4, 8, 24, 64}) {
    const auto input = MakeInputVectorOfSize(input_size);
    REQUIRE(input.size() == input_size);
    const Table table(input);

    IB loop_start = *table.OutputIndices().begin();
    IB loop_end = *table.OutputIndices().end();

    REQUIRE(loop_start == 0);
    REQUIRE(loop_end == input_size);

    std::size_t loop_counter = 0UL;
    for (const IB i : table.OutputIndices()) {
      REQUIRE(i == loop_counter);
      loop_counter += 1;
    }
    REQUIRE(loop_counter == input_size);
  }
}

TEST_CASE("IndexConversion, Test SourceIndex.") {
  for (const std::size_t input_size : {4, 8, 24, 64}) {
    const auto input = MakeInputVectorOfSize(input_size);
    REQUIRE(input.size() == input_size);
    const Table table(input);

    std::size_t loop_counter = 0UL;
    for (const IB i : table.OutputIndices()) {
      REQUIRE(table.SourceIndex(i) == input[loop_counter]);
      loop_counter += 1;
    }
  }
}

TEST_CASE("IndexConversion, Test SourceIndexSafe.") {
  SECTION("in safe range") {
    for (const std::size_t input_size : {4, 8, 24, 64}) {
      const auto input = MakeInputVectorOfSize(input_size);
      REQUIRE(input.size() == input_size);
      const Table table(input);

      std::size_t loop_counter = 0UL;
      for (const IB i : table.OutputIndices()) {
        REQUIRE(table.SourceIndexSafe(i) == input[loop_counter]);
        loop_counter += 1;
      }
    }
  }
  SECTION("in unsafe range") {
    for (const std::size_t input_size : {4, 8, 24, 64}) {
      const auto input = MakeInputVectorOfSize(input_size);
      REQUIRE(input.size() == input_size);
      const Table table(input);

      for (const IB i : {400, 600, 10000}) {
        REQUIRE(table.SourceIndexSafe(i) == IA::Invalid());
      }
    }
  }
}
