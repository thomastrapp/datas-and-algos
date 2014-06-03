#include "gtest/gtest.h"
#include "al/murmur.h"

namespace {

// Note: See test/smhasher for verification 

TEST(AlMurmurTest, SameInputSameResult)
{
  const char * first = "some-input-test";
  const char * second = "some-input-test"
    "-force-duplicate";

  auto hash_first = al::murmur_32(
    first,
    strlen(first)
  );
  auto hash_second = al::murmur_32(
    second,
    strlen(first)
  );
  EXPECT_EQ(hash_first, hash_second);
  auto hash_first_128 = al::murmur_128(
    first,
    strlen(first)
  );
  auto hash_second_128 = al::murmur_128(
    second,
    strlen(first)
  );
  EXPECT_EQ(hash_first_128, hash_second_128);

  uint32_t seed = 23235;
  auto seeded_hash_first = al::murmur_32(
    first,
    strlen(first),
    seed
  );
  auto seeded_hash_second = al::murmur_32(
    second,
    strlen(first),
    seed
  );
  EXPECT_EQ(seeded_hash_first, seeded_hash_second);
  auto seeded_hash_first_128 = al::murmur_128(
    first,
    strlen(first),
    seed
  );
  auto seeded_hash_second_128 = al::murmur_128(
    second,
    strlen(first),
    seed
  );
  EXPECT_EQ(seeded_hash_first_128, seeded_hash_second_128);
}

TEST(AlMurmurTest, DifferentInputDifferentResult)
{
  uint32_t first = 23;
  uint32_t second = 22;

  auto hash_first = al::murmur_32(
    &first,
    sizeof(first)
  );
  auto hash_second = al::murmur_32(
    &second,
    sizeof(second)
  );
  EXPECT_NE(hash_first, hash_second);
  auto hash_first_128 = al::murmur_128(
    &first,
    sizeof(first)
  );
  auto hash_second_128 = al::murmur_128(
    &second,
    sizeof(second)
  );
  EXPECT_NE(hash_first_128, hash_second_128);
}

TEST(AlMurmurTest, EmptySequenceReturnsZero)
{
  auto hash = al::murmur_32(nullptr, 0);
  EXPECT_EQ(hash, 0);

  auto hash_pair = al::murmur_128(nullptr, 0);
  EXPECT_EQ(hash_pair.first, 0);
  EXPECT_EQ(hash_pair.second, 0);
}


}

