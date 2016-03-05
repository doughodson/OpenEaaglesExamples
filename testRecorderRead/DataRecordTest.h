//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#ifndef __oe_test_DataRecordTest_H__
#define __oe_test_DataRecordTest_H__

#include "openeaagles/base/Component.h"

namespace oe {

namespace recorder { class InputHandler; class OutputHandler; }

namespace test {

//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
class DataRecordTest : public base::Component
{
   DECLARE_SUBCLASS(DataRecordTest, base::Component)

public:
    DataRecordTest();

    // Main test
    void runTest();

protected:
    // Slot functions
    virtual bool setSlotInputHandler(recorder::InputHandler* const msg);
    virtual bool setSlotOutputHandler(recorder::OutputHandler* const msg);

private:
   void initData();

   base::safe_ptr<recorder::InputHandler> inputHandler;
   base::safe_ptr<recorder::OutputHandler> outputHandler;
};

}
}

#endif
