
#include "TestStateMachine04.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/Boolean.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(TestStateMachine04,"TestStateMachine04")
EMPTY_SLOTTABLE(TestStateMachine04)
EMPTY_CONSTRUCTOR(TestStateMachine04)
EMPTY_COPYDATA(TestStateMachine04)
EMPTY_DELETEDATA(TestStateMachine04)
EMPTY_SERIALIZER(TestStateMachine04)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine04)
   STATE_FUNC( INIT_STATE, stateFunc00)
   STATE_MACH( 1, "s01")
   STATE_FUNC( 2, stateFunc02)
   STATE_FUNC( 3, stateFunc03)
   STATE_MACH( 4, "s04")
   STATE_FUNC( 5, stateFunc05)
   STATE_FUNC(11, stateFunc11)
   STATE_FUNC(12, stateFunc12)
   STATE_MACH(13, "s13")
   STATE_FUNC(14, stateFunc14)
   STATE_FUNC(15, stateFunc15)
   STATE_FUNC(21, stateFunc21)
   STATE_FUNC(22, stateFunc22)
   STATE_FUNC(23, stateFunc23)
   STATE_FUNC(99, stateFunc99)
END_STATE_TABLE()

//------------------------------------------------------------------------------
// Pre/Post functions
//------------------------------------------------------------------------------

void TestStateMachine04::preStateProc(const LCreal)
{
   // Start line
   std::cout << "Test #4 State(" << getState() << "," << getSubstate() << "): ";
}

void TestStateMachine04::postStateProc(const LCreal)
{
   // End the line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine04::stateFunc00(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc02(const LCreal)
{
   std::cout << "goTo(4)";
   goTo(4);
}

void TestStateMachine04::stateFunc03(const LCreal)
{
   std::cout << "Should NOT be here!";
}

void TestStateMachine04::stateFunc05(const LCreal)
{
   std::cout << "goTo(99)";
   goTo(99);
}

void TestStateMachine04::stateFunc11(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc12(const LCreal)
{
   std::cout << "next()";
   next();
}


void TestStateMachine04::stateFunc14(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc15(const LCreal)
{
   std::cout << "rtn()";
   rtn();
}

void TestStateMachine04::stateFunc21(const LCreal)
{
   const Basic::Number* arg = dynamic_cast<const Basic::Number*>( getArgument() );
   if (arg != 0) {
      std::cout << "arg(" << arg->getReal() << "); ";
   }

   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc22(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc23(const LCreal)
{
   std::cout << "rtn(arg=true)";
   Basic::Boolean* arg = new Basic::Boolean(true);
   rtn(arg);
   arg->unref();
}

void TestStateMachine04::stateFunc99(const LCreal)
{
   if (getMode() == NEW_STATE) {
      std::cout << "Finished;";
   }
}

} // End Test namespace
} // End Eaagles namespace
