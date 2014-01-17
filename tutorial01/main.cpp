
#include <iostream>

#include "openeaagles/basic/String.h"

namespace Tutorial {

int main(int argc, char* argv[])
{

  Eaagles::Basic::String* str = new Eaagles::Basic::String("Hello world\n");

  std::cout << str->getString();

  str->setStr("Goodbye world\n");

  std::cout << str->getString();

  str->unref();

  return 0;
}

}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Tutorial::main(argc, argv);
}
