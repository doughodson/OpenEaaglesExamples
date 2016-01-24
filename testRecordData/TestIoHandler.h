//------------------------------------------------------------------------------
// Class: TestIoHandler
//------------------------------------------------------------------------------
#ifndef __oe_test_TestIoHandler_H___
#define __oe_test_TestIoHandler_H___

#include "openeaagles/basic/IoHandler.h"

namespace oe {
   namespace Simulation { class AirVehicle; }

namespace test {

//------------------------------------------------------------------------------
// Class: TestIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware.
//------------------------------------------------------------------------------
class TestIoHandler : public basic::IoHandler {
   DECLARE_SUBCLASS(TestIoHandler,basic::IoHandler)

public:
   TestIoHandler();

   void inputDevices(const LCreal dt) override;

protected:
   void clear() override;

private:
   void initData();

   bool rstSw1;
   bool frzSw1;
   bool wpnReloadSw1;

   bool wpnRelSw1;
   bool trgSw1;
   bool tgtStepSw1;
   bool tgtDesSw1;
   bool rtn2SrchSw1;

   bool autopilotSw1;
   bool incStptSw1;
   bool decStptSw1;
};

} // end test
} // end oe namespace

#endif
