
#ifndef __SimIoHandler_H__
#define __SimIoHandler_H__

#include "openeaagles/base/io/IoHandler.hpp"

//------------------------------------------------------------------------------
// Class:  SimIoHandler
//
// Description:  Handles the flow of I/O data to and from the
//               stick and throttle hardware.
//------------------------------------------------------------------------------
class SimIoHandler : public oe::base::IoHandler
{
   DECLARE_SUBCLASS(SimIoHandler, oe::base::IoHandler)

public:
   SimIoHandler();

   virtual void inputDevices(const double dt) override;

protected:
   virtual void clear() override;

private:
   bool rstSw1 {};
   bool frzSw1 {};
   bool wpnReloadSw1 {};

   bool wpnRelSw1 {};
   bool trgSw1 {};
   bool tgtStepSw1 {};
   bool tgtDesSw1 {};
   bool rtn2SrchSw1 {};

   bool autopilotSw1 {};
   bool incStptSw1 {};
   bool decStptSw1 {};
};

#endif
