
#include <iostream>

#include "openeaagles/base/String.h"

int main(int argc, char* argv[])
{
   oe::base::String* str = new oe::base::String("Hello world\n");

   std::cout << str->getString();

   str->setStr("Goodbye world\n");

   std::cout << str->getString();

   str->unref();

   return 0;
}
