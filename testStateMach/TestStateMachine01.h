//------------------------------------------------------------------------------
// Class: TestStateMachine01
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStateMachine01_H__
#define __oe_test_TestStateMachine01_H__

#include "openeaagles/base/StateMachine.h"

namespace oe {
namespace test {

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
class TestStateMachine01 : public base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine01, base::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine01();

protected:
   void preStateProc(const double dt) override;
   void postStateProc(const double dt) override;
   unsigned short stateTable(
         const unsigned short cstate,
         const StateTableCode code,
         const double dt=0
      ) override;

private:
   // State specific functions
   void anyStateFunc(const double dt);
};

} // End test namespace
} // End oe namespace

#endif
