
#include "TestStateMachine03.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/Boolean.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(TestStateMachine03,"TestStateMachine03")
EMPTY_SLOTTABLE(TestStateMachine03)
EMPTY_CONSTRUCTOR(TestStateMachine03)
EMPTY_COPYDATA(TestStateMachine03)
EMPTY_DELETEDATA(TestStateMachine03)
EMPTY_SERIALIZER(TestStateMachine03)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine03)
   STATE_FUNC( INIT_STATE, stateFunc00)
   STATE_FUNC( 1, stateFunc01)
   STATE_FUNC( 2, stateFunc02)
   STATE_FUNC( 3, stateFunc03)
   STATE_FUNC( 4, stateFunc04)
   STATE_FUNC( 5, stateFunc05)
   STATE_FUNC(11, stateFunc11)
   STATE_FUNC(12, stateFunc12)
   STATE_FUNC(13, stateFunc13)
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

void TestStateMachine03::preStateProc(const LCreal)
{
   // Start line
   std::cout << "Test #3 State(" << getState() << "," << getSubstate() << "): ";
}

void TestStateMachine03::postStateProc(const LCreal)
{
   // End the line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine03::stateFunc00(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc01(const LCreal)
{

   switch (getSubstate()) {

      case INIT_STATE : {
         std::cout << "nextSubstate()";
         nextSubstate();
         break;
      }

      case 1 : {
         std::cout << "nextSubstate()";
         nextSubstate();
         break;
      }

      case 2 : {
         std::cout << "goToSubstate(4)";
         goToSubstate(4);
         break;
      }

      case 3 : {
         std::cout << "Should NOT be here!";
         break;
      }

      case 4 : {
         std::cout << "next()";
         next();
         break;
      }

   }
}

void TestStateMachine03::stateFunc02(const LCreal)
{
   std::cout << "goTo(4)";
   goTo(4);
}

void TestStateMachine03::stateFunc03(const LCreal)
{
   std::cout << "Should NOT be here!";
}

void TestStateMachine03::stateFunc04(const LCreal)
{
   switch (getSubstate()) {

      case INIT_STATE : {
         std::cout << "nextSubstate()";
         nextSubstate();
         break;
      }

      case 1 : {
         if (getMode() != RTN_STATE) {
            std::cout << "call(CALL_01)";
            call(CALL_01);
         }
         else {
            std::cout << "Returned from call(); nextSubstate()";
            nextSubstate();
         }
         break;
      }

      case 2 : {
         std::cout << "next()";
         next();
         break;
      }

   }
}

void TestStateMachine03::stateFunc05(const LCreal)
{
   std::cout << "goTo(99)";
   goTo(99);
}

void TestStateMachine03::stateFunc11(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc12(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc13(const LCreal)
{
   switch (getSubstate()) {

      case INIT_STATE : {
         std::cout << "nextSubstate()";
         nextSubstate();
         break;
      }

      case 1 : {
         if (getMode() != RTN_STATE) {
            std::cout << "call(CALL_02,arg=13)";
            Basic::Number* arg = new Basic::Integer(13);
            call(CALL_02, arg);
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
         std::cout << "next()";
         next();
         break;
      }

   }
}

void TestStateMachine03::stateFunc14(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc15(const LCreal)
{
   std::cout << "rtn()";
   rtn();
}

void TestStateMachine03::stateFunc21(const LCreal)
{
   const Basic::Number* arg = dynamic_cast<const Basic::Number*>( getArgument() );
   if (arg != 0) {
      std::cout << "arg(" << arg->getReal() << "); ";
   }

   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc22(const LCreal)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc23(const LCreal)
{
   std::cout << "rtn(arg=true)";
   Basic::Boolean* arg = new Basic::Boolean(true);
   rtn(arg);
   arg->unref();
}

void TestStateMachine03::stateFunc99(const LCreal)
{
   if (getMode() == NEW_STATE) {
      std::cout << "Finished;";
   }
}

} // End Test namespace
} // End Eaagles namespace
