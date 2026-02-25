#ifndef EVENT_HANDLERS_HPP
#define EVENT_HANDLERS_HPP
#include "computer-club.hpp"

namespace telecom
{
  void handleClientArrival(ComputerClub & club, const Event & event);
  void handleClientSit(ComputerClub & club, const Event & event);
  void handleClientWait(ComputerClub & club, const Event & event);
  void handleClientLeave(ComputerClub & club, const Event & event);
}

#endif
