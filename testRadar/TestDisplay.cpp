//------------------------------------------------------------------------------
// Class: TestDisplay
//------------------------------------------------------------------------------
#include "TestDisplay.h"
#include "TestStation.h"
#include "DspRadar.h"
#include "DspRwr.h"

#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Missile.h"
#include "openeaagles/simulation/Jammer.h"
#include "openeaagles/simulation/Radar.h"
#include "openeaagles/simulation/Rwr.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/StoresMgr.h"
#include "openeaagles/simulation/Weapon.h"
#include "openeaagles/sensors/Gmti.h"
#include "openeaagles/sensors/Tws.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basicGL/SymbolLoader.h"
#include <GL/glut.h>

namespace Eaagles {
namespace Test {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestDisplay,"TestDisplay")
EMPTY_SERIALIZER(TestDisplay)
EMPTY_DELETEDATA(TestDisplay)

// Event() map
BEGIN_EVENT_HANDLER(TestDisplay)
   ON_EVENT('r',onResetKey)        // Station Reset
   ON_EVENT('R',onResetKey)        // Station Reset
   ON_EVENT('f',onFreezeKey)       // Simulation Freeze
   ON_EVENT('F',onFreezeKey)       // Simulation Freeze
   ON_EVENT('l',onWpnRelKey)       // Launch
   ON_EVENT('L',onWpnRelKey)       // Launch
   ON_EVENT('p',onPreRelKey)       // Pre-launch
   ON_EVENT('P',onPreRelKey)       // Pre-launch
   ON_EVENT('s',onTgtStepKey)      // Step target
   ON_EVENT('S',onTgtStepKey)      // Step target
   ON_EVENT('2',onRtn2SearchKey)   // Return to search
   ON_EVENT('a',onAir2AirKey)      // A/A mode toggle
   ON_EVENT('A',onAir2AirKey)      // A/A mode toggle
   ON_EVENT('g',onAir2GndKey)      // A/G mode toggle
   ON_EVENT('G',onAir2GndKey)      // A/G mode toggle
   ON_EVENT('i',onIncRngKey)       // Increase range
   ON_EVENT('I',onIncRngKey)       // Increase range
   ON_EVENT('d',onDecRngKey)       // Decrease range
   ON_EVENT('D',onDecRngKey)       // Decrease range
   ON_EVENT('+',onStepOwnshipKey)  // Step ownship
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// constructor
TestDisplay::TestDisplay() : myStation(0)
{
   STANDARD_CONSTRUCTOR()

   rdrDisplay = 0;
   rwrDisplay = 0;
   for (unsigned int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = 0;
      trkIdx[i] = 0;
   }
   range = 40.0;
}

// copy member data
void TestDisplay::copyData(const TestDisplay& org, const bool)
{
   BaseClass::copyData(org);

   myStation = 0;
   for (int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = 0;
      trkIdx[i] = 0;
   }

   rdrDisplay = 0;
   rwrDisplay = 0;
   range = org.range;

   rangeSD.empty();
   headingSD.empty();
}


//------------------------------------------------------------------------------
// Event handlers
//------------------------------------------------------------------------------

// reset simulation
bool TestDisplay::onResetKey()
{
    if ( getSimulation() != 0 ) {
        getSimulation()->event(RESET_EVENT);
    }
    return true;
}

// freeze simulation
bool TestDisplay::onFreezeKey()
{
    if ( getSimulation() != 0 ) {
        Basic::Boolean newFrz( !getSimulation()->isFrozen() );
        getSimulation()->event(FREEZE_EVENT, &newFrz);
    }
    return true;
}

// Weapon Release Switch
bool TestDisplay::onWpnRelKey()
{
    if (getOwnship() != 0) {
        getOwnship()->event(WPN_REL_EVENT);
    }
    return true;
}

// Pre-Release Switch
bool TestDisplay::onPreRelKey()
{
    if (getOwnship() != 0) {
       Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            Simulation::Weapon* wpn = sms->getCurrentWeapon();
            if (wpn != 0) {
               wpn->prerelease();
               std::cout << "Prelaunched wpn = " << wpn << std::endl;
            }
        }
    }
    return true;
}


// Target Step Switch
bool TestDisplay::onTgtStepKey()
{
    if (getOwnship() != 0) {
        getOwnship()->event(TGT_STEP_EVENT);
    }
    return true;
}

// Target Step Switch
bool TestDisplay::onRtn2SearchKey()
{
    if (getOwnship() != 0) {
        getOwnship()->event(SENSOR_RTS);
    }
    return true;
}


// Air to Air mode key
bool TestDisplay::onAir2AirKey()
{
    if (getOwnship() != 0) {
       Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            sms->setWeaponDeliveryMode(Simulation::StoresMgr::A2A);
            std::cout << "Set A/A Weapon Mode!" << std::endl;
        }
    }
    return true;
}

