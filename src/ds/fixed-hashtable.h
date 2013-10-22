#ifndef AL_HASHTABLE_H
#define AL_HASHTABLE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <boost/optional.hpp>

#include "al/murmur.h"


namespace ds
{

template<typename key_type, typename value_type>
class fixed_hashtable 
{
  typedef std::vector<std::pair<key_type, value_type>> bucket_type;
  typedef std::vector<bucket_type> table_type;

public:
  explicit fixed_hashtable(size_t size)
  : table(size)
  {
  }

  void set(const key_type& key, const value_type& value)
  {
    uint32_t hash = this->hash_f(key);
    auto& values = this->table.at(hash % this->table.size());
    values.push_back(std::make_pair(key, value));
  }

  boost::optional<value_type> get(const key_type& key) const
  {
    uint32_t hash = this->hash_f(key);
    const auto& values = this->table.at(hash % this->table.size());
    for(const auto& pair : values)
    {
      if( pair.first == key )
      {
        return boost::optional<value_type>(pair.second);
      }
    }

    return boost::optional<value_type>();
  }

private:
  uint32_t hash_f(const key_type& key) const
  {
    return al::murmur_32(
      reinterpret_cast<const uint32_t *>(&key), 
      sizeof(key), 
      0 /* seed */
    );
  }

  table_type table;
};

}

#endif // AL_HASHTABLE_H
