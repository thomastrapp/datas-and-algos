#include "gtest/gtest.h"

#include "al/sort-and-count-inversions.h"

namespace {

TEST(AlSortAndCountTest, ZeroElements)
{
  std::vector<int> v;

  unsigned long inversions = 
    al::sort_and_count_inversions(v.begin(), v.end());

  EXPECT_EQ(0, v.size());
  EXPECT_EQ(0, inversions);
}

TEST(AlSortAndCountTest, OneElement)
{
  const int my_value = 23;
  std::vector<int> v {my_value};

  unsigned long inversions = 
    al::sort_and_count_inversions(v.begin(), v.end());

  EXPECT_EQ(my_value, v.back());
  EXPECT_EQ(1, v.size());
  EXPECT_EQ(0, inversions);
}

TEST(AlSortAndCountTest, TwoElements)
{
  std::vector<int> v = {99,66};

  unsigned long inversions = 
    al::sort_and_count_inversions(v.begin(), v.end());

  EXPECT_EQ(2, v.size());
  EXPECT_EQ(66, v.front());
  EXPECT_EQ(99, v.back());
  EXPECT_EQ(1, inversions);
}

TEST(AlSortAndCountTest, Duplicates)
{
  std::vector<int> v = {99,99,99};

  unsigned long inversions = 
    al::sort_and_count_inversions(v.begin(), v.end());

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(99, v.front());
  EXPECT_EQ(99, v.back());
  EXPECT_EQ(0, inversions);
}

TEST(AlSortAndCountTest, IntMax)
{
  int max = std::numeric_limits<int>::max();
  std::vector<int> v = {max,max-1,max-2};

  unsigned long inversions = 
    al::sort_and_count_inversions(v.begin(), v.end());

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(max-2, v.front());
  EXPECT_EQ(max, v.back());
  EXPECT_EQ(3, inversions);
}

TEST(AlSortAndCountTest, SortsValues)
{
  const size_t size = 12;

  int unsorted[size] = {12, 1, 15, 4, 15, 61, 2, 3, 4, 2, 1, 1};
  int sorted[size] = {1, 1, 1, 2, 2, 3, 4, 4, 12, 15, 15, 61};

  al::sort_and_count_inversions(unsorted, unsorted + size);

  EXPECT_EQ(0, std::memcmp(unsorted, sorted, size));
}

TEST(AlSortAndCountTest, TextbookExample)
{
  std::vector<int> v = {1,3,5,2,4,6};

  unsigned long inversions = 
    al::sort_and_count_inversions(v.begin(), v.end());

  EXPECT_EQ(3, inversions);
}

}

