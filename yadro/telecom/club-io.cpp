#include "club-io.hpp"

#include <sstream>

#include "event-handlers.hpp"
#include "event-ids.hpp"

namespace
{
  using Handler = void (*)(telecom::ComputerClub &, const telecom::Event &);
  using EvID = telecom::EventID;
  const std::unordered_map< EvID, Handler > handlers = {{EvID::CLIENT_ARRIVAL, telecom::handleClientArrival},
    {EvID::CLIENT_SIT, telecom::handleClientSit}, {EvID::CLIENT_WAIT, telecom::handleClientWait},
    {EvID::CLIENT_LEAVE, telecom::handleClientLeave}};

  bool parseEventLine(const std::string & line, telecom::Event & ev, std::string & errorLine);

  std::ostream & printEvent(const telecom::Event & event, std::ostream & out);
  std::ostream & printTable(const telecom::Table & table, std::ostream & out);

  bool parseEventLine(const std::string & line, telecom::Event & ev, std::string & errorLine)
  {
    std::istringstream iss(line);
    int id;
    if (!(iss >> ev.time_ >> id >> ev.name_))
    {
      ev.id_ = static_cast< telecom::EventID >(id);
      errorLine = line;
      return false;
    }
    iss >> std::ws;
    if (iss.peek() != EOF)
    {
      if (!(iss >> ev.table_))
      {
        errorLine = line;
        return false;
      }

      iss >> std::ws;
      if (iss.peek() != EOF)
      {
        errorLine = line;
        return false;
      }
    }
    return true;
  }

  void processSingleEvent(telecom::ComputerClub & club, const telecom::Event & ev)
  {
    auto it = handlers.find(ev.id_);
    if (it != handlers.end())
    {
      it->second(club, ev);
    }
  }

  std::ostream & printEvent(const telecom::Event & event, std::ostream & out)
  {
    out << event.time_ << ' ' << event.id_ << ' ';
    if (!event.err_.empty())
    {
      out << event.err_;
      return out;
    }
    out << event.name_;
    if (event.table_ != 0)
    {
      out << ' ' << event.table_;
    }
    return out;
  }

  std::ostream & printTable(const telecom::Table & table, std::ostream & out)
  {
    out << table.getNum() << ' ' << table.getRevenue() << ' ' << table.getSumTime();
    return out;
  }
}

std::ostream & telecom::printListEvents(const ComputerClub & comp_club, std::ostream & out)
{
  const std::vector< Event > events = comp_club.getEvents();

  if (!events.empty())
  {
    printEvent(events[0], out);
    for (size_t i = 1; i < events.size(); i++)
    {
      out << '\n';
      printEvent(events[i], out);
    }
  }

  return out;
}

std::ostream & telecom::printListTables(const ComputerClub & comp_club, std::ostream & out)
{
  const std::vector< Table > tables = comp_club.getTables();

  if (!tables.empty())
  {
    printTable(tables[0], out);
    for (size_t i = 1; i < tables.size(); i++)
    {
      out << '\n';
      printTable(tables[i], out);
    }
  }

  return out;
}
