
#include <iostream>
#include "Random.h"

namespace Eaagles {
namespace Example02 {

int exec (int, char **)
{
  Random* rgen = new Random();
  rgen->setSeed(25);

  for( int i=0; i<10; i++)
    std::cout << rgen->getNum() << std::endl;

  rgen->unref();

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
