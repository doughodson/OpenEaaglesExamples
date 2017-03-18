
#include "openeaagles/linearsystem/Sz1.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>

int main(int, char**)
{
   enum class InputType { PULSE, STEP, RAMP };
   const InputType inputType = InputType::STEP;
   const unsigned int RATE {100};
   const double A {10.0};

   oe::linearsystem::Sz1 filter;

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

   double time = 0.0;
   const double deltaTime = 1.0 / static_cast<double>(RATE);

   for (unsigned int i = 0; i < RATE; i++) {
      time += deltaTime;
      double input = 0.0;
      if (inputType == InputType::PULSE && i < 1) {
         input = 1.0f;
      }
      else if (inputType == InputType::STEP) {
         input = 1.0f;
      }
      else if (inputType == InputType::RAMP) {
         input = time;
      }
      const double out = filter.g(input);
      const double ee = std::exp( -time * A );
      std::cout << time << ", " << input << ", " << (1.0 - ee) << ", " << out << std::endl;
   }

   return EXIT_SUCCESS;
}
