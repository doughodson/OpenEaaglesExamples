//------------------------------------------------------------------------------
// Class: TestIoHandler
//------------------------------------------------------------------------------
#ifndef __oe_test_TestIoHandler_H___
#define __oe_test_TestIoHandler_H___

#include "openeaagles/base/IoHandler.h"

namespace oe {
   namespace simulation { class AirVehicle; }

namespace test {

//------------------------------------------------------------------------------
// Class: TestIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware.
//------------------------------------------------------------------------------
class TestIoHandler : public base::IoHandler {
   DECLARE_SUBCLASS(TestIoHandler,base::IoHandler)

public:
   TestIoHandler();

   virtual void inputDevices(const double dt) override;

protected:
   virtual void clear() override;

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
}

#endif
