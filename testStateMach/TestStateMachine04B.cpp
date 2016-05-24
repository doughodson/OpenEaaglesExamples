
#include "TestStateMachine04B.h"
#include "TestStateMachine04.h"

#include "openeaagles/base/Integer.h"
#include "openeaagles/base/Boolean.h"

namespace oe {
namespace test {

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

void TestStateMachine04B::preStateProc(const double)
{
   // Start line
   std::cout << "SM(#4B)(" << getState() << "," << getSubstate() << "): ";
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine04B::stateFunc00(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine04B::stateFunc01(const double)
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

void TestStateMachine04B::stateFunc02(const double)
{
   std::cout << "nextState()";
   nextState();
}


}
}
