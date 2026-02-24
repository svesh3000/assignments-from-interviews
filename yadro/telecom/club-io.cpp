#include "club-io.hpp"

#include <sstream>

#include "event-handlers.hpp"

namespace
{
  using Handler = void (*)(telecom::ComputerClub &, const telecom::Event &);
  const std::unordered_map< int, Handler > handlers = {{1, telecom::handleClientArrival},
    {2, telecom::handleClientSit}, {3, telecom::handleClientWait}, {4, telecom::handleClientLeave}};

  bool parseEventLine(const std::string & line, telecom::Event & ev, std::string & errorLine);

  std::ostream & printEvent(const telecom::Event & event, std::ostream & out);
  std::ostream & printTable(const telecom::Table & table, std::ostream & out);

  bool parseEventLine(const std::string & line, telecom::Event & ev, std::string & errorLine)
  {
    std::istringstream iss(line);
    if (!(iss >> ev.time_ >> ev.id_ >> ev.name_))
    {
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
