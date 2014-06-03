#include "gtest/gtest.h"

#include "ds/bloom-filter.h"

namespace {


TEST(DsBloomFilterTest, OneBit)
{
  ds::bloom_filter<int, 1> bf;
  const int input = 65536;

  // empty filter: no false positives
  EXPECT_FALSE(bf.maybe_contains(input));

  bf.insert(input);
  EXPECT_TRUE(bf.maybe_contains(input));
}

TEST(DsBloomFilterTest, RemembersInputByValue)
{
  ds::bloom_filter<int, 1024> bf;
  const int step = 323;
  for(int i = 0; i < step * 300; i += step)
  {
    bf.insert(i);
    EXPECT_TRUE(bf.maybe_contains(i));
  }

  for(int i = 0; i < step * 300; i += step)
  {
    EXPECT_TRUE(bf.maybe_contains(i));
  }
}

TEST(DsBloomFilterTest, RemembersInputByValueRange)
{
  ds::bloom_filter<const char, 256> bf;

  const char* words[] = {
    "GNU", "GENERAL", "PUBLIC", "LICENSE", 
    "VERSION", "2", "JUNE", "1991",
    "COPYRIGHT", "C", "LICENSES"
  };

  for( const auto i : words )
  {
    bf.insert(i, i + strlen(i));
    EXPECT_TRUE(bf.maybe_contains(i, i + strlen(i)));
  }

  for( const auto i : words )
  {
    EXPECT_TRUE(bf.maybe_contains(i, i + strlen(i)));
  }
}


}

