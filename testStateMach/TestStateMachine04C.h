//------------------------------------------------------------------------------
// Class: TestStateMachine04C
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStateMachine04C_H__
#define __oe_test_TestStateMachine04C_H__

#include "openeaagles/base/StateMachine.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class: TestStateMachine04C
//
//------------------------------------------------------------------------------
class TestStateMachine04C : public base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04C, base::StateMachine)

public:
   TestStateMachine04C();

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
};

} // End test namespace
} // End oe namespace

#endif
