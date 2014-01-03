
#include "TestStateMachine04A.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/Boolean.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(TestStateMachine04A,"TestStateMachine04A")
EMPTY_SLOTTABLE(TestStateMachine04A)
EMPTY_CONSTRUCTOR(TestStateMachine04A)
EMPTY_COPYDATA(TestStateMachine04A)
EMPTY_DELETEDATA(TestStateMachine04A)
EMPTY_SERIALIZER(TestStateMachine04A)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine04A)
   STATE_FUNC( INIT_STATE, stateFunc00)
   STATE_FUNC( 1, stateFunc01)
   STATE_FUNC( 2, stateFunc02)
   STATE_FUNC( 3, stateFunc03)
   STATE_FUNC( 4, stateFunc04)
END_STATE_TABLE()

//------------------------------------------------------------------------------
// Pre/Post functions
//------------------------------------------------------------------------------

void TestStateMachine04A::preStateProc(const LCreal)
{
   std::cout << "SM(#4A)(" << getState() << "," << getSubstate() << "): ";
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine04A::stateFunc00(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04A::stateFunc01(const LCreal)
{
   std::cout << "goTo(3)";
   goTo(3);
}

void TestStateMachine04A::stateFunc02(const LCreal)
{
   std::cout << "Should NOT be here!";
}

void TestStateMachine04A::stateFunc03(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04A::stateFunc04(const LCreal)
{
   std::cout << "nextState()";
   nextState();
}


} // End Test namespace
} // End Eaagles namespace
