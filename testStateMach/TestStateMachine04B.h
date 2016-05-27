
#ifndef __TestStateMachine04B_H__
#define __TestStateMachine04B_H__

#include "openeaagles/base/StateMachine.h"

//------------------------------------------------------------------------------
// Class: TestStateMachine04B
//
//------------------------------------------------------------------------------
class TestStateMachine04B : public oe::base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04B, oe::base::StateMachine)

public:
   TestStateMachine04B();

protected:
   virtual void preStateProc(const double dt) override;
   virtual unsigned short stateTable(
         const unsigned short cstate,
         const StateTableCode code,
         const double dt=0
      ) override;

private:
   // State specific functions
   void stateFunc00(const double dt);
   void stateFunc01(const double dt);
   void stateFunc02(const double dt);
};

#endif
