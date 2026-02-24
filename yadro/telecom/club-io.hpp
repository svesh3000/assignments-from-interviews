#ifndef CLUB_IO_HPP
#define CLUB_IO_HPP
#include "computer-club.hpp"

namespace telecom
{
  std::pair< ComputerClub, std::string > processComputerClub(std::istream & in);

  std::ostream & printListEvents(const ComputerClub & comp_club, std::ostream & out);
  std::ostream & printListTables(const ComputerClub & comp_club, std::ostream & out);
}

#endif
