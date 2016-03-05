//------------------------------------------------------------------------------
// Class: SimIoHandler
//------------------------------------------------------------------------------
#ifndef __oe_example_SimIoHandler_H__
#define __oe_example_SimIoHandler_H__

#include "openeaagles/base/IoHandler.h"

namespace oe {
   namespace simulation { class AirVehicle; }

namespace example {

//------------------------------------------------------------------------------
// Class:  SimIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware.
//------------------------------------------------------------------------------
class SimIoHandler : public base::IoHandler
{
   DECLARE_SUBCLASS(SimIoHandler,base::IoHandler)

public:
   SimIoHandler();

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

} // end example
} // end oe namespace

#endif
