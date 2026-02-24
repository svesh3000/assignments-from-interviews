#ifndef COMPUTER_CLUB_HPP
#define COMPUTER_CLUB_HPP
#include <queue>
#include <vector>

#include "event.hpp"
#include "table.hpp"

#include <unordered_map>

namespace telecom
{
  class ComputerClub
  {
  public:
    ComputerClub(int num_tables, Time start, Time end, int cost);

    const Time & getStart() const noexcept;
    const Time & getEnd() const noexcept;
    const std::vector< Event > & getEvents() const noexcept;
    const std::vector< Table > & getTables() const noexcept;

    size_t getNumTables() const noexcept;
    size_t getNumClientsInQueue() const noexcept;
    int getClientTable(const std::string & client) const noexcept;

    void addEvent(const Event & ev);

    void addClient(const std::string & client);
    bool isClientInClub(const std::string & client) const noexcept;
    int removeClient(const std::string & client, const Time & t);

    bool isTableFree(int num) const;
    int getFreeTableNumber() const noexcept;
    void seatClientAtTable(const std::string & client, int num, const Time & t);

    void addToQueue(const std::string & client);
    bool isQueueEmpty() const noexcept;
    std::string moveFromQueueToTable(int num, const Time & t);

    std::vector< std::pair< std::string, int > > close();

  private:
    Time start_;
    Time end_;
    int cost_;
    std::vector< Table > tables_;
    std::vector< Event > events_;
    std::unordered_map< std::string, int > clients_;
    std::queue< std::string > waiting_queue_;
  };
}

#endif
