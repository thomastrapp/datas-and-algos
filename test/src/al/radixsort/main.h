#include <cstring>
#include <algorithm>

#include "gtest/gtest.h"
#include "al/radixsort.h"
#include "data/random-number-array.h"

namespace {

TEST(AlRadixsortText, ZeroElements)
{
  std::vector<unsigned int> v;

  al::radixsort(v);

  EXPECT_EQ(0, v.size());
}

TEST(AlRadixsortText, OneElement)
{
  const unsigned int my_value = 23;
  std::vector<unsigned int> v {my_value};

  al::radixsort(v);

  EXPECT_EQ(my_value, v.back());
  EXPECT_EQ(1, v.size());
}

TEST(AlRadixsortText, TwoElements)
{
  std::vector<unsigned int> v = {99,66};
  al::radixsort(v);

  EXPECT_EQ(2, v.size());
  EXPECT_EQ(66, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlRadixsortText, ThreeElements)
{
  std::vector<unsigned int> v = {99,66,88};

  al::radixsort(v);

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(66, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlRadixsortText, Duplicates)
{
  std::vector<unsigned int> v = {99,99,99};

  al::radixsort(v);

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(99, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlRadixsortText, IntMax)
{
  unsigned int max = std::numeric_limits<unsigned int>::max();
  std::vector<unsigned int> v = {max,max-1,max-2};

  al::radixsort(v);

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(max-2, v.front());
  EXPECT_EQ(max, v.back());
}

TEST(AlRadixsortText, SortsValues)
{
  std::vector<unsigned int> unsorted{12, 1, 15, 4, 15, 61, 2, 3, 4, 2, 1, 1};
  std::vector<unsigned int> sorted{1, 1, 1, 2, 2, 3, 4, 4, 12, 15, 15, 61};

  al::radixsort(unsorted);

  EXPECT_EQ(0, std::memcmp(unsorted.data(), sorted.data(), unsorted.size()));
}

TEST(AlRadixsortText, Sorts10kValues)
{
  // namespace data:
  // - random_numbers
  // - random_numbers_sorted: already sorted by std::sort 
  // (and pasted into random-number-array.h)
  
  using data::random_numbers;
  using data::random_numbers_sorted;

  std::vector<unsigned int> numbers(random_numbers);
  std::vector<unsigned int> numbers_sorted(random_numbers_sorted);

  ASSERT_EQ(numbers.size(), numbers_sorted.size());

  al::radixsort(numbers);

  EXPECT_EQ(numbers.size(), numbers_sorted.size());
  EXPECT_TRUE(std::equal(numbers.begin(), numbers.end(), numbers_sorted.begin()));
  EXPECT_EQ(0, std::memcmp(numbers.data(), numbers_sorted.data(), numbers.size()));
}

}

