//------------------------------------------------------------------------------
// Class: TestStateMachine04A
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestStateMachine04A_H__
#define __Eaagles_Test_TestStateMachine04A_H__

#include "openeaagles/basic/StateMachine.h"

namespace Eaagles {
namespace Test {

//------------------------------------------------------------------------------
// Class: TestStateMachine04A -- (sub) State Machine test #4a
//
//
//------------------------------------------------------------------------------
class TestStateMachine04A : public Basic::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine04A, Basic::StateMachine)

public:
   TestStateMachine04A();

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
   void stateFunc03(const LCreal dt);
   void stateFunc04(const LCreal dt);
};

} // End Test namespace
} // End Eaagles namespace

#endif
