#include "gtest/gtest.h"
#include "al/murmur.h"

namespace {

// Note: See test/smhasher for verification 

TEST(AlMurmurTest, SameInputSameResult)
{
  std::string first("some-input-test");
  std::string second("some-input-test");

  uint32_t hash_first = al::murmur_32(
    reinterpret_cast<const uint32_t *>(first.c_str()),
    sizeof(first.c_str())
  );

  uint32_t hash_second = al::murmur_32(
    reinterpret_cast<const uint32_t *>(second.c_str()),
    sizeof(second.c_str())
  );

  EXPECT_EQ(hash_first, hash_second);

  uint32_t seed = 23235;
  uint32_t seeded_hash_first = al::murmur_32(
    reinterpret_cast<const uint32_t *>(first.c_str()),
    sizeof(first.c_str()),
    seed
  );

  uint32_t seeded_hash_second = al::murmur_32(
    reinterpret_cast<const uint32_t *>(second.c_str()),
    sizeof(second.c_str()),
    seed
  );

  EXPECT_EQ(seeded_hash_first, seeded_hash_second);
}

TEST(AlMurmurTest, DifferentInputDifferentResult)
{
  uint32_t first = 23;
  uint32_t second = 22;

  uint32_t hash_first = al::murmur_32(
    reinterpret_cast<uint32_t *>(&first),
    sizeof(first)
  );
  uint32_t hash_second = al::murmur_32(
    reinterpret_cast<uint32_t *>(&second),
    sizeof(second)
  );
  EXPECT_NE(hash_first, hash_second);
}

}

