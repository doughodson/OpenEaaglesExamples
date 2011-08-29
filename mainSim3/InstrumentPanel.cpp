//------------------------------------------------------------------------------
// Glut Display
//------------------------------------------------------------------------------
#include "InstrumentPanel.h"
#include "SimStation.h"
#include "SimPlayer.h"

#include "openeaagles/instruments/eadi3D/Eadi3DPage.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/Boolean.h"
#include <GL/glut.h>


namespace Eaagles {
namespace Sim3 {


IMPLEMENT_SUBCLASS(InstrumentPanel,"InstrumentPanel")
EMPTY_SERIALIZER(InstrumentPanel)

EMPTY_SLOTTABLE(InstrumentPanel)

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
InstrumentPanel::InstrumentPanel() 
{
   STANDARD_CONSTRUCTOR()

   myStation = 0;
}

//------------------------------------------------------------------------------
// copyData() - copies one object to another
//------------------------------------------------------------------------------
void InstrumentPanel::copyData(const InstrumentPanel& org, const bool) 
{
   BaseClass::copyData(org);

   myStation = 0;
}

//------------------------------------------------------------------------------
// deleteData() -- delete this object's data
//------------------------------------------------------------------------------
void InstrumentPanel::deleteData()
{
   myStation = 0;
}


//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
Simulation::Player* InstrumentPanel::getOwnship()
{
   Simulation::Player* p = 0;
   Simulation::Station* sta = getStation();
   if (sta != 0) p = sta->getOwnship();
   return p;
}

Simulation::Simulation* InstrumentPanel::getSimulation()
{
   Simulation::Simulation* s = 0;
   Simulation::Station* sta = getStation();
   if (sta != 0) s = sta->getSimulation();
   return s;
}

Simulation::Station* InstrumentPanel::getStation()
{
   if (myStation == 0) {
      Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
      if (s != 0) myStation = s;
   }
   return myStation;
}


//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void InstrumentPanel::updateData(const LCreal dt)
{
    // update our base class first
    BaseClass::updateData(dt);
    
    // try to get an Sim3 first.  If that doesn't work, then get a generic air vehicle
    // Get the data from our ownship, if we have a valid one.  Else everything goes to a default value
    // we need to dynamically cast to an AirVehicle* for this instrument panel
    Simulation::AirVehicle* tempOwnship = dynamic_cast<Simulation::AirVehicle*>( getOwnship() );
    if (tempOwnship != 0) {    
        tempOwnship->ref();
#if 0
        sBrakePos = tempOwnship->getSpeedBrakePosition();
#endif
        gForce = tempOwnship->getGload();
        aoa = tempOwnship->getAngleOfAttackD();
        airSpeed = tempOwnship->getCalibratedAirspeed();
        heading = tempOwnship->getHeadingD();
        altitude = tempOwnship->getAltitudeFt();
        vvi = tempOwnship->getVelocity();
        slip = tempOwnship->getSideSlipD();
        pitch = tempOwnship->getPitchD();
        roll = tempOwnship->getRollD();
	mach = tempOwnship->getMach();
	gload = tempOwnship->getGload();

        tempOwnship->unref();
    }
    else {
        SimPlayer* player = dynamic_cast<SimPlayer*>( getOwnship() );
        if (player != 0) {
            player->ref();

#if 0
            course = (LCreal) player->getCourse();
            sBrakePos = player->getSpeedBrakePosition();
#endif
            gForce = player->getGload();
            aoa = player->getAngleOfAttackD();
            airSpeed = player->getCalibratedAirspeed();
            heading = player->getHeadingD();
            altitude = player->getAltitudeFt();
            vvi = player->getVelocity();
            slip = player->getSideSlipD();
            pitch = player->getPitchD();
            roll = player->getRollD();
	    mach = player->getMach();
	    gload = 1.0;

            player->unref();
	}
        else {
#if 0
            sBrakePos = 0;
            course = 0;
#endif
            gForce = 1.0;
            aoa = 0;
            dme = 0;
            airSpeed = 0;
            heading = 0;
            altitude = 0;
            vvi.set(0,0,0);
            bpAngle = 0;  
        }
    }

    Basic::Pair* a = findSubpageByType(typeid(Instruments::Eadi3DPage));
    if (a != 0) {
        Instruments::Eadi3DPage* eadi = dynamic_cast<Instruments::Eadi3DPage*>(a->object());
        if (eadi != 0) {
            eadi->setAltitude(altitude);
            eadi->setAirspeed(airSpeed);
            eadi->setHeading(heading);
            eadi->setAOA(aoa);
            eadi->setVVI(-vvi.z() * Basic::Distance::M2FT * 60.0);
            eadi->setPitch(pitch);
            eadi->setRoll(roll);
            eadi->setMach(mach);
	    eadi->setGLoad(gload);
	    eadi->setLandingMode(false);
	    eadi->setPitchSteeringCmd(0.0);
	    eadi->setRollSteeringCmd(0.0);
	    eadi->setPitchSteeringValid(false);
	    eadi->setRollSteeringValid(false);
	    eadi->setGlideslopeDev(0.0);
	    eadi->setLocalizerDev(0.0);
	    eadi->setTurnRate(0.0);
	    eadi->setSlipInd(0.0);
	    eadi->setGlideslopeValid(false);
	    eadi->setLocalizerValid(false);
        }
    }
}

//------------------------------------------------------------------------------
// keyboardEvent() - pass keyboard events to the correct destination
//------------------------------------------------------------------------------
void InstrumentPanel::keyboardEvent(const int key)
{
    Simulation::Player* plyr = getOwnship();
    if (plyr != 0) {
        Simulation::Simulation* sim = plyr->getSimulation();
        if (sim != 0) {
	    switch (key) {
	    case 'f':
	    case 'F':
		{
		    Basic::Boolean newFrz(!sim->isFrozen());
		    sim->event(FREEZE_EVENT, &newFrz);
		}
		return;
		break;
	
	    case 'r':
	    case 'R':
	        sim->event(RESET_EVENT);
		return;
		break;

	    default:
		break;
	    }
	}
    }
    BaseClass::keyboardEvent(key);
}

#if 0
//------------------------------------------------------------------------------
// onButtonEvent() - pass button events to the correct destination
//------------------------------------------------------------------------------
void InstrumentPanel::buttonEvent(const int b)
{
    Basic::PairStream* sd = subDisplays();
    if (sd == 0) return;

} 

// mouseEvent() - takes care of the selection of graphics
void InstrumentPanel::mouseEvent(const int button, const int state, const int x, const int y)
{   
}
#endif

//------------------------------------------------------------------------------
// getSlotByIndex() for InstrumentPanel
//------------------------------------------------------------------------------
#if 0
Basic::Object* InstrumentPanel::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}
#endif

} // end Sim3 namespace
} // end Eaagles namespace
