#ifndef UTIL_PRINT_H
#define UTIL_PRINT_H

#include <iostream>

namespace util {

template<typename cont>
void print_container(const cont& container, std::ostream& out = std::cout)
{
  for(const auto& elem : container)
  {
    out << elem << "\n";
  }
}

}

#endif // UTIL_PRINT_H
