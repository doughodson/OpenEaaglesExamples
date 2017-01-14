
#include "TestStateMachine04.hpp"

#include "openeaagles/base/Integer.hpp"
#include "openeaagles/base/Boolean.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(TestStateMachine04, "TestStateMachine04")
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

void TestStateMachine04::preStateProc(const double)
{
   // Start line
   std::cout << "Test #4 State(" << getState() << "," << getSubstate() << "): ";
}

void TestStateMachine04::postStateProc(const double)
{
   // End the line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine04::stateFunc00(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc02(const double)
{
   std::cout << "goTo(4)";
   goTo(4);
}

void TestStateMachine04::stateFunc03(const double)
{
   std::cout << "Should NOT be here!";
}

void TestStateMachine04::stateFunc05(const double)
{
   std::cout << "goTo(99)";
   goTo(99);
}

void TestStateMachine04::stateFunc11(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc12(const double)
{
   std::cout << "next()";
   next();
}


void TestStateMachine04::stateFunc14(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc15(const double)
{
   std::cout << "rtn()";
   rtn();
}

void TestStateMachine04::stateFunc21(const double)
{
   const auto arg = dynamic_cast<const base::Number*>( getArgument() );
   if (arg != nullptr) {
      std::cout << "arg(" << arg->getReal() << "); ";
   }

   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc22(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04::stateFunc23(const double)
{
   std::cout << "rtn(arg=true)";
   const auto arg = new base::Boolean(true);
   rtn(arg);
   arg->unref();
}

void TestStateMachine04::stateFunc99(const double)
{
   if (getMode() == NEW_STATE) {
      std::cout << "Finished;";
   }
}
