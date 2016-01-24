//------------------------------------------------------------------------------
// Class: TestStateMachine04
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStateMachine04_H__
#define __oe_test_TestStateMachine04_H__

#include "openeaagles/basic/StateMachine.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class: TestStateMachine04
//
//    Same as Test #2 plus we're testing the substate transition
//    functions: nextSubstate() and goToSubstate().
//
//------------------------------------------------------------------------------
class TestStateMachine04 : public basic::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04, basic::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine04();

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
   void stateFunc00(const LCreal dt);
   void stateFunc02(const LCreal dt);
   void stateFunc03(const LCreal dt);
   void stateFunc05(const LCreal dt);
   void stateFunc11(const LCreal dt);
   void stateFunc12(const LCreal dt);
   void stateFunc14(const LCreal dt);
   void stateFunc15(const LCreal dt);
   void stateFunc21(const LCreal dt);
   void stateFunc22(const LCreal dt);
   void stateFunc23(const LCreal dt);
   void stateFunc99(const LCreal dt);
};

} // End test namespace
} // End oe namespace

#endif
