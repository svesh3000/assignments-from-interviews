#include "computer-club.hpp"

#include <utility>
#include <vector>

#include "event.hpp"
#include "table.hpp"

namespace
{
  std::vector< telecom::Table > createTables(int num_tables);

  std::ostream & printEvent(const telecom::Event & event, std::ostream & out);
  std::ostream & printTable(const telecom::Table & table, std::ostream & out);

  std::vector< telecom::Table > createTables(int num_tables)
  {
    using namespace telecom;

    std::vector< Table > tables;
    tables.reserve(num_tables);
    for (int i = 0; i < num_tables; i++)
    {
      tables[i] = Table(i);
    }
    return tables;
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

telecom::ComputerClub::ComputerClub(int num_tables, Time start, Time end, int cost):
  start_(start),
  end_(end),
  cost_(cost),
  tables_(createTables(num_tables)),
  clients_(),
  events_(),
  waitig_queue_()
{}

const telecom::Time & telecom::ComputerClub::getStart() const
{
  return start_;
}

const telecom::Time & telecom::ComputerClub::getEnd() const
{
  return end_;
}

const std::vector< telecom::Event > & telecom::ComputerClub::getEvents() const
{
  return events_;
}

const std::vector< telecom::Table > & telecom::ComputerClub::getTables() const
{
  return tables_;
}

void telecom::ComputerClub::addEvent(const Event & ev)
{
  events_.push_back(ev);
}

void telecom::ComputerClub::addClient(const std::string & client)
{
  int num_table = 0;
  clients_.insert(std::make_pair(client, num_table));
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
