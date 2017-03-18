
#ifndef __DataRecordTest_H__
#define __DataRecordTest_H__

#include "openeaagles/base/Component.hpp"

namespace oe {
namespace recorder { class InputHandler; class OutputHandler; }
}

//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
class DataRecordTest : public oe::base::Component
{
   DECLARE_SUBCLASS(DataRecordTest, oe::base::Component)

public:
   DataRecordTest();

   // Main test
   void runTest();

protected:
   // Slot functions
   virtual bool setSlotInputHandler(oe::recorder::InputHandler* const msg);
   virtual bool setSlotOutputHandler(oe::recorder::OutputHandler* const msg);

private:
   void initData();

   oe::base::safe_ptr<oe::recorder::InputHandler> inputHandler;
   oe::base::safe_ptr<oe::recorder::OutputHandler> outputHandler;
};

#endif
