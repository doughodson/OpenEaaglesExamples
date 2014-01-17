
#include "TestStateMachine04B.h"
#include "TestStateMachine04.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/Boolean.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(TestStateMachine04B,"TestStateMachine04B")
EMPTY_SLOTTABLE(TestStateMachine04B)
EMPTY_CONSTRUCTOR(TestStateMachine04B)
EMPTY_COPYDATA(TestStateMachine04B)
EMPTY_DELETEDATA(TestStateMachine04B)
EMPTY_SERIALIZER(TestStateMachine04B)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine04B)
   STATE_FUNC( INIT_STATE, stateFunc00)
   STATE_FUNC( 1, stateFunc01)
   STATE_FUNC( 2, stateFunc02)
END_STATE_TABLE()

//------------------------------------------------------------------------------
// Pre/Post functions
//------------------------------------------------------------------------------

void TestStateMachine04B::preStateProc(const LCreal)
{
   // Start line
   std::cout << "SM(#4B)(" << getState() << "," << getSubstate() << "): ";
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine04B::stateFunc00(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04B::stateFunc01(const LCreal)
{
   if (getMode() != RTN_STATE) {
      std::cout << "callState(CALL_01)";
      callState(TestStateMachine04::CALL_01);
   }
   else {
      std::cout << "Returned from call(); next()";
      next();
   }
}

void TestStateMachine04B::stateFunc02(const LCreal)
{
   std::cout << "nextState()";
   nextState();
}


} // End Test namespace
} // End Eaagles namespace
