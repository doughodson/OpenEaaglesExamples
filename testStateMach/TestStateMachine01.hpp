
#ifndef __TestStateMachine01_H__
#define __TestStateMachine01_H__

#include "openeaagles/base/StateMachine.hpp"

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
class TestStateMachine01 : public oe::base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine01, oe::base::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine01();

protected:
   virtual void preStateProc(const double dt) override;
   virtual void postStateProc(const double dt) override;
   virtual unsigned short stateTable(
         const unsigned short cstate,
         const StateTableCode code,
         const double dt=0
      ) override;

private:
   // State specific functions
   void anyStateFunc(const double dt);
};

#endif
