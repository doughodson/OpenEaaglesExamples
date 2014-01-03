//------------------------------------------------------------------------------
// Class: TestStateMachine04C
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestStateMachine04C_H__
#define __Eaagles_Test_TestStateMachine04C_H__

#include "openeaagles/basic/StateMachine.h"

namespace Eaagles {
namespace Test {

//------------------------------------------------------------------------------
// Class: TestStateMachine04C
//
//------------------------------------------------------------------------------
class TestStateMachine04C : public Basic::StateMachine {
   DECLARE_SUBCLASS(TestStateMachine04C,Basic::StateMachine)

public:
   TestStateMachine04C();

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
};

} // End Test namespace
} // End Eaagles namespace

#endif
