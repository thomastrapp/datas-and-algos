#ifndef DS_BLOOM_FILTER_H
#define DS_BLOOM_FILTER_H

/* 
 * A basic bloom filter.
 *
 * Uses al::murmur_128 as its hash function, which returns a 
 * std::pair containing two parts of a 128-bit hash.
 *
 * These two parts are used independently, as if they were 
 * separate hashes. This decreases the false-positive rate
 * significantly, compared to using only one hash.
 *
 */

#include <bitset>
#include <iterator>

#include "al/murmur.h"

namespace ds
{

template<
  typename value_type,
  size_t bitset_size
>
class bloom_filter
{
public:
  bloom_filter()
  : bits()
  {
  }

  void insert(const value_type& val)
  {
    auto hash_pair = al::murmur_128(&val, sizeof(value_type));

    this->bits.set(hash_pair.first % this->bits.size());
    this->bits.set(hash_pair.second % this->bits.size());
  }

  void insert(const value_type * begin, const value_type * end)
  {
    auto len = std::distance(begin, end);
    auto hash_pair = al::murmur_128(begin, len * sizeof(value_type));

    this->bits.set(hash_pair.first % this->bits.size());
    this->bits.set(hash_pair.second % this->bits.size());
  }

  bool maybe_contains(const value_type& val) const
  {
    auto hash_pair = al::murmur_128(&val, sizeof(value_type));
    
    return 
      this->bits.test(hash_pair.first % this->bits.size()) &&
      this->bits.test(hash_pair.second % this->bits.size())
    ;
  }

  bool maybe_contains(const value_type * begin, const value_type * end) const
  {
    auto len = std::distance(begin, end);
    auto hash_pair = al::murmur_128(begin, len * sizeof(value_type));

    return 
      this->bits.test(hash_pair.first % this->bits.size()) &&
      this->bits.test(hash_pair.second % this->bits.size())
    ;
  }

  const std::bitset<bitset_size>& data() const
  {
    return this->bits;
  }

private:
  std::bitset<bitset_size> bits;
};

}

#endif // DS_BLOOM_FILTER_H
