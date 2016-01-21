//------------------------------------------------------------------------------
// Class: TestStateMachine04B
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStateMachine04B_H__
#define __oe_test_TestStateMachine04B_H__

#include "openeaagles/basic/StateMachine.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class: TestStateMachine04B
//
//------------------------------------------------------------------------------
class TestStateMachine04B : public Basic::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04B, Basic::StateMachine)

public:
   TestStateMachine04B();

protected:
   void preStateProc(const LCreal dt) override;
   unsigned short stateTable(
         const unsigned short cstate,
         const StateTableCode code,
         const LCreal dt=0
      ) override;

private:
   // State specific functions
   void stateFunc00(const LCreal dt);
   void stateFunc01(const LCreal dt);
   void stateFunc02(const LCreal dt);
};

} // End test namespace
} // End oe namespace

#endif
