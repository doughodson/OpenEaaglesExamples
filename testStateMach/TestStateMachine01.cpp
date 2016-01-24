
#include "TestStateMachine01.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/Boolean.h"

namespace oe {
namespace test {

IMPLEMENT_SUBCLASS(TestStateMachine01,"TestStateMachine01")
EMPTY_SLOTTABLE(TestStateMachine01)
EMPTY_CONSTRUCTOR(TestStateMachine01)
EMPTY_COPYDATA(TestStateMachine01)
EMPTY_DELETEDATA(TestStateMachine01)
EMPTY_SERIALIZER(TestStateMachine01)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine01)
   ANY_STATE_FUNC( anyStateFunc)
END_STATE_TABLE()

//------------------------------------------------------------------------------
// Pre/Post functions
//------------------------------------------------------------------------------

void TestStateMachine01::preStateProc(const LCreal)
{
   // Start of trace line
   std::cout << "Test #1 State(" << getState() << "): ";
}

void TestStateMachine01::postStateProc(const LCreal)
{
   // End of line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------

void TestStateMachine01::anyStateFunc(const LCreal)
{
   switch (getState()) {

      case INIT_STATE : {
         std::cout << "next()";
         next();
         break;
      }

      case 1 : {
         std::cout << "next()";
         next();
         break;
      }

      case 2 : {
         std::cout << "goTo(4)";
         goTo(4);
         break;
      }

      case 3 : {
         std::cout << "Should NOT be here!";
         break;
      }

      case 4 : {
         if (getMode() != RTN_STATE) {
            std::cout << "call(CALL_01)";
            call(CALL_01);
         }
         else {
            std::cout << "Returned from call(); next()";
            next();
         }
         break;
      }

      case 5 : {
         std::cout << "goTo(99)";
         goTo(99);
         break;
      }

      case 11 : {
         std::cout << "next()";
         next();
         break;
      }

      case 12 : {
         std::cout << "next()";
         next();
         break;
      }

      case 13 : {
         if (getMode() != RTN_STATE) {
            std::cout << "call(CALL_02,arg=13)";
            basic::Number* arg = new basic::Integer(13);
            call(CALL_02, arg);
            arg->unref();
         }
         else {
            std::cout << "Returned from call; ";
            const basic::Boolean* arg = dynamic_cast<const basic::Boolean*>( getArgument() );
            if (arg != nullptr) {
               std::cout << "arg(" << arg->getBoolean() << "); ";
            }
            std::cout << "next()";
            next();
         }
         break;
      }

      case 14 : {
         std::cout << "next()";
         next();
         break;
      }

      case 15 : {
         std::cout << "rtn()";
         rtn();
         break;
      }

      case 21 : {
         const basic::Number* arg = dynamic_cast<const basic::Number*>( getArgument() );
         if (arg != nullptr) {
            std::cout << "arg(" << arg->getReal() << "); ";
         }

         std::cout << "next()";
         next();
         break;
      }

      case 22 : {
         std::cout << "next()";
         next();
         break;
      }

      case 23 : {
         std::cout << "rtn(arg=true)";
         basic::Boolean* arg = new basic::Boolean(true);
         rtn(arg);
         arg->unref();
         break;
      }

      case 99 : {
         if (getMode() == NEW_STATE) {
            std::cout << "Finished;";
         }
         break;
      }

   };
}

} // End test namespace
} // End oe namespace
