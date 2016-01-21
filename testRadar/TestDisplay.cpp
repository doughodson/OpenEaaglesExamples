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

namespace oe {
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
TestDisplay::TestDisplay() : myStation(nullptr)
{
   STANDARD_CONSTRUCTOR()

   rdrDisplay = nullptr;
   rwrDisplay = nullptr;
   for (unsigned int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = nullptr;
      trkIdx[i] = 0;
   }
   range = 40.0;
}

// copy member data
void TestDisplay::copyData(const TestDisplay& org, const bool)
{
   BaseClass::copyData(org);

   myStation = nullptr;
   for (int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = nullptr;
      trkIdx[i] = 0;
   }

   rdrDisplay = nullptr;
   rwrDisplay = nullptr;
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
    if ( getSimulation() != nullptr ) {
        getSimulation()->event(RESET_EVENT);
    }
    return true;
}

// freeze simulation
bool TestDisplay::onFreezeKey()
{
    if ( getSimulation() != nullptr ) {
        Basic::Boolean newFrz( !getSimulation()->isFrozen() );
        getSimulation()->event(FREEZE_EVENT, &newFrz);
    }
    return true;
}

// Weapon Release Switch
bool TestDisplay::onWpnRelKey()
{
    if (getOwnship() != nullptr) {
        getOwnship()->event(WPN_REL_EVENT);
    }
    return true;
}

// Pre-Release Switch
bool TestDisplay::onPreRelKey()
{
    if (getOwnship() != nullptr) {
       Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            Simulation::Weapon* wpn = sms->getCurrentWeapon();
            if (wpn != nullptr) {
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
    if (getOwnship() != nullptr) {
        getOwnship()->event(TGT_STEP_EVENT);
    }
    return true;
}

// Target Step Switch
bool TestDisplay::onRtn2SearchKey()
{
    if (getOwnship() != nullptr) {
        getOwnship()->event(SENSOR_RTS);
    }
    return true;
}


// Air to Air mode key
bool TestDisplay::onAir2AirKey()
{
    if (getOwnship() != nullptr) {
       Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            sms->setWeaponDeliveryMode(Simulation::StoresMgr::A2A);
            std::cout << "Set A/A Weapon Mode!" << std::endl;
        }
    }
    return true;
}

// Air to Ground mode key
bool TestDisplay::onAir2GndKey()
{
    if (getOwnship() != nullptr) {
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            sms->setWeaponDeliveryMode(Simulation::StoresMgr::A2G);
            std::cout << "Set A/G Weapon Mode!" << std::endl;
        }
    }
    return true;
}

// Increase range key
bool TestDisplay::onIncRngKey()
{
    if (getOwnship() != nullptr) {
        Simulation::Radar* rdr = nullptr;
        {
           Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
           if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
        }
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
            }
        }
        if (rdr != nullptr) {
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
    if (getOwnship() != nullptr) {
        Simulation::Radar* rdr = nullptr;
        {
           Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
           if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
        }
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            // But could be GMTI
            if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
            }
        }
        if (rdr != nullptr) {
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
   if ( ts != nullptr ) {
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
        rdrDisplay = nullptr;
        Basic::Pair* p = findByType(typeid(DspRadar));
        if (p != nullptr) rdrDisplay = dynamic_cast<DspRadar*>( p->object() );
    }
    if (rdrDisplay != nullptr && getOwnship() != nullptr) {
        // Default is TWS
        Simulation::Radar* rdr = nullptr;
        {
           Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
           if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
        }
        Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
            }
        }
        rdrDisplay->setRadar(rdr);
    }


    // Find and update the test RWR display
    {
        rwrDisplay = nullptr;
        Basic::Pair* p = findByType(typeid(DspRwr));
        if (p != nullptr) rwrDisplay = dynamic_cast<DspRwr*>( p->object() );
    }
    if (rwrDisplay != nullptr && getOwnship() != nullptr) {
        Simulation::Rwr* rwr = nullptr;
        Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Simulation::Rwr));
        if (pair != nullptr) rwr = static_cast<Simulation::Rwr*>(pair->object());
        rwrDisplay->setRwr(rwr);
    }
    
   // Send flight data to readouts
   if (getOwnship() != nullptr) {

      {
         Simulation::Radar* rdr = nullptr;
         {
            Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Tws));
            if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
         }
         Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
         if (sms != nullptr) {
               // But could be GMTI ...
               if (sms->isWeaponDeliveryMode(Simulation::StoresMgr::A2G)) {
                  Basic::Pair* pair = getOwnship()->getSensorByType(typeid(Sensor::Gmti));
                  if (pair != nullptr) rdr = static_cast<Simulation::Radar*>(pair->object());
               }
         }
         if (rdr != nullptr) range = rdr->getRange();
      }

      send("hsi", UPDATE_VALUE5, getOwnship()->getHeadingR(), headingSD);
      send("rangeRO", UPDATE_VALUE, range, rangeSD);


      // Maintain Air Tracks
      Basic::Pair* pair = findByName("airTracks");
      if (pair != nullptr) {
         BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
         if (myLoader != nullptr) {
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
      if (pair != nullptr) {
         BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
         if (myLoader != nullptr) {
            BasicGL::Graphic* selected = pick(0);
            if (selected != nullptr) {
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
        if (tracks[i] != nullptr) codes[i] = -1;  // needs to be matched
        else codes[i] = 0;                  // empty slot
    }
    
    // find all air vehicles within range
    {
        // get the player list
        Simulation::Simulation* sim = getSimulation();
        Basic::PairStream* plist = sim->getPlayers();
        
        // search for air vehicles or missiles within range
        Basic::List::Item* item = plist->getFirstItem();
        while (item != nullptr && nNewTracks < maxTracks) {
       
            Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
            Simulation::Player* p = static_cast<Simulation::Player*>(pair->object());
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
            tracks[i] = nullptr;      // clear the player pointer
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
                  if (newTracks[inew]->getSensorByType(typeid(Simulation::Jammer)) == nullptr) {
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
                trkIdx[islot] = loader->addSymbol( type, nullptr);
               if (trkIdx[islot] == 0) {
                    // it didn't make it in for some unknown reason
                    tracks[islot]->unref();
                    tracks[islot] = nullptr;
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
        if (tracks[i] != nullptr && trkIdx[i] != 0) {
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
    Simulation::Player* p = nullptr;
    Simulation::Station* sta = getStation();
    if (sta != nullptr) p = sta->getOwnship();
    return p;
}

Simulation::Simulation* TestDisplay::getSimulation()
{
    Simulation::Simulation* s = nullptr;
    Simulation::Station* sta = getStation();
    if (sta != nullptr) s = sta->getSimulation();
    return s;
}

Simulation::Station* TestDisplay::getStation()
{
    if (myStation == nullptr) {
        Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
        if (s != nullptr) myStation = s;
    }
    return myStation;
}

} // End Test namespace
} // End oe namespace
