
#include "TestStateMachine03.hpp"

#include "openeaagles/base/Integer.hpp"
#include "openeaagles/base/Boolean.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(TestStateMachine03, "TestStateMachine03")
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

void TestStateMachine03::preStateProc(const double)
{
   // Start line
   std::cout << "Test #3 State(" << getState() << "," << getSubstate() << "): ";
}

void TestStateMachine03::postStateProc(const double)
{
   // End the line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine03::stateFunc00(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc01(const double)
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

void TestStateMachine03::stateFunc02(const double)
{
   std::cout << "goTo(4)";
   goTo(4);
}

void TestStateMachine03::stateFunc03(const double)
{
   std::cout << "Should NOT be here!";
}

void TestStateMachine03::stateFunc04(const double)
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

void TestStateMachine03::stateFunc05(const double)
{
   std::cout << "goTo(99)";
   goTo(99);
}

void TestStateMachine03::stateFunc11(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc12(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc13(const double)
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

void TestStateMachine03::stateFunc14(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc15(const double)
{
   std::cout << "rtn()";
   rtn();
}

void TestStateMachine03::stateFunc21(const double)
{
   const auto arg = dynamic_cast<const base::Number*>( getArgument() );
   if (arg != nullptr) {
      std::cout << "arg(" << arg->getReal() << "); ";
   }

   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc22(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine03::stateFunc23(const double)
{
   std::cout << "rtn(arg=true)";
   const auto arg = new base::Boolean(true);
   rtn(arg);
   arg->unref();
}

void TestStateMachine03::stateFunc99(const double)
{
   if (getMode() == NEW_STATE) {
      std::cout << "Finished;";
   }
}
