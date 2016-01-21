
#ifndef __oe_example_TestIoHandler_H__
#define __oe_example_TestIoHandler_H__

#include "openeaagles/basic/IoHandler.h"

namespace oe {
   namespace Simulation { class AirVehicle; }

namespace example {

//------------------------------------------------------------------------------
// Class: TestIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware
//------------------------------------------------------------------------------
class TestIoHandler : public Basic::IoHandler
{
   DECLARE_SUBCLASS(TestIoHandler, Basic::IoHandler)

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

} // end example namespace
} // end oe namespace

#endif
