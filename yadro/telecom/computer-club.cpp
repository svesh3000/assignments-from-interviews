#include "computer-club.hpp"

#include <utility>
#include <vector>

#include "event-handlers.hpp"
#include "event.hpp"
#include "table.hpp"

namespace
{
  using Handler = void (*)(telecom::ComputerClub &, const telecom::Event &);
  const std::unordered_map< int, Handler > eventHandlers = {{1, telecom::handleClientArrival},
    {2, telecom::handleClientSit}, {3, telecom::handleClientWait}, {4, telecom::handleClientLeave}};

  std::vector< telecom::Table > createTables(int num_tables);

  std::ostream & printEvent(const telecom::Event & event, std::ostream & out);
  std::ostream & printTable(const telecom::Table & table, std::ostream & out);

  std::vector< telecom::Table > createTables(int num_tables)
  {
    using namespace telecom;

    std::vector< Table > tables;
    tables.reserve(num_tables);
    for (int i = 1; i <= num_tables; i++)
    {
      tables.emplace_back(i);
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
  clients_.emplace(client, 0);
}

bool telecom::ComputerClub::isClientInClub(const std::string & client) const
{
  return clients_.find(client) != clients_.end();
}

bool telecom::ComputerClub::isTableFree(int num) const
{
  return tables_[num - 1].isFree();
}

int telecom::ComputerClub::getFreeTableNumber() const
{
  for (int i = 0; i < tables_.size(); i++)
  {
    if (isTableFree(i + 1))
    {
      return i + 1;
    }
  }
  return 0;
}

void telecom::ComputerClub::seatClientAtTable(const std::string & client, int num, const Time & t)
{
  auto it = clients_.find(client);
  if (it == clients_.end())
  {
    return;
  }

  int oldTable = it->second;
  if (oldTable != 0)
  {
    tables_[oldTable - 1].endSession(t, cost_);
  }
  tables_[num - 1].startSession(t);
  it->second = num;
}

void telecom::ComputerClub::addToQueue(const std::string & client)
{
  waitig_queue_.push(client);
}

void telecom::ComputerClub::moveFromQueueToTable(int num, const Time & t)
{
  if (waitig_queue_.empty())
  {
    return;
  }
  std::string client = waitig_queue_.front();
  waitig_queue_.pop();

  seatClientAtTable(client, num, t);
  addEvent(Event{t, 12, client, num, ""});
}

int telecom::ComputerClub::removeClient(const std::string & client, const Time & t)
{
  auto it = clients_.find(client);
  if (it == clients_.end())
  {
    return 0;
  }

  int tableNum = it->second;
  if (tableNum != 0)
  {
    tables_[tableNum - 1].endSession(t, cost_);
    clients_.erase(it);

    if (!waitig_queue_.empty())
    {
      moveFromQueueToTable(tableNum, t);
    }
  }
  else
  {
    clients_.erase(it);
  }
  return tableNum;
}

void telecom::ComputerClub::close()
{
  std::vector< std::string > remaining;
  for (const auto & p : clients_)
  {
    remaining.push_back(p.first);
  }
  std::sort(remaining.begin(), remaining.end());

  for (const auto & name : remaining)
  {
    int table = clients_[name];
    if (table != 0)
    {
      tables_[table - 1].endSession(end_, cost_);
    }
    addEvent(Event{end_, 11, name, 0, ""});
  }
  clients_.clear();
  while (!waitig_queue_.empty())
  {
    waitig_queue_.pop();
  }
}

void telecom::ComputerClub::processEvent(const Event & ev)
{
  auto it = eventHandlers.find(ev.id_);
  if (it != eventHandlers.end())
  {
    it->second(*this, ev);
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
