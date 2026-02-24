#ifndef EVENT_IDS_HPP
#define EVENT_IDS_HPP
#include <iostream>

namespace telecom
{

  enum class EventID : int
  {
    CLIENT_ARRIVAL = 1,
    CLIENT_SIT = 2,
    CLIENT_WAIT = 3,
    CLIENT_LEAVE = 4,
    CLIENT_FORCED_LEAVE = 11,
    CLIENT_SIT_FROM_QUEUE = 12,
    ERROR = 13
  };

  inline std::ostream & operator<<(std::ostream & os, EventID id)
  {
    return os << static_cast< int >(id);
  }
}

#endif
