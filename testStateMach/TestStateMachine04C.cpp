
#include "TestStateMachine04C.h"
#include "TestStateMachine04.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/Boolean.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(TestStateMachine04C,"TestStateMachine04C")
EMPTY_SLOTTABLE(TestStateMachine04C)
EMPTY_CONSTRUCTOR(TestStateMachine04C)
EMPTY_COPYDATA(TestStateMachine04C)
EMPTY_DELETEDATA(TestStateMachine04C)
EMPTY_SERIALIZER(TestStateMachine04C)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine04C)
   STATE_FUNC( INIT_STATE, stateFunc00)
END_STATE_TABLE()

//------------------------------------------------------------------------------
// Pre/Post functions
//------------------------------------------------------------------------------

void TestStateMachine04C::preStateProc(const LCreal)
{
   // Start line
   std::cout << "SM(#4C)(" << getState() << "," << getSubstate() << "): ";
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------

void TestStateMachine04C::stateFunc00(const LCreal)
{
   switch (getSubstate()) {

      case INIT_STATE : {
         std::cout << "nextSubstate()";
         nextSubstate();
         break;
      }

      case 1 : {
         if (getMode() != RTN_STATE) {
            std::cout << "callState(CALL_02,arg=13)";
            Basic::Number* arg = new Basic::Integer(13);
            callState(TestStateMachine04::CALL_02, arg);
            arg->unref();
         }
         else {
            std::cout << "Returned from call; ";
            const Basic::Boolean* arg = dynamic_cast<const Basic::Boolean*>( getArgument() );
            if (arg != 0) {
               std::cout << "arg(" << arg->getBoolean() << "); ";
            }
            std::cout << "nextSubstate()";
            nextSubstate();
         }
         break;
      }

      case 2 : {
         std::cout << "nextState()";
         nextState();
         break;
      }

   }
}

} // End Test namespace
} // End Eaagles namespace
