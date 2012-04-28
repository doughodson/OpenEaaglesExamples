//
// PlaneAgent
//

#include "PlaneAgent.h"

#include "openeaagles/ubf/Behavior.h"
#include "openeaagles/ubf/Action.h"

#include "PlaneState.h"
#include "PlaneAction.h"

#include "openeaagles/basic/PairStream.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/StoresMgr.h"
#include "openeaagles/simulation/AirVehicle.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneAgent, "PlaneAgent")
EMPTY_SLOTTABLE(PlaneAgent)
EMPTY_SERIALIZER(PlaneAgent)
EMPTY_COPYDATA(PlaneAgent)
EMPTY_DELETEDATA(PlaneAgent)

PlaneAgent::PlaneAgent()
{
   STANDARD_CONSTRUCTOR()

   // create and set state
   PlaneState* planeState = new PlaneState;
   setState(planeState);
   planeState->unref();

   setup = false;
}

void PlaneAgent::executeAction(const Ubf::Action* const action)
{
   Eaagles::Simulation::Player* ownship = getOwnship();

   //Set weapons to anti-aircraft mode.
   //This could be moved into actions and behaviors if desired, here for convenience
   if (!setup) {
      Eaagles::Simulation::StoresMgr* sms = ownship->getStoresManagement();
      if (sms != 0) {
         sms->setWeaponDeliveryMode(Eaagles::Simulation::StoresMgr::A2A);
         std::cout << "Set A/A Weapon Mode!" << std::endl;

         setup = true;
      }
   }

   const PlaneAction* planeAction = dynamic_cast<const PlaneAction*>(action);
   Eaagles::Simulation::AirVehicle* airVehicle = dynamic_cast<Eaagles::Simulation::AirVehicle*>(ownship);

   airVehicle->setControlStick((LCreal)planeAction->getRoll(), (LCreal)planeAction->getPitch());
	
   // set throttle to engines(assuming there are 8 or less)
   LCreal throttles[8];
   for(int i = 0 ; i < airVehicle->getNumberOfEngines() ; i++) {
      throttles[i] = (LCreal)planeAction->getThrottle();
   }
   if (planeAction->isThrottleChanged()) {
      airVehicle->setThrottles(throttles,2);
   }
   if(planeAction->isPitchTrimChanged()) {
      airVehicle->setTrimSwitch(0, (LCreal)planeAction->getPitchTrim());
   }
   //airVehicle->setRudderPedalInput(planeAction->getHeading());
   //airVehicle->setVelocity(0, 0, 0);
	
   if (planeAction->getFireMissile()) {
      airVehicle->event(WPN_REL_EVENT);
      //WPN_REL_EVENT         = 1405,  // Passes requested switch state as Boolean
                                       // or no argument for one-shot event
   }
}

}
}

