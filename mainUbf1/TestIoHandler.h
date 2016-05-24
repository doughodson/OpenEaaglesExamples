
#ifndef __oe_example_TestIoHandler_H__
#define __oe_example_TestIoHandler_H__

#include "openeaagles/base/IoHandler.h"

namespace oe {
   namespace simulation { class AirVehicle; }

namespace example {

//------------------------------------------------------------------------------
// Class: TestIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware
//------------------------------------------------------------------------------
class TestIoHandler : public base::IoHandler
{
   DECLARE_SUBCLASS(TestIoHandler, base::IoHandler)

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

}
}

#endif
