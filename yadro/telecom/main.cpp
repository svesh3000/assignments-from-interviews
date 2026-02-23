#include <exception>
#include <fstream>
#include <vector>

#include "computer-club.hpp"

int main(int argc, char * argv[])
{
  if (argc > 2)
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

  telecom::ComputerClub comp_club;
  try
  {
    std::string err = loadAndExec(comp_club, file);
    if (!err.empty())
    {
      std::cout << err << "\n";
      return 1;
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  }

  std::cout << comp_club.getStart() << '\n';
  std::vector< telecom::Event > events = comp_club.getEvents();
  for (size_t i = 0; i < events.size(); i++)
  {
    std::cout << events[i] << '\n';
  }
  std::cout << comp_club.getEnd() << '\n';
  std::vector< telecom::Table > tables = comp_club.getTables();
  for (size_t i = 0; i < tables.size(); i++)
  {
    std::cout << tables[i] << '\n';
  }

  return 0;
}
