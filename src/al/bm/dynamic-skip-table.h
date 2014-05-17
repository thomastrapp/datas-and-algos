#ifndef AL_BM_DYNAMIC_SKIP_TABLE_H
#define AL_BM_DYNAMIC_SKIP_TABLE_H

#include <unordered_map>

namespace al {
namespace bm {

template<
  typename key_type,
  typename value_type
>
class dynamic_skip_table
{
  public:
    dynamic_skip_table(size_t pattern_len, value_type default_val)
    : default_value(default_val),
      table(pattern_len)
    {
    }

    value_type get(key_type idx) const
    {
      auto iter = this->table.find(idx);
      if( iter != this->table.end() )
        return iter->second;
      else
        return this->default_value;
    }

    void set(key_type idx, value_type val)
    {
      this->table[idx] = val;
    }

  private:
    const value_type default_value;
    std::unordered_map<key_type, value_type> table;
};

}
}

#endif // AL_BM_DYNAMIC_SKIP_TABLE_H
