//------------------------------------------------------------------------------
// Class: TestStateMachine04
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStateMachine04_H__
#define __oe_test_TestStateMachine04_H__

#include "openeaagles/base/StateMachine.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class: TestStateMachine04
//
//    Same as Test #2 plus we're testing the substate transition
//    functions: nextSubstate() and goToSubstate().
//
//------------------------------------------------------------------------------
class TestStateMachine04 : public base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04, base::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine04();

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
   void stateFunc00(const double dt);
   void stateFunc02(const double dt);
   void stateFunc03(const double dt);
   void stateFunc05(const double dt);
   void stateFunc11(const double dt);
   void stateFunc12(const double dt);
   void stateFunc14(const double dt);
   void stateFunc15(const double dt);
   void stateFunc21(const double dt);
   void stateFunc22(const double dt);
   void stateFunc23(const double dt);
   void stateFunc99(const double dt);
};

} // End test namespace
} // End oe namespace

#endif
