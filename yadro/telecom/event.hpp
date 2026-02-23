#ifndef EVENT_HPP
#define EVENT_HPP
#include "time.hpp"

namespace telecom
{
  struct Event
  {
    Time time;
  };

  std::istream & operator>>(std::istream & in, Event & ev);
  std::ostream & operator<<(std::ostream & out, const Event & ev);
}

#endif
