#include "event-handlers.hpp"

void telecom::handleClientArrival(ComputerClub & club, const Event & event)
{
  if (club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, 13, "", 0, "YouShallNotPass"});
    return;
  }

  if (event.time_ < club.getStart() || event.time_ >= club.getEnd())
  {
    club.addEvent(Event{event.time_, 13, "", 0, "NotOpenYet"});
    return;
  }

  club.addClient(event.name_);
}

void telecom::handleClientSit(ComputerClub & club, const Event & event)
{
  if (!club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, 13, "", 0, "ClientUnknown"});
    return;
  }

  if (!club.isTableFree(event.table_))
  {
    club.addEvent(Event{event.time_, 13, "", 0, "PlaceIsBusy"});
    return;
  }

  club.seatClientAtTable(event.name_, event.table_, event.time_);
}

void telecom::handleClientWait(ComputerClub & club, const Event & event)
{
  if (!club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, 13, "", 0, "ClientUnknown"});
    return;
  }

  if (club.getFreeTableNumber() != 0)
  {
    club.addEvent(Event{event.time_, 13, "", 0, "ICanWaitNoLonger!"});
    return;
  }

  if (club.getNumClientsInQueue() >= club.getNumTables())
  {
    club.addEvent(Event{event.time_, 11, event.name_, 0, ""});
    club.removeClient(event.name_, event.time_);
    return;
  }

  club.addToQueue(event.name_);
}

void telecom::handleClientLeave(ComputerClub & club, const Event & event)
{
  if (!club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, 13, "", 0, "ClientUnknown"});
    return;
  }

  club.removeClient(event.name_, event.time_);
}
