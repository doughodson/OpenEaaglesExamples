
#include <iostream>
#include "openeaagles/basic/String.h"

namespace Example01 {

int exec (int, char **)
{

  Eaagles::Basic::String* str = new Eaagles::Basic::String("Hello world\n");

  std::cout << str->getString();

  str->setStr("Goodbye world\n");

  std::cout << str->getString();

  str->unref();

  return 0;
}

} // namespace Example01

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Example01::exec(argc, argv);
}