// Air to Ground mode key
bool TestDisplay::onAir2GndKey()
{
    if (getOwnship() != 0) {
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            sms->setWeaponDeliveryMode(Simulation::StoresMgr::A2G);
            std::cout << "Set A/G Weapon Mode!" << std::endl;
        }
    }
    return true;
}

// Increase range key
bool TestDisplay::onIncRngKey()
{
    if (getOwnship() != 0) {
        Simulation::Radar* rdr = 0;
        {
           Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
           if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
        }
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
            }
        }
        if (rdr != 0) {
            rdr->incRange();
        }
        else {
            range = range * 2.0f;
        }
    }
    return true;
}

// Decrease range key
bool TestDisplay::onDecRngKey()
{
    if (getOwnship() != 0) {
        Simulation::Radar* rdr = 0;
        {
           Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
           if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
        }
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
            }
        }
        if (rdr != 0) {
            rdr->decRange();
        }
        else {
            range = range / 2.0f;
        }
    }
    return true;
}

// Step ownship key
bool TestDisplay::onStepOwnshipKey()
{
   TestStation* ts = dynamic_cast<TestStation*>(getStation());
   if ( ts != 0 ) {
      ts->stepOwnshipPlayer();
   }
   return true;
}


//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestDisplay::updateData(const LCreal dt)
{
    // Find and update the test RADAR display
    {
        rdrDisplay = 0;
        Basic::Pair* p = findByType(typeid(DspRadar));
        if (p != 0) rdrDisplay = dynamic_cast<DspRadar*>( p->object() );
    }
    if (rdrDisplay != 0 && getOwnship() != 0) {
        // Default is TWS
        Simulation::Radar* rdr = 0;
        {
           Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
           if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
        }
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
            }
        }
        rdrDisplay->setRadar(rdr);
    }


    // Find and update the test RWR display
    {
        rwrDisplay = 0;
        Basic::Pair* p = findByType(typeid(DspRwr));
        if (p != 0) rwrDisplay = dynamic_cast<DspRwr*>( p->object() );
    }
    if (rwrDisplay != 0 && getOwnship() != 0) {
        Simulation::Rwr* rwr = 0;
        Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Simulation::Rwr));
        if (pair != 0) rwr = (Simulation::Rwr*)( pair->object() );
        rwrDisplay->setRwr(rwr);
    }
    
   // Send flight data to readouts
   if (getOwnship() != 0) {

      {
         Simulation::Radar* rdr = 0;
         {
            Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
            if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
         }
         Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
         if (sms != 0) {
               // But could be GMTI ...
               if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                  Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                  if (pair != 0) rdr = (Simulation::Radar*)( pair->object() );
               }
         }
         if (rdr != 0) range = rdr->getRange();
      }

      send("hsi", UPDATE_VALUE5, getOwnship()->getHeadingR(), headingSD);
      send("rangeRO", UPDATE_VALUE, range, rangeSD);


      // Maintain Air Tracks
      Basic::Pair* pair = findByName("airTracks");
      if (pair != 0) {
         BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
         if (myLoader != 0) {
            myLoader->setRange(range);
            myLoader->setHeadingDeg(getOwnship()->getHeadingD());
            myLoader->setNorthUp(false);

            maintainAirTrackSymbols(myLoader, range);
         }
      }        
   }

   // Update base classes stuff
   BaseClass::updateData(dt);
}

//------------------------------------------------------------------------------
// mouseEvent() -- Handle mouse inputs
//------------------------------------------------------------------------------
void TestDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
    setMouse(x,y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      Basic::Pair* pair = findByName("airTracks");
      if (pair != 0) {
         BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
         if (myLoader != 0) {
            BasicGL::Graphic* selected = pick(0);
            if (selected != 0) {
               int idx = myLoader->getSymbolIndex(selected);
               if (idx > 0) {
                  int found = -1;
                  for (int i = 0; found < 0 && i < MAX_TRACKS; i++) {
                     if (idx == trkIdx[i]) found = i;
                  }
                  if (found >= 0) {
                     getStation()->setOwnshipPlayer(tracks[found]);
                  }
               }
            }
         }
      }
    }
}

