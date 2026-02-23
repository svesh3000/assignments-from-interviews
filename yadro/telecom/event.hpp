#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>

#include "time.hpp"

namespace telecom
{
  struct Event
  {
    Time time_;
    int id_;
    std::string name_;
    int table_ = 0;
    std::string err_;
  };
}

#endif
