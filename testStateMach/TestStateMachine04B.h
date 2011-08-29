//------------------------------------------------------------------------------
// Class: TestStateMachine04B
//------------------------------------------------------------------------------
#ifndef __TestStateMach_TestStateMachine04B_H__
#define __TestStateMach_TestStateMachine04B_H__

#include "openeaagles/basic/StateMachine.h"

namespace Eaagles {
namespace TestStateMach {

//------------------------------------------------------------------------------
// Class: TestStateMachine04B
//
//------------------------------------------------------------------------------
class TestStateMachine04B : public Basic::StateMachine {
   DECLARE_SUBCLASS(TestStateMachine04B,Basic::StateMachine)

public:
   TestStateMachine04B();

protected:
   // Basic::StateMachine protected interface function
   virtual void preStateProc(const LCreal dt);
   virtual unsigned short stateTable(
         const unsigned short cstate,
         const StateTableCode code,
         const LCreal dt=0
      );

private:
   // State specific functions
   void stateFunc00(const LCreal dt);
   void stateFunc01(const LCreal dt);
   void stateFunc02(const LCreal dt);
};

} // End TestStateMach namespace
} // End Eaagles namespace

#endif	/* __TestStateMach_TestStateMachine04B_H__ */
