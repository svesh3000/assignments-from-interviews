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
    ComputerClub(Time start, Time end, int cost);

    const Time & getStart() const;
    const Time & getEnd() const;
    const std::vector< Event > & getEvents() const;
    const std::vector< Table > & getTables() const;

    void processEvent(const Event & ev);
    void close();

  private:
    Time start_;
    Time end_;
    int cost_;
    std::vector< Table > tables_;
    std::vector< Event > events_;
    std::unordered_map< std::string, int > clients_;
    std::queue< std::string > waitig_queue_;

    void addEvent(const Event & ev);
    void addClient(const std::string & client);
    void seatClientAtTable(const std::string & client, int num);
    bool isClientWait(const std::string & client);
    void removeClient(const std::string & client);

    friend void handleClientArrival(ComputerClub &, const Event &);
    friend void handleClientSit(ComputerClub &, const Event &);
    friend void handleClientWait(ComputerClub &, const Event &);
    friend void handleClientLeave(ComputerClub &, const Event &);
  };

  std::pair< ComputerClub, std::string > loadComputerClub(std::istream & in);
  std::ostream & printListEvents(const ComputerClub & comp_club, std::ostream & out);
  std::ostream & printListTables(const ComputerClub & comp_club, std::ostream & out);
}

#endif
