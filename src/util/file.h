#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <fstream>
#include <iostream>

namespace util
{

template<typename cont>
bool push_integer_file_to_container(const char * file, cont& container)
{
  std::ifstream f(file);

  if( !f.is_open() )
  {
    std::cout << "cannot open file for reading" << std::endl;
    return false;
  }

  typename cont::value_type num = 0;
  while( f.good() )
  {
    if( f >> num )
      container.push_back(num);
  }

  f.close();

  return true;
}

}

#endif // UTIL_FILE_H
