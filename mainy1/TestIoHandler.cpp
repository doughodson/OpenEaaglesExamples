//------------------------------------------------------------------------------
// Class: TestIoHandler
//------------------------------------------------------------------------------

#include "TestIoHandler.h"
#include "SimStation.h"
#include "configs/f16HotasIo.h"

#include "openeaagles/simulation/Autopilot.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Navigation.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/Route.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/IoData.h"

namespace Eaagles {
namespace Example {

//==============================================================================
// TestIoHandler
//==============================================================================

IMPLEMENT_SUBCLASS(TestIoHandler,"TestIoHandler")
EMPTY_SLOTTABLE(TestIoHandler)
EMPTY_SERIALIZER(TestIoHandler)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestIoHandler::TestIoHandler()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

//------------------------------------------------------------------------------
// initData -- initialize our data for the first time
//------------------------------------------------------------------------------
void TestIoHandler::initData()
{
   rstSw1 = false;
   frzSw1 = false;
   wpnReloadSw1 = false;

   wpnRelSw1 = false;
   trgSw1 = false;
   tgtStepSw1 = false;
   tgtDesSw1 = false;
   rtn2SrchSw1 = false;

   autopilotSw1 = false;
   incStptSw1 = false;
   decStptSw1 = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void TestIoHandler::copyData(const TestIoHandler& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();

   rstSw1 = org.rstSw1;
   frzSw1 = org.frzSw1;
   wpnReloadSw1 = org.wpnReloadSw1;

   wpnRelSw1 = org.wpnRelSw1;
   trgSw1 = org.trgSw1;
   tgtStepSw1 = org.tgtStepSw1;
   tgtDesSw1 = org.tgtDesSw1;
   rtn2SrchSw1 = org.rtn2SrchSw1;

   autopilotSw1 = org.autopilotSw1;
   incStptSw1 = org.incStptSw1;
   decStptSw1 = org.decStptSw1;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void TestIoHandler::deleteData()
{
}

//------------------------------------------------------------------------------
// Handle input devices
//------------------------------------------------------------------------------
void TestIoHandler::inputDevices(const LCreal dt)
{
   BaseClass::inputDevices(dt);

   // ---
   // get the Input data buffer
   // ---
   const Basic::IoData* const inData = getInputData();

   // ---
   // get the Station, Simulation and our ownship player
   // ---
   SimStation* const sta = (SimStation*)( findContainerByType(typeid(SimStation)) );

   Simulation::Simulation* sim = 0;
   Simulation::AirVehicle* av = 0;

   if (sta != 0) {
      sim = sta->getSimulation();
      av = dynamic_cast<Simulation::AirVehicle*>(sta->getOwnship());
   }

   // ---
   // If we have everything we need ....
   // ---
   if (av != 0 && sim != 0 && inData != 0) {

      // find the (optional) autopilot
      Simulation::Autopilot* ap = 0;
      {
         Basic::Pair* p = av->getPilotByType( typeid( Simulation::Autopilot) );
         if (p != 0) ap = (Simulation::Autopilot*)( p->object() );
      }

      // ------------------------------------------------------------
      // Simulation Control Inputs
      // ------------------------------------------------------------

      {
         bool enabled = false;
         inData->getDiscreteInput(CTL_ENABLE_SW, &enabled);

         {  // Toggle simulation freeze
            bool sw = false;
            inData->getDiscreteInput(FREEZE_SW, &sw);
            bool frzSw = sw && enabled;
            if(frzSw && !frzSw1) {
               Basic::Boolean newFrz( !sim->isFrozen() );
               sim->event(FREEZE_EVENT, &newFrz);
            }
            frzSw1 = frzSw;
         }

         {  // Send a reset pulse to the station
            bool sw = false;
            inData->getDiscreteInput(RESET_SW, &sw);
            bool rstSw = sw && enabled;
            if(rstSw && !rstSw1) {
               sta->event(RESET_EVENT);
            }
            rstSw1 = rstSw;
         }

         {  // Send a weapons reload pulse to the station
            bool sw = false;
            inData->getDiscreteInput(RELOAD_SW, &sw);
            bool wpnReloadSw = sw && enabled;
            if(wpnReloadSw && !wpnReloadSw1) {
               sta->event(WPN_RELOAD);
            }
            wpnReloadSw1 = wpnReloadSw;
         }

      }

      // ------------------------------------------------------------
      // Flight Control Inputs
      // ------------------------------------------------------------

      {  // Process Roll Input
         LCreal ai = 0;
         inData->getAnalogInput(ROLL_AI, &ai);
         LCreal aiLim = alim(ai, 1.0f);
         if (ap != 0) ap->setControlStickRollInput(aiLim);
         else av->setControlStickRollInput(aiLim);
      }

      {  // Process Pitch Input
         LCreal ai = 0;
         inData->getAnalogInput(PITCH_AI, &ai);
         LCreal aiLim = alim(ai, 1.0f);
         if (ap != 0) ap->setControlStickPitchInput(aiLim);
         else av->setControlStickPitchInput(aiLim);
      }

      {  // Process Rudder Input
         LCreal ai = 0;
         inData->getAnalogInput(RUDDER_AI, &ai);
         LCreal aiLim = alim(ai, 1.0f);
         av->setRudderPedalInput(aiLim);
      }

      {  // Process Throttle Input
         LCreal value = 0;
         inData->getAnalogInput(THROTTLE_AI, &value);

         if (value < 0.0f) value = 0.0f;
         else if (value > 2.0f) value = 2.0f;

         if (ap != 0) ap->setThrottles(&value,1);
         else av->setThrottles(&value,1);
      }

      { // Weapons Release
         bool sw = false;
         inData->getDiscreteInput(PICKLE_SW, &sw);
         if(sw != wpnRelSw1) {
            Basic::Boolean sw(sw);
            av->event(WPN_REL_EVENT, &sw);
         }
         wpnRelSw1 = sw;
      }

      { // Trigger switch
         bool sw = false;
         inData->getDiscreteInput(TRIGGER_SW2, &sw);
         if(sw != trgSw1) {
            Basic::Boolean sw(sw);
            av->event(TRIGGER_SW_EVENT, &sw);
         }
         trgSw1 = sw;
      }

      { // Target Step (reject)
         bool sw = false;
         inData->getDiscreteInput(TMS_RIGHT_SW, &sw);
         if(sw && !tgtStepSw1) {
            av->event(TGT_STEP_EVENT);
         }
         tgtStepSw1 = sw;
      }

      { // Target Designate
         bool sw = false;
         inData->getDiscreteInput(TMS_UP_SW, &sw);
         if(sw && !tgtDesSw1) {
            av->event(TGT_DESIGNATE);
         }
         tgtDesSw1 = sw;
      }

      { // Return-To-Search
         bool sw = false;
         inData->getDiscreteInput(TMS_DOWN_SW, &sw);
         if(sw && !rtn2SrchSw1) {
            av->event(SENSOR_RTS);
         }
         rtn2SrchSw1 = sw;
      }

      { // Autopilot disengage
         bool autopilotSw = false;
         inData->getDiscreteInput(PADDLE_SW, &autopilotSw);
         if (autopilotSw && !autopilotSw1) {
            Simulation::Autopilot* ap = dynamic_cast<Simulation::Autopilot*>(av->getPilot());
            if (ap != 0) {
               ap->setHeadingHoldMode(false);
               ap->setAltitudeHoldMode(false);
               ap->setVelocityHoldMode(false);
               ap->setLoiterMode(false);
               ap->setNavMode(false);
            }
         }
         autopilotSw1 = autopilotSw;
      }

      { // Speedbrake switch  
         bool sbExtSw = false;
         bool sbRetSw = false;
         inData->getDiscreteInput(SB_EXT_SW, &sbExtSw);
         inData->getDiscreteInput(SB_RET_SW, &sbRetSw);

         LCreal sb = 0.0;
         if(sbExtSw) sb = -1.0f;
         if(sbRetSw) sb =  1.0f;
         av->setSpeedBrakesSwitch(sb);
      }

      { // Steerpoint increment
         bool incStptSw = false;
         inData->getDiscreteInput(DMS_UP_SW, &incStptSw);
         if(incStptSw && !incStptSw1) {
            // find our route and increment the steerpoint
            Simulation::Navigation* myNav = av->getNavigation();
            if (myNav != 0) {
               myNav->ref();
               Simulation::Route* myRoute = myNav->getPriRoute();
               if (myRoute != 0) {
                  myRoute->ref();
                  myRoute->incStpt();
                  myRoute->unref();
               }
            }
         }
         incStptSw1 = incStptSw;
      }

      { // Steerpoint decrement
         bool decStptSw = false;
         inData->getDiscreteInput(DMS_DOWN_SW, &decStptSw);
         if(decStptSw && !decStptSw1) {
            // find our route and increment the steerpoint
            Simulation::Navigation* myNav = av->getNavigation();
            if (myNav != 0) {
               myNav->ref();
               Simulation::Route* myRoute = myNav->getPriRoute();
               if (myRoute != 0) {
                  myRoute->ref();
                  myRoute->decStpt();
                  myRoute->unref();
               }
            }
         }
         decStptSw1 = decStptSw;
      }


   }

}

// -----------------------------------------------------------------------------
// Clear our data
// (called from Basic::TestIoHandler::reset())
// -----------------------------------------------------------------------------
void TestIoHandler::clear()
{
}

} // End Example namespace
} // end Eaagles namespace
