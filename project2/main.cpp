#include <iostream>
#include <string>

#include "heat.hpp"

int main(int argc, char *argv[])
{
  /* Get command line arguments */
  if (argc != 3)
  {
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << argv[0] << " <input file> <soln prefix>" << std::endl;
    return 0;
  }
  std::string inputfile   = argv[1];
  std::string soln_prefix   = argv[2];

  /* Setup 2D heat equation system */
  HeatEquation2D sys;
  int status = sys.Setup(inputfile);
  if (status)
  {
    std::cerr << "ERROR: System setup was unsuccessful!" << std::endl;
    return 1;
  }
  
  /* Solve system using CG */
  status = sys.Solve(soln_prefix);
  if (status)
  {
    std::cerr << "ERROR: System solve was unsuccessful!" << std::endl;
    return 1;
  }

  return 0;
}
