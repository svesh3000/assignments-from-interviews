#include <exception>
#include <fstream>

#include "computer-club.hpp"

int main(int argc, char * argv[])
{
  using namespace telecom;
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " test_file.txt\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cout << "NON-EXISTENT FILE\n";
    return 1;
  }

  try
  {
    std::pair< ComputerClub, std::string > club_with_err = processComputerClub(file);
    if (!club_with_err.second.empty())
    {
      std::cout << club_with_err.second << "\n";
      return 1;
    }

    ComputerClub & club = club_with_err.first;
    std::cout << club.getStart() << '\n';
    printListEvents(club, std::cout) << '\n';
    std::cout << club.getEnd() << '\n';
    printListTables(club, std::cout) << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
