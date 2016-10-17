
#ifndef __TestStateMachine04A_H__
#define __TestStateMachine04A_H__

#include "openeaagles/base/StateMachine.hpp"

//------------------------------------------------------------------------------
// Class: TestStateMachine04A -- (sub) State Machine test #4a
//
//
//------------------------------------------------------------------------------
class TestStateMachine04A : public oe::base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04A, oe::base::StateMachine)

public:
   TestStateMachine04A();

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
   void stateFunc03(const double dt);
   void stateFunc04(const double dt);
};

#endif
