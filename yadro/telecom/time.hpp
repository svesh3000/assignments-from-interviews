#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>

namespace telecom
{
  struct Time
  {
    int hours_;
    int minutes_;
  };

  Time operator+(const Time & lhs, const Time & rhs);
  Time countDuration(const Time & lhs, const Time & rhs);

  bool operator==(const Time & lhs, const Time & rhs);

  std::istream & operator>>(std::istream & in, Time & t);
  std::ostream & operator<<(std::ostream & out, const Time & t);
}

#endif
