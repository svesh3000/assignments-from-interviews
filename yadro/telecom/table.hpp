#ifndef TABLE_HPP
#define TABLE_HPP
#include "time.hpp"

namespace telecom
{
  struct Table
  {
    int num_;
    int revenue_;
    Time last_start_;
    Time sum_time_;
  };
}

#endif
