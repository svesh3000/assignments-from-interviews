#ifndef COMPUTER_CLUB_HPP
#define COMPUTER_CLUB_HPP
#include <vector>

#include "event.hpp"
#include "table.hpp"

namespace telecom
{
  class ComputerClub
  {
  public:
    Time getStart();
    Time getEnd();
    std::vector< Event > getEvents();
    std::vector< Table > getTables();

  private:
    Time start_;
    Time end_;
    std::vector< Event > report_events_;
    std::vector< Table > tables_;
  };

  std::string loadAndExec(ComputerClub comp_club, std::istream & in);
}

#endif
