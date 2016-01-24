
#include <iostream>

#include "openeaagles/basic/String.h"

namespace Tutorial {

int main(int argc, char* argv[])
{
   oe::basic::String* str = new oe::basic::String("Hello world\n");

   std::cout << str->getString();

   str->setStr("Goodbye world\n");

   std::cout << str->getString();

   str->unref();

   return 0;
}

}

//
int main(int argc, char* argv[])
{
   Tutorial::main(argc, argv);
}
