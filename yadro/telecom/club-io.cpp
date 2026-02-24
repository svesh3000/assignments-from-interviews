#include "club-io.hpp"

#include <sstream>
#include <stdexcept>

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

  void processSingleEvent(telecom::ComputerClub & club, const telecom::Event & ev);

  std::ostream & printEvent(const telecom::Event & event, std::ostream & out);
  std::ostream & printTable(const telecom::Table & table, std::ostream & out);

  bool parseEventLine(const std::string & line, telecom::Event & ev, std::string & errorLine)
  {
    std::istringstream iss(line);

    int id;
    if (!(iss >> ev.time_ >> id >> ev.name_))
    {
      errorLine = line;
      return false;
    }
    ev.id_ = static_cast< telecom::EventID >(id);

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

std::pair< telecom::ComputerClub, std::string > telecom::processComputerClub(std::istream & in)
{
  std::string line;
  int num_tables;
  Time start, end;
  int cost;

  if (!std::getline(in, line) || line.empty())
  {
    return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), line};
  }

  try
  {
    num_tables = std::stoi(line);
    if (num_tables <= 0)
    {
      throw std::out_of_range("Number of tables is less than zero");
    }
  }
  catch (...)
  {
    return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), line};
  }
  if (!std::getline(in, line) || line.empty())
  {
    return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), line};
  }
  std::istringstream issTime(line);
  if (!(issTime >> start >> end))
  {
    return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), line};
  }

  if (!std::getline(in, line) || line.empty())
  {
    return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), line};
  }
  try
  {
    cost = std::stoi(line);
    if (cost <= 0)
    {
      throw std::out_of_range("Cost is less than zero");
    }
  }
  catch (...)
  {
    return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), line};
  }

  ComputerClub club(num_tables, start, end, cost);

  while (std::getline(in, line))
  {
    if (line.empty())
    {
      continue;
    }
    Event ev;
    std::string err_line;
    if (!parseEventLine(line, ev, err_line))
    {
      return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), err_line};
    }
    club.addEvent(ev);
    try
    {
      processSingleEvent(club, ev);
    }
    catch (...)
    {
      return {ComputerClub(0, Time{0, 0}, Time{0, 0}, 0), err_line};
    }
  }

  auto departed_clients = club.close();
  for (auto it = departed_clients.begin(); it != departed_clients.end(); ++it)
  {
    club.addEvent(Event{club.getEnd(), EventID::CLIENT_FORCED_LEAVE, it->first, 0, ""});
  }

  return {std::move(club), ""};
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
