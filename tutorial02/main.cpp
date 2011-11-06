
#include <iostream>
#include "Random.h"

namespace Eaagles {
namespace Example02 {

int exec (int, char **)
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

} // namespace Example02
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   Eaagles::Example02::exec(argc, argv);
}

