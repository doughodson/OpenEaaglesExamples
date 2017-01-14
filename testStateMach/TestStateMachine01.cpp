
#include "TestStateMachine01.hpp"

#include "openeaagles/base/Integer.hpp"
#include "openeaagles/base/Boolean.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(TestStateMachine01, "TestStateMachine01")
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

void TestStateMachine01::preStateProc(const double)
{
   // Start of trace line
   std::cout << "Test #1 State(" << getState() << "): ";
}

void TestStateMachine01::postStateProc(const double)
{
   // End of line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------

void TestStateMachine01::anyStateFunc(const double)
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
            const auto arg = new base::Integer(13);
            call(CALL_02, arg);
            arg->unref();
         }
         else {
            std::cout << "Returned from call; ";
            const auto arg = dynamic_cast<const base::Boolean*>( getArgument() );
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
         const auto arg = dynamic_cast<const base::Number*>( getArgument() );
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
         const auto arg = new base::Boolean(true);
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
