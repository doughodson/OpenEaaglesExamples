
#include <iostream>

#include "Random.hpp"

int main(int argc, char* argv[])
{
   std::cout << "Creating Random object\n";
   const auto rgen = new Random();
   std::cout << "Random object created\n";

   rgen->setSeed(25);

   for (unsigned int i=0; i<10; i++)
      std::cout << rgen->getNum() << std::endl;

   std::cout << "Unref'ing random object\n";
   rgen->unref();
   std::cout << "Random object unrefed\n";

   return 0;
}
