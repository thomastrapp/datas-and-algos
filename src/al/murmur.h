#ifndef AL_MURMUR_H
#define AL_MURMUR_H

#include <cstdint>

/* 
 * An implementation of murmur3 (32bit) as invented by Austin Appleby.
 *
 * Assumes little endian.
 * Verified with smhasher.
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

  if( num_remaining_bytes != 0 )
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


}

#endif // AL_MURMUR_H
