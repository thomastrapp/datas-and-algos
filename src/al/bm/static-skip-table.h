#ifndef AL_BM_STATIC_SKIP_TABLE_H
#define AL_BM_STATIC_SKIP_TABLE_H

#include <array>

namespace al { 
namespace bm {

template<
  typename key_type,
  typename value_type
>
class static_skip_table
{
  public:
    static_skip_table(
      size_t, // pattern_len; preserve common skip table interface
      value_type default_value
    )
    : table()
    {
      this->table.fill(default_value);
    }

    value_type get(key_type idx) const
    {
      return this->table.at(idx);
    }

    void set(key_type idx, value_type val)
    {
      this->table.at(idx) = val;
    }

  private:
    std::array<
      value_type, 
      1U << (std::numeric_limits<unsigned char>::digits * sizeof(key_type))
    > table;
};

}
}

#endif // AL_BM_STATIC_SKIP_TABLE_H
