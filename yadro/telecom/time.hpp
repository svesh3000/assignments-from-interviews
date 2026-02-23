#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>

namespace telecom
{
  struct Time
  {
    int hours;
    int minutes;
  };

  std::istream & operator>>(std::istream & in, Time & t);
  std::ostream & operator<<(std::ostream & out, const Time & t);
}

#endif
