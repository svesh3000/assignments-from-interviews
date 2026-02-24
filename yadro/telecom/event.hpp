#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>

#include "event-ids.hpp"
#include "time.hpp"

namespace telecom
{
  struct Event
  {
    Time time_;
    EventID id_;
    std::string name_;
    int table_ = 0;
    std::string err_;
  };
}

#endif
