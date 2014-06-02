#ifndef AL_MURMUR_H
#define AL_MURMUR_H

#include <cstdint>
#include <utility>
#include <algorithm>

/* 
 * An implementation of murmur3 (32bit, 128bit) as invented by Austin Appleby.
 *
 * Assumes little endian.
 * Verified with smhasher; See test/smhasher.
 *
 * References:
 * - http://en.wikipedia.org/wiki/MurmurHash#Algorithm
 * - http://code.google.com/p/smhasher/
 *
 */

namespace al
{

uint32_t murmur_32(const uint32_t * data, size_t num_bytes, uint32_t seed = 0)
{
  // magic numbers
  const uint32_t m_constant_first = 0xcc9e2d51;
  const uint32_t m_constant_second = 0x1b873593;
  const uint32_t m_rotate_first = 15;
  const uint32_t m_rotate_second = 13;
  const uint32_t m_multiply = 5;
  const uint32_t m_add = 0xe6546b64;

  const size_t num_four_byte_blocks = num_bytes / 4;
  const size_t num_remaining_bytes = num_bytes % 4;

  uint32_t hash = seed;

  // for each four-byte-block in data
  for(size_t i = 0; i < num_four_byte_blocks; ++i)
  {
    // perform some magic tricks
    uint32_t block = data[i];
    block *= m_constant_first;
    block = (block << m_rotate_first) | (block >> (32 - m_rotate_first));
    block *= m_constant_second;

    hash ^= block;
    hash = (hash << m_rotate_second) | (hash >> (32 - m_rotate_second));
    hash = hash * m_multiply + m_add;
  }

  if( num_remaining_bytes )
  {
    // put all remaining bytes into a single four-byte-block
    const uint8_t * byte_wise = 
      reinterpret_cast<const uint8_t *>(data + num_four_byte_blocks);

    uint32_t remaining_block = 0;
    for(unsigned int i = 0; i < num_remaining_bytes; ++i)
    {
      remaining_block ^= 
        static_cast<const uint32_t>(byte_wise[i]) << i * 8;
    }

    // .. some more magic here ..
    remaining_block *= m_constant_first;
    remaining_block = 
      (remaining_block << m_rotate_first) | 
      (remaining_block >> (32 - m_rotate_first));
    remaining_block *= m_constant_second;

    hash ^= remaining_block;
  }

  // .. and some final magic
  hash ^= static_cast<uint32_t>(num_bytes);
  hash ^= ( hash >> 16 );
  hash *= 0x85ebca6b;
  hash ^= ( hash >> 13 );
  hash *= 0xc2b2ae35;
  hash ^= ( hash >> 16 );

  return hash;
}

std::pair<uint64_t, uint64_t> murmur_128(const uint64_t * data, size_t num_bytes, uint32_t seed = 0)
{
  const uint64_t m_constant1 = 0x87c37b91114253d5;
  const uint64_t m_constant2 = 0x4cf5ad432745937f;
  const uint64_t m_rotate1 = 31;
  const uint64_t m_rotate2 = 27;
  const uint64_t m_rotate3 = 33;
  const uint64_t m_rotate4 = 31;
  const uint64_t m_add_first = 0x52dce729;
  const uint64_t m_add_second = 0x38495ab5;

  const size_t num_chunks = num_bytes / 16;
  const unsigned int num_remaining_bytes = num_bytes % 16;

  uint64_t hash_high = seed;
  uint64_t hash_low = seed;

  for(size_t i = 0; i < num_chunks; ++i)
  {
    uint64_t block_high = *(data + i * 2);
    uint64_t block_low  = *(data + i * 2 + 1);

    block_high *= m_constant1;
    block_high  = (block_high << m_rotate1) | (block_high >> (64 - m_rotate1));
    block_high *= m_constant2;
    hash_high  ^= block_high;
    hash_high   = (hash_high << m_rotate2) | (hash_high >> (64 - m_rotate2));
    hash_high  += hash_low;
    hash_high   = hash_high * 5 + m_add_first;

    block_low *= m_constant2;
    block_low  = (block_low << m_rotate3) | (block_low >> (64 - m_rotate3));
    block_low *= m_constant1;
    hash_low  ^= block_low;
    hash_low   = (hash_low << m_rotate4) | (hash_low >> (64 - m_rotate4));
    hash_low  += hash_high;
    hash_low   = hash_low * 5 + m_add_second;
  }

  if( num_remaining_bytes )
  {
    const uint8_t * byte_wise =
      reinterpret_cast<const uint8_t *>(data + num_chunks * 2);

    const int first_half = std::min(8U, num_remaining_bytes);
    uint64_t r_block_high = 0;
    for(int i = 0; i < first_half; ++i)
    {
      r_block_high ^=
        static_cast<uint64_t>(byte_wise[i]) << i * 8;
    }

    r_block_high *= m_constant1;
    r_block_high =
      (r_block_high << m_rotate1) |
      (r_block_high >> (64 - m_rotate1));
    r_block_high *= m_constant2;
    hash_high ^= r_block_high;

    byte_wise += first_half;
    const int second_half = num_remaining_bytes - first_half;
    if( second_half > 0 )
    {
      uint64_t r_block_low = 0;
      for(int i = 0; i < second_half; ++i)
      {
        r_block_low ^=
          static_cast<uint64_t>(byte_wise[i]) << i * 8;
      }

      r_block_low *= m_constant2;
      r_block_low =
        (r_block_low << m_rotate3) |
        (r_block_low >> (64 - m_rotate3));
      r_block_low *= m_constant1;
      hash_low ^= r_block_low;
    }
  }

  hash_high ^= num_bytes;
  hash_low  ^= num_bytes;
  hash_high += hash_low;
  hash_low  += hash_high;

  hash_high ^= hash_high >> 33;
  hash_high *= 0xff51afd7ed558ccd;
  hash_high ^= hash_high >> 33;
  hash_high *= 0xc4ceb9fe1a85ec53;
  hash_high ^= hash_high >> 33;

  hash_low ^= hash_low >> 33;
  hash_low *= 0xff51afd7ed558ccd;
  hash_low ^= hash_low >> 33;
  hash_low *= 0xc4ceb9fe1a85ec53;
  hash_low ^= hash_low >> 33;

  hash_high += hash_low;
  hash_low  += hash_high;

  return std::make_pair(hash_high, hash_low);
}


}

#endif // AL_MURMUR_H
