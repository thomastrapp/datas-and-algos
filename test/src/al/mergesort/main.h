#include <cstring>
#include <algorithm>

#include "gtest/gtest.h"
#include "al/mergesort.h"
#include "data/random-number-array.h"

namespace {

TEST(AlMergesortTest, ZeroElements)
{
  std::vector<int> v;

  al::mergesort(v.begin(), v.end());

  EXPECT_EQ(0, v.size());
}

TEST(AlMergesortTest, OneElement)
{
  const int my_value = 23;
  std::vector<int> v {my_value};

  al::mergesort(v.begin(), v.end());

  EXPECT_EQ(my_value, v.back());
  EXPECT_EQ(1, v.size());
}

TEST(AlMergesortTest, TwoElements)
{
  std::vector<int> v = {99,66};
  al::mergesort(v.begin(), v.end());

  EXPECT_EQ(2, v.size());
  EXPECT_EQ(66, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlMergesortTest, ThreeElements)
{
  std::vector<int> v = {99,66,88};

  al::mergesort(v.begin(), v.end());

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(66, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlMergesortTest, Duplicates)
{
  std::vector<int> v = {99,99,99};

  al::mergesort(v.begin(), v.end());

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(99, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlMergesortTest, IntMax)
{
  int max = std::numeric_limits<int>::max();
  std::vector<int> v = {max,max-1,max-2};

  al::mergesort(v.begin(), v.end());

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(max-2, v.front());
  EXPECT_EQ(max, v.back());
}

TEST(AlMergesortTest, SortsValues)
{
  const size_t size = 12;

  int unsorted[size] = {12, 1, 15, 4, 15, 61, 2, 3, 4, 2, 1, 1};
  int sorted[size] = {1, 1, 1, 2, 2, 3, 4, 4, 12, 15, 15, 61};

  al::mergesort(unsorted, unsorted + size);

  EXPECT_EQ(0, std::memcmp(unsorted, sorted, sizeof(unsorted)));
}

TEST(AlMergesortTest, Sorts10kValues)
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

  al::mergesort(numbers.begin(), numbers.end());

  EXPECT_EQ(numbers.size(), numbers_sorted.size());
  EXPECT_TRUE(std::equal(numbers.begin(), numbers.end(), numbers_sorted.begin()));
  EXPECT_EQ(0, std::memcmp(numbers.data(), numbers_sorted.data(), numbers.size()));
}

}


