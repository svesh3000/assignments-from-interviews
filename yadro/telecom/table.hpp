#ifndef TABLE_HPP
#define TABLE_HPP
#include "time.hpp"

namespace telecom
{
  class Table
  {
    Time time;
  };

  std::istream & operator>>(std::istream & in, Table & t);
  std::ostream & operator<<(std::ostream & out, const Table & t);
}

#endif
