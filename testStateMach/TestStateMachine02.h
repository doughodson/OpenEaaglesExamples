//------------------------------------------------------------------------------
// Class: TestStateMachine02
//------------------------------------------------------------------------------
#ifndef __oe_test_TestStateMachine02_H__
#define __oe_test_TestStateMachine02_H__

#include "openeaagles/base/StateMachine.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class: TestStateMachine02
// Description: State Machine Test #2 --
//
//    Same as Test #1 except that we're using separate state specific functions.
//
//------------------------------------------------------------------------------
class TestStateMachine02 : public base::StateMachine
{
   DECLARE_SUBCLASS(TestStateMachine02, base::StateMachine)

public:
   enum { CALL_01 = 11, CALL_02 = 22 };

public:
   TestStateMachine02();

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
   void stateFunc00(const double dt);
   void stateFunc01(const double dt);
   void stateFunc02(const double dt);
   void stateFunc03(const double dt);
   void stateFunc04(const double dt);
   void stateFunc05(const double dt);
   void stateFunc11(const double dt);
   void stateFunc12(const double dt);
   void stateFunc13(const double dt);
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
