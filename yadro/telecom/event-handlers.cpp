#include "event-handlers.hpp"

#include <stdexcept>

#include "event-errors.hpp"
#include "event-ids.hpp"

namespace
{
  void checkNoTable(const telecom::Event & event)
  {
    if (event.table_ != 0)
    {
      throw std::invalid_argument("Incorrect event data format: unexpected table number");
    }
  }
  void checkNoError(const telecom::Event & event)
  {
    if (!event.err_.empty())
    {
      throw std::invalid_argument("Incorrect event data format: unexpected error message");
    }
  }
}

void telecom::handleClientArrival(ComputerClub & club, const Event & event)
{
  checkNoTable(event);
  checkNoError(event);

  if (club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::YouShallNotPass});
    return;
  }

  if (event.time_ < club.getStart() || event.time_ >= club.getEnd())
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::NotOpenYet});
    return;
  }

  club.addClient(event.name_);
}

void telecom::handleClientSit(ComputerClub & club, const Event & event)
{
  checkNoError(event);

  if (!club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::ClientUnknown});
    return;
  }

  if (!club.isTableFree(event.table_))
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::PlaceIsBusy});
    return;
  }

  int old_table = club.getClientTable(event.name_);
  club.seatClientAtTable(event.name_, event.table_, event.time_);
  if (old_table != 0 && old_table != event.table_ && !club.isQueueEmpty())
  {
    std::string next = club.moveFromQueueToTable(old_table, event.time_);
    if (!next.empty())
    {
      club.addEvent(Event{event.time_, EventID::CLIENT_SIT_FROM_QUEUE, next, old_table, ""});
    }
  }
}

void telecom::handleClientWait(ComputerClub & club, const Event & event)
{
  checkNoTable(event);
  checkNoError(event);

  if (!club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::ClientUnknown});
    return;
  }

  if (club.getFreeTableNumber() != 0)
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::ICanWaitNoLonger});
    return;
  }

  if (club.getNumClientsInQueue() >= club.getNumTables())
  {
    club.addEvent(Event{event.time_, EventID::CLIENT_FORCED_LEAVE, event.name_, 0, ""});
    club.removeClient(event.name_, event.time_);
    return;
  }

  club.addToQueue(event.name_);
}

void telecom::handleClientLeave(ComputerClub & club, const Event & event)
{
  checkNoTable(event);
  checkNoError(event);

  if (!club.isClientInClub(event.name_))
  {
    club.addEvent(Event{event.time_, EventID::ERROR, "", 0, ErrMsg::ClientUnknown});
    return;
  }

  int free_table = club.removeClient(event.name_, event.time_);
  if (free_table != 0 && !club.isQueueEmpty())
  {
    std::string next = club.moveFromQueueToTable(free_table, event.time_);
    if (!next.empty())
    {
      club.addEvent(Event{event.time_, EventID::CLIENT_SIT_FROM_QUEUE, next, free_table, ""});
    }
  }
}
