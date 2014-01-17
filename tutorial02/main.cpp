
#include <iostream>
#include "Random.h"

namespace Eaagles {
namespace Tutorial {

int main(int argc, char* argv[])
{
   std::cout << "Creating Random object\n";
   Random* rgen = new Random();
   std::cout << "Random object created\n";

   rgen->setSeed(25);

   for( int i=0; i<10; i++)
      std::cout << rgen->getNum() << std::endl;

   std::cout << "Unref'ing random object\n";
   rgen->unref();
   std::cout << "Random object unrefed\n";

   return 0;
}

} // namespace Tutorial
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   Eaagles::Tutorial::main(argc, argv);
}

