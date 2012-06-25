//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#ifndef __DataRecordTest_H__
#define __DataRecordTest_H__

namespace Eaagles {
   namespace Recorder { class InputHandler; class OutputHandler; }
}

#include "openeaagles/basic/Component.h"

namespace TestRecorder {

//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
class DataRecordTest : public Eaagles::Basic::Component {
   DECLARE_SUBCLASS(DataRecordTest,Eaagles::Basic::Component)

public:
    DataRecordTest();

    // Main test
    void runTest();

protected:
    // Slot functions
    virtual bool setSlotInputHandler(Eaagles::Recorder::InputHandler* const msg);
    virtual bool setSlotOutputHandler(Eaagles::Recorder::OutputHandler* const msg);

private:
   void initData();

   SPtr<Eaagles::Recorder::InputHandler> inputHandler;
   SPtr<Eaagles::Recorder::OutputHandler> outputHandler;
};

}

#endif
