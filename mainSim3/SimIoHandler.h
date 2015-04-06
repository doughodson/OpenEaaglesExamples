//------------------------------------------------------------------------------
// Class: SimIoHandler
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_SimIoHandler_H__
#define __Eaagles_Example_SimIoHandler_H__

#include "openeaagles/basic/IoHandler.h"

namespace Eaagles {
   namespace Simulation { class AirVehicle; }

namespace Example {

//------------------------------------------------------------------------------
// Class:  SimIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware.
//------------------------------------------------------------------------------
class SimIoHandler : public Basic::IoHandler
{
   DECLARE_SUBCLASS(SimIoHandler,Basic::IoHandler)

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

} // end Example
} // end Eaagles namespace

#endif
