#include "computer-club.hpp"

#include <vector>

namespace
{
  std::ostream & printEvent(const telecom::Event & event, std::ostream & out);
  std::ostream & printTable(const telecom::Table & table, std::ostream & out);

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
    out << table.num_ << ' ' << table.revenue_ << ' ' << table.sum_time_;
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
