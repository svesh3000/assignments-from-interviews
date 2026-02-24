#include "computer-club.hpp"

#include <utility>
#include <vector>

#include "event.hpp"
#include "table.hpp"

namespace
{
  std::vector< telecom::Table > createTables(int num_tables);
  void checkTableNumber(int num);

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

  void checkTableNumber(int num, int max_num)
  {
    if (num < 1 || num > max_num)
    {
      throw std::out_of_range("Invalid table number");
    }
  }
}

telecom::ComputerClub::ComputerClub(int num_tables, Time start, Time end, int cost):
  start_(start),
  end_(end),
  cost_(cost),
  tables_(createTables(num_tables)),
  clients_(),
  events_(),
  waiting_queue_()
{}

const telecom::Time & telecom::ComputerClub::getStart() const noexcept
{
  return start_;
}

const telecom::Time & telecom::ComputerClub::getEnd() const noexcept
{
  return end_;
}

const std::vector< telecom::Event > & telecom::ComputerClub::getEvents() const noexcept
{
  return events_;
}

const std::vector< telecom::Table > & telecom::ComputerClub::getTables() const noexcept
{
  return tables_;
}

size_t telecom::ComputerClub::getNumTables() const noexcept
{
  return tables_.size();
}

size_t telecom::ComputerClub::getNumClientsInQueue() const noexcept
{
  return waiting_queue_.size();
}

void telecom::ComputerClub::addEvent(const Event & ev)
{
  events_.push_back(ev);
}

void telecom::ComputerClub::addClient(const std::string & client)
{
  clients_.emplace(client, 0);
}

bool telecom::ComputerClub::isClientInClub(const std::string & client) const noexcept
{
  return clients_.find(client) != clients_.end();
}

bool telecom::ComputerClub::isTableFree(int num) const
{
  checkTableNumber(num, static_cast< int >(tables_.size()));
  return tables_[num - 1].isFree();
}

int telecom::ComputerClub::getFreeTableNumber() const noexcept
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
  checkTableNumber(num, static_cast< int >(tables_.size()));

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
  waiting_queue_.push(client);
}

void telecom::ComputerClub::moveFromQueueToTable(int num, const Time & t)
{
  checkTableNumber(num, static_cast< int >(tables_.size()));

  if (waiting_queue_.empty())
  {
    return;
  }
  std::string client = waiting_queue_.front();
  waiting_queue_.pop();

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

    if (!waiting_queue_.empty())
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
  while (!waiting_queue_.empty())
  {
    waiting_queue_.pop();
  }
}
