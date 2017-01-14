//------------------------------------------------------------------------------
// Test template class creation and functionality
//------------------------------------------------------------------------------

#include <iostream>

#include "openeaagles/base/LinkedList.hpp"
#include "openeaagles/base/Color.hpp"

//using namespace oe::base;

int main(int argc, char**)
{
   std::cout << "Test templates" << std::endl;

   auto colorList = new oe::base::LinkedList<oe::base::Color>;

   if (colorList->isEmpty()) { std::cout << "List is empty\n"; }

   std::cout << "# entries : " << colorList->entries() << std::endl;

   oe::base::Color* c1 = new oe::base::Color();

   colorList->put(c1);

   std::cout << "# entries : " << colorList->entries() << std::endl;


   return 0;
}
