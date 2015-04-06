//------------------------------------------------------------------------------
// Class: TestStateMachine01
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestStateMachine01_H__
#define __Eaagles_Test_TestStateMachine01_H__

#include "openeaagles/basic/StateMachine.h"

namespace Eaagles {
namespace Test {

//------------------------------------------------------------------------------
// Class: TestStateMachine01
// Description: State Machine Test #1 --
//
//    Tests the standard state transition functions (e.g., next(), goTo(), call(),
//    and rtn()), as well as arguments passed and returned.   There's one common
//    state function that's using the standard 'switch' and 'case' statements to
//    select each state's specific code.
//
//------------------------------------------------------------------------------
class TestStateMachine01 : public Basic::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine01, Basic::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine01();

protected:
   void preStateProc(const LCreal dt) override;
   void postStateProc(const LCreal dt) override;
   unsigned short stateTable(
         const unsigned short cstate,
         const StateTableCode code,
         const LCreal dt=0
      ) override;

private:
   // State specific functions
   void anyStateFunc(const LCreal dt);
};

} // End Test namespace
} // End Eaagles namespace

#endif
