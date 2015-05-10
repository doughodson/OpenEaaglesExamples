
#include "openeaagles/linearSys/Sz1.h"
#include <iostream>
#include <cstdlib>

namespace Eaagles {
namespace Test {

int main(int, char**)
{
   enum { PULSE, STEP, RAMP };
   const unsigned int inputType = STEP;
   const unsigned int RATE = 100;
   const LCreal A = 10.0f;

   LinearSystem::Sz1 filter;

   filter.setN1(0.0);
   filter.setN2(1.0);
   filter.setD1(1/A);
   filter.setD2(1.0);
   filter.setRate(RATE);
   filter.setX0(0);
   filter.setY0(0);

   if (filter.isValid()) {
      std::cout << "Valid difference equation!" << std::endl;
   }
   else {
      std::cerr << "Error: invalid difference equation!" << std::endl;
      return EXIT_FAILURE;
   }

   LCreal time = 0;
   LCreal deltaTime = 1.0 / static_cast<LCreal>(RATE);

   for (unsigned int i = 0; i < RATE; i++) {
      time += deltaTime;
      LCreal input = 0.0;
      if (inputType == PULSE && i < 1) {
         input = 1.0f;
      }
      else if (inputType == STEP) {
         input = 1.0f;
      }
      else if (inputType == RAMP) {
         input = time;
      }
      LCreal out = filter.g(input);
      LCreal ee = lcExp( -time * A );
      std::cout << time << ", " << input << ", " << (1.0 -ee) << ", " << out << std::endl;
   }

   return EXIT_SUCCESS;
}

} // End Test namespace
} // End Eaagles namespace


int main(int argc, char* argv[], char**)
{
   return Eaagles::Test::main(argc,argv);
}
