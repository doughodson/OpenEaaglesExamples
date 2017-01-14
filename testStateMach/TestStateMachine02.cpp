
#include "TestStateMachine02.hpp"

#include "openeaagles/base/Integer.hpp"
#include "openeaagles/base/Boolean.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(TestStateMachine02, "TestStateMachine02")
EMPTY_SLOTTABLE(TestStateMachine02)
EMPTY_CONSTRUCTOR(TestStateMachine02)
EMPTY_COPYDATA(TestStateMachine02)
EMPTY_DELETEDATA(TestStateMachine02)
EMPTY_SERIALIZER(TestStateMachine02)

// State dispatch table
BEGIN_STATE_TABLE(TestStateMachine02)
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

void TestStateMachine02::preStateProc(const double)
{
   // Start line
   std::cout << "Test #2 State(" << getState() << "): ";
}

void TestStateMachine02::postStateProc(const double)
{
   // End the line
   std::cout << std::endl;
}

//------------------------------------------------------------------------------
// State functions
//------------------------------------------------------------------------------
void TestStateMachine02::stateFunc00(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc01(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc02(const double)
{
   std::cout << "goTo(4)";
   goTo(4);
}

void TestStateMachine02::stateFunc03(const double)
{
   std::cout << "Should NOT be here!";
}

void TestStateMachine02::stateFunc04(const double)
{
   if (getMode() != RTN_STATE) {
      std::cout << "call(CALL_01)";
      call(CALL_01);
   }
   else {
      std::cout << "Returned from call(); next()";
      next();
   }
}

void TestStateMachine02::stateFunc05(const double)
{
   std::cout << "goTo(99)";
   goTo(99);
}

void TestStateMachine02::stateFunc11(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc12(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc13(const double)
{
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
}

void TestStateMachine02::stateFunc14(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc15(const double)
{
   std::cout << "rtn()";
   rtn();
}

void TestStateMachine02::stateFunc21(const double)
{
   const auto arg = dynamic_cast<const base::Number*>( getArgument() );
   if (arg != nullptr) {
      std::cout << "arg(" << arg->getReal() << "); ";
   }

   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc22(const double)
{
   std::cout << "next()";
   next();
}

void TestStateMachine02::stateFunc23(const double)
{
   std::cout << "rtn(arg=1)";
   const auto arg = new base::Boolean(1);
   rtn(arg);
   arg->unref();
}

void TestStateMachine02::stateFunc99(const double)
{
   if (getMode() == NEW_STATE) {
      std::cout << "Finished;";
   }
}
