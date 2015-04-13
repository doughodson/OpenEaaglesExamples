//------------------------------------------------------------------------------
// Class: TestStateMachine03
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestStateMachine03_H__
#define __Eaagles_Test_TestStateMachine03_H__

#include "openeaagles/basic/StateMachine.h"

namespace Eaagles {
namespace Test {

//------------------------------------------------------------------------------
// Class: TestStateMachine03
//
//    Same as Test #2 plus we're testing the substate transition
//    functions: nextSubstate() and goToSubstate().
//
//------------------------------------------------------------------------------
class TestStateMachine03 : public Basic::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine03, Basic::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine03();

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
   void stateFunc01(const LCreal dt);
   void stateFunc02(const LCreal dt);
   void stateFunc03(const LCreal dt);
   void stateFunc04(const LCreal dt);
   void stateFunc05(const LCreal dt);
   void stateFunc11(const LCreal dt);
   void stateFunc12(const LCreal dt);
   void stateFunc13(const LCreal dt);
   void stateFunc14(const LCreal dt);
   void stateFunc15(const LCreal dt);
   void stateFunc21(const LCreal dt);
   void stateFunc22(const LCreal dt);
   void stateFunc23(const LCreal dt);
   void stateFunc99(const LCreal dt);
};

} // End Test namespace
} // End Eaagles namespace

#endif