//------------------------------------------------------------------------------
// maintainAirTrackSymbols() -- maintain the air track symbology
//------------------------------------------------------------------------------
void TestDisplay::maintainAirTrackSymbols(BasicGL::SymbolLoader* loader, const LCreal rng)
{
    int codes[MAX_TRACKS];              // Work codes: empty(0), matched(1), unmatched(-1)
    LCreal rng2 = (rng * rng);          // Range squared (KM * KM)
    
    Simulation::Player* newTracks[MAX_TRACKS];  // New tracks to add
    int nNewTracks = 0;                         // Number of new tracks
    
    // The real maximum number of tracks is the smaller of MAX_TRACKS and the loader's maximum
    int maxTracks = loader->getMaxSymbols();
    if (MAX_TRACKS < maxTracks) maxTracks = MAX_TRACKS;
    
    // Set the initial codes
    for (int i = 0; i < maxTracks; i++) {
        if (tracks[i] != 0) codes[i] = -1;  // needs to be matched
        else codes[i] = 0;                  // empty slot
    }
    
    // find all air vehicles within range
    {
        // get the player list
        Simulation::Simulation* sim = getSimulation();
        Basic::PairStream* plist = sim->getPlayers();
        
        // search for air vehicles or missiles within range
        Basic::List::Item* item = plist->getFirstItem();
        while (item != 0 && nNewTracks < maxTracks) {
       
            Basic::Pair* pair = (Basic::Pair*) item->getValue();
            Simulation::Player* p = (Simulation::Player*)( pair->object() );
            osg::Vec3 rpos = p->getPosition() - getOwnship()->getPosition();
            LCreal x = rpos[0] * Basic::Distance::M2NM;
            LCreal y = rpos[1] * Basic::Distance::M2NM;
            
            if (
               p != getOwnship() && 
               p->isActive() &&
               ((x*x + y*y) < rng2) &&
               (p->isClassType(typeid(Simulation::AirVehicle)) || p->isClassType(typeid(Simulation::Missile))) ) {
                // Ok, it's an active air vehicle or missile that's within range, and it's not us.
                
                // Are we already in the track list?
                bool found = false;
                for (int i = 0; !found && i < maxTracks; i++) {
                    if (p == tracks[i]) {
                        // Yes it is.  So mark the slot as matched!
                        codes[i] = 1;
                        found = true;
                    }
                }
                
                // If not found then add it to the new tracks list
                if (!found) {
                    p->ref();
                    newTracks[nNewTracks++] = p;
                }
                 
            }
            item = item->getNext();
        }
        
        plist->unref();
    }
    
    
    // Now remove any unmatched tracks
    for (int i = 0; i < maxTracks; i++) {
        if (codes[i] == -1) {
            // This is an old symbol that wasn't matched with a valid player
            loader->removeSymbol( trkIdx[i] );
            tracks[i]->unref(); // unref the player
            tracks[i] = 0;      // clear the player pointer
            trkIdx[i] = 0;      // clear the index
            codes[i]  = 0;      // slot is now empty
        }
    }
    
    // Now add any new tracks
    {
        int islot = 0;      // slot index
        int inew = 0;       // new track index
        
        while (inew < nNewTracks && islot < maxTracks) {
            if (codes[islot] == 0) {
                // We have an empty slot, so add the symbol
                
                int type = 4;                                       // unknown
                if (newTracks[inew]->isClassType(typeid(Simulation::AirVehicle))) {
                  if (newTracks[inew]->getSensorByType(typeid(Simulation::Jammer)) == 0) {
                     // non-jammers
                     if (newTracks[inew]->isSide(Simulation::Player::BLUE)) type = 1;      // friend
                     else if (newTracks[inew]->isSide(Simulation::Player::RED)) type = 2; // foe  
                     else type = 3; // neutral/commercial
                  }
                }
                else if (newTracks[inew]->isClassType(typeid(Simulation::Missile))) {
                   type = 5; // Missile
                }


                tracks[islot] = newTracks[inew];
                trkIdx[islot] = loader->addSymbol( type, 0);
               if (trkIdx[islot] == 0) {
                    // it didn't make it in for some unknown reason
                    tracks[islot]->unref();
                    tracks[islot] = 0;
                }
                inew++;
                
            }
            islot++;
        }
       
        // unref any air vehicles that didn't make it
        while (inew < nNewTracks) {
            newTracks[inew++]->unref();
        }
    }    

    // now update the active tracks
    for (int i = 0; i < maxTracks; i++) {
        double osX = getOwnship()->getXPosition();
        double osY = getOwnship()->getYPosition();
        if (tracks[i] != 0 && trkIdx[i] != 0) {
            double xp = tracks[i]->getXPosition() - osX;
            double yp = tracks[i]->getYPosition() - osY;
            loader->updateSymbolPositionXY( trkIdx[i], (xp * Basic::Distance::M2NM), (yp * Basic::Distance::M2NM) );
            loader->updateSymbolHeading( trkIdx[i], tracks[i]->getHeadingD() );
        }
    }

}


//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
Simulation::Player* TestDisplay::getOwnship()
{
    Simulation::Player* p = 0;
    Simulation::Station* sta = getStation();
    if (sta != 0) p = sta->getOwnship();
    return p;
}

Simulation::Simulation* TestDisplay::getSimulation()
{
    Simulation::Simulation* s = 0;
    Simulation::Station* sta = getStation();
    if (sta != 0) s = sta->getSimulation();
    return s;
}

Simulation::Station* TestDisplay::getStation()
{
    if (myStation == 0) {
        Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
        if (s != 0) myStation = s;
    }
    return myStation;
}

} // End Test namespace
} // End Eaagles namespace
