#ifndef UTIL_MAKE_UNIQUE_H
#define UTIL_MAKE_UNIQUE_H

#include <memory>
#include <utility>

namespace util
{


template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


}

#endif // UTIL_MAKE_UNIQUE_H
