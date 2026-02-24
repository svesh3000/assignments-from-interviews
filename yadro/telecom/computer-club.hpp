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

    void processEvent(const Event & ev);
    void close();

  private:
    Time start_;
    Time end_;
    int cost_;
    std::vector< Table > tables_;
    std::vector< Event > events_;
    std::unordered_map< std::string, int > clients_;
    std::queue< std::string > waiting_queue_;

    void addEvent(const Event & ev);
    bool isClientInClub(const std::string & client) const noexcept;
    void addClient(const std::string & client);
    bool isTableFree(int num) const;
    int getFreeTableNumber() const noexcept;
    void seatClientAtTable(const std::string & client, int num, const Time & t);
    void addToQueue(const std::string & client);
    void moveFromQueueToTable(int num, const Time & t);
    int removeClient(const std::string & client, const Time & t);

    friend void handleClientArrival(ComputerClub &, const Event &);
    friend void handleClientSit(ComputerClub &, const Event &);
    friend void handleClientWait(ComputerClub &, const Event &);
    friend void handleClientLeave(ComputerClub &, const Event &);
  };

  std::pair< ComputerClub, std::string > processComputerClub(std::istream & in);
  std::ostream & printListEvents(const ComputerClub & comp_club, std::ostream & out);
  std::ostream & printListTables(const ComputerClub & comp_club, std::ostream & out);
}

#endif
