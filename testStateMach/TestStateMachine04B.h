//------------------------------------------------------------------------------
// Class: TestStateMachine04B
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestStateMachine04B_H__
#define __Eaagles_Test_TestStateMachine04B_H__

#include "openeaagles/basic/StateMachine.h"

namespace Eaagles {
namespace Test {

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

} // End Test namespace
} // End Eaagles namespace

#endif
