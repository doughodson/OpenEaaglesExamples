
#include "TestDisplay.hpp"
#include "SimStation.hpp"
#include "xpanel/DspRadar.hpp"
#include "xpanel/DspRwr.hpp"
#include "xpanel/Pfd.hpp"

#include "openeaagles/models/player/AirVehicle.hpp"
#include "openeaagles/models/player/Missile.hpp"

#include "openeaagles/models/system/Jammer.hpp"
#include "openeaagles/models/system/Radar.hpp"
#include "openeaagles/models/system/Rwr.hpp"
#include "openeaagles/models/system/StoresMgr.hpp"
#include "openeaagles/models/sensor/Gmti.hpp"
#include "openeaagles/models/sensor/Tws.hpp"

#include "openeaagles/simulation/Simulation.hpp"

#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/graphics/SymbolLoader.hpp"
#include <GL/glut.h>

IMPLEMENT_SUBCLASS(TestDisplay, "TestDisplay")
EMPTY_SLOTTABLE(TestDisplay)
EMPTY_SERIALIZER(TestDisplay)
EMPTY_DELETEDATA(TestDisplay)

// Event() map
BEGIN_EVENT_HANDLER(TestDisplay)
   ON_EVENT('r',onResetKey)
   ON_EVENT('R',onResetKey)
   ON_EVENT('f',onFreezeKey)
   ON_EVENT('F',onFreezeKey)
   ON_EVENT('l',onWpnRelKey)
   ON_EVENT('L',onWpnRelKey)
   ON_EVENT('s',onTgtStepKey)
   ON_EVENT('S',onTgtStepKey)
   ON_EVENT('2',onRtn2SearchKey)
   ON_EVENT('a',onAir2AirKey)
   ON_EVENT('A',onAir2AirKey)
   ON_EVENT('g',onAir2GndKey)
   ON_EVENT('G',onAir2GndKey)
   ON_EVENT('i',onIncRngKey)
   ON_EVENT('I',onIncRngKey)
   ON_EVENT('d',onDecRngKey)
   ON_EVENT('D',onDecRngKey)
   ON_EVENT('+',onStepOwnshipKey)
END_EVENT_HANDLER()

TestDisplay::TestDisplay() : myStation(nullptr)
{
   STANDARD_CONSTRUCTOR()

   // ---
   // RADAR, RWR and SA stuff
   // ---
   rdrDisplay = nullptr;
   rwrDisplay = nullptr;
   for (int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = nullptr;
      trkIdx[i] = 0;
   }
   range = 40.0;

   // ---
   // PFD stuff
   // ---

   // pitch and roll
   pitch = 0.0;
   pitchRate = 10.0;
   roll = 0.0;
   rollRate = -9.0;

   // heading and nav stuff
   trueHdg = 0.0;
   tHdgRate = 11.0;
   cmdHdg = 0.0;
   cmdHdgRate = 3.0;

   // airspeed
   airSpd = 0.0;
   airSpdRate = 5.0;

   // altitude
   alt = 10000.0;
   altRate = 80.0;

   // side slip
   slip = 0.0;
   slipRate = 10.0;

   // glideslope
   gSlope = 0.0;
   gSlopeRate = 0.2;

   // lateral deviation
   latDev = 0.0;
   ldRate = 0.3;

   // commanded speed
   cmdSpd = 200.0;

   // commanded alt
   cmdAlt = 6000.0;

   // vvi
   vvi = 0.0;
   vviRate = 500.0;

   // flight director (command bars)
   fDirBank = 0.0;
   fDirBankRate = 4.0;
   fDirPitch = 0.0;
   fDirPitchRate = 7.0;

   // selected barometric pressure
   baro = 0.0;
   baroRate = 10.0;
}

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

   // pitch and roll
   pitch = org.pitch;
   pitchRate = org.pitchRate;
   roll = org.roll;
   rollRate = org.rollRate;

   // hdg and nav
   trueHdg = org.trueHdg;
   tHdgRate = org.tHdgRate;
   cmdHdg = org.cmdHdg;
   cmdHdgRate = org.cmdHdgRate;

   // airspeed
   airSpd = org.airSpd;
   airSpdRate = org.airSpdRate;

   // altitude
   alt = org.alt;
   altRate = org.alt;

   // side slip
   slip = org.slip;
   slipRate = org.slipRate;

   // glideslope
   gSlope = org.gSlope;
   gSlopeRate = org.gSlopeRate;

   // lateral deviation
   latDev = org.latDev;
   ldRate = org.ldRate;

   // commanded speed
   cmdSpd = org.cmdSpd;

   // commanded alt
   cmdAlt = org.cmdAlt;
   vvi = org.vvi;
   vviRate = org.vviRate;

   // flight director (command bars)
   fDirBank = org.fDirBank;
   fDirBankRate = org.fDirBankRate;
   fDirPitch = org.fDirPitch;
   fDirPitchRate = org.fDirPitchRate;

   // selected barometric pressure
   baro = org.baro;
   baroRate = org.baroRate;
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
      oe::base::Boolean newFrz( !getSimulation()->isFrozen() );
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
      oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != nullptr) {
         sms->setWeaponDeliveryMode(oe::models::StoresMgr::A2A);
         std::cout << "Set A/A Weapon Mode!" << std::endl;
      }
   }
   return true;
}

// Air to Ground mode key
bool TestDisplay::onAir2GndKey()
{
   if (getOwnship() != nullptr) {
      oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != nullptr) {
         sms->setWeaponDeliveryMode(oe::models::StoresMgr::A2G);
         std::cout << "Set A/G Weapon Mode!" << std::endl;
      }
   }
   return true;
}

// Increase range key
bool TestDisplay::onIncRngKey()
{
   if (getOwnship() != nullptr) {
      oe::models::Radar* rdr = nullptr;
      {
         oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Tws));
         if (pair != nullptr) rdr = static_cast<oe::models::Radar*>( pair->object() );
      }
      oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != nullptr) {
         // But could be GMTI ...
         if (sms->isWeaponDeliveryMode(oe::models::StoresMgr::A2G)) {
            oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Gmti));
            if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
         }
      }
      if (rdr != nullptr) {
         rdr->incRange();
      }
      else {
         range = range * 2.0;
      }
   }
   return true;
}

// Decrease range key
bool TestDisplay::onDecRngKey()
{
   if (getOwnship() != nullptr) {
      oe::models::Radar* rdr = nullptr;
      {
         oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Tws));
         if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
      }
      oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != nullptr) {
         // But could be GMTI ...
         if (sms->isWeaponDeliveryMode(oe::models::StoresMgr::A2G)) {
            oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Gmti));
            if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
         }
      }
      if (rdr != nullptr) {
         rdr->decRange();
      }
      else {
         range = range / 2.0;
      }
   }
   return true;
}

// Step ownship key
bool TestDisplay::onStepOwnshipKey()
{
   const auto ts = dynamic_cast<SimStation*>(getStation());
   if ( ts != nullptr ) {
      ts->stepOwnshipPlayer();
   }
   return true;
}

bool TestDisplay::shutdownNotification()
{
   oe::base::Component* parent = container();
   if (parent != nullptr) parent->event(SHUTDOWN_EVENT);

   return BaseClass::shutdownNotification();
}

// update non-time critical stuff here
void TestDisplay::updateData(const double dt)
{
   // Update the PFD
   updatePfd(dt);

   // Find and update the test RADAR display
   {
      rdrDisplay = nullptr;
      oe::base::Pair* p = findByType(typeid(oe::xpanel::DspRadar));
      if (p != nullptr) rdrDisplay = dynamic_cast<oe::xpanel::DspRadar*>( p->object() );
   }
   if (rdrDisplay != nullptr && getOwnship() != nullptr) {
      // Default is TWS
      oe::models::Radar* rdr = nullptr;
      {
         oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Tws));
         if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
      }
      oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != nullptr) {
         // But could be GMTI ...
         if (sms->isWeaponDeliveryMode(oe::models::StoresMgr::A2G)) {
            oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Gmti));
            if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
         }
      }
      rdrDisplay->setRadar(rdr);
   }

   // Find and update the test RWR display
   {
      rwrDisplay = nullptr;
      oe::base::Pair* p = findByType(typeid(oe::xpanel::DspRwr));
      if (p != nullptr) rwrDisplay = dynamic_cast<oe::xpanel::DspRwr*>( p->object() );
   }
   if (rwrDisplay != nullptr && getOwnship() != nullptr) {
      oe::models::Rwr* rwr = nullptr;
      oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Rwr));
      if (pair != nullptr) rwr = static_cast<oe::models::Rwr*>(pair->object());
      rwrDisplay->setRwr(rwr);
   }

   // Send flight data to readouts
   if (getOwnship() != nullptr) {
      {
         oe::models::Radar* rdr = nullptr;
         {
            oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Tws));
            if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
         }
         oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
         if (sms != nullptr) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(oe::models::StoresMgr::A2G)) {
               oe::base::Pair* pair = getOwnship()->getSensorByType(typeid(oe::models::Gmti));
               if (pair != nullptr) rdr = static_cast<oe::models::Radar*>(pair->object());
            }
         }
         if (rdr != nullptr) range = rdr->getRange();
      }

      send("hsi1", UPDATE_VALUE5, getOwnship()->getHeadingR(), headingSD);
      send("rangeRO", UPDATE_VALUE, range, rangeSD);

      // Maintain Air Tracks
      oe::base::Pair* pair = findByName("airTracks1");
      if (pair != nullptr) {
         const auto myLoader = dynamic_cast<oe::graphics::SymbolLoader*>(pair->object());
         if (myLoader != nullptr) {
            myLoader->setRange(range);
            myLoader->setHeadingDeg(getOwnship()->getHeadingD());

            maintainAirTrackSymbols(myLoader, range);
         }
      }
   }

   // Update base classes stuff
   BaseClass::updateData(dt);
}

void TestDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
   setMouse(x,y);

   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      oe::base::Pair* pair = findByName("airTracks1");
      if (pair != nullptr) {
         const auto myLoader = dynamic_cast<oe::graphics::SymbolLoader*>(pair->object());
         if (myLoader != nullptr) {
            oe::graphics::Graphic* selected = pick(0);
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
void TestDisplay::maintainAirTrackSymbols(oe::graphics::SymbolLoader* loader, const double rng)
{
    int codes[MAX_TRACKS];              // Work codes: empty(0), matched(1), unmatched(-1)
    double rng2 = (rng * rng);          // Range squared (KM * KM)

    oe::models::Player* newTracks[MAX_TRACKS];  // New tracks to add
    int nNewTracks = 0;                         // Number of new tracks

    // The real maximum number of tracks is the smaller of MAX_TRACKS and the loader's maximum
    int maxTracks = loader->getMaxSymbols();
    if (MAX_TRACKS < maxTracks) maxTracks = MAX_TRACKS;

    // Set the initial codes
    for (int i = 0; i < maxTracks; i++) {
        if (tracks[i] != nullptr) codes[i] = -1;  // needs to be matched
        else codes[i] = 0;                        // empty slot
    }

    // find all air vehicles within range
    {
        // get the player list
        oe::simulation::Simulation* sim = getSimulation();
        oe::base::PairStream* plist = sim->getPlayers();

        // search for air vehicles or missiles within range
        oe::base::List::Item* item = plist->getFirstItem();
        while (item != nullptr && nNewTracks < maxTracks) {

            const auto pair = static_cast<oe::base::Pair*>(item->getValue());
            const auto p = static_cast<oe::models::Player*>(pair->object());
            oe::base::Vec3d rpos = p->getPosition() - getOwnship()->getPosition();
            double x = rpos[0] * oe::base::distance::M2NM;
            double y = rpos[1] * oe::base::distance::M2NM;

            if (
               p != getOwnship() &&
               p->isActive() &&
               ((x*x + y*y) < rng2) &&
               (p->isClassType(typeid(oe::models::AirVehicle)) || p->isClassType(typeid(oe::models::Missile))) ) {
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
            tracks[i]->unref();   // unref the player
            tracks[i] = nullptr;  // clear the player pointer
            trkIdx[i] = 0;        // clear the index
            codes[i]  = 0;        // slot is now empty
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
                if (newTracks[inew]->isClassType(typeid(oe::models::AirVehicle))) {
                  if (newTracks[inew]->getSensorByType(typeid(oe::models::Jammer)) == nullptr) {
                     // non-jammers
                     if (newTracks[inew]->isSide(oe::models::Player::BLUE)) type = 1;      // friend
                     else if (newTracks[inew]->isSide(oe::models::Player::RED)) type = 2; // foe
                     else type = 3; // neutral/commercial
                  }
                }
                else if (newTracks[inew]->isClassType(typeid(oe::models::Missile))) {
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
        const double osX = getOwnship()->getXPosition();
        const double osY = getOwnship()->getYPosition();
        if (tracks[i] != nullptr && trkIdx[i] != 0) {
            double xp = tracks[i]->getXPosition() - osX;
            double yp = tracks[i]->getYPosition() - osY;
            loader->updateSymbolPositionXY( trkIdx[i], (xp * oe::base::distance::M2NM), (yp * oe::base::distance::M2NM) );
            loader->updateSymbolHeading( trkIdx[i], tracks[i]->getHeadingD() );
        }
    }
}

//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
oe::models::Player* TestDisplay::getOwnship()
{
   oe::models::Player* p = nullptr;
   oe::simulation::Station* sta = getStation();
   if (sta != nullptr) {
      p = dynamic_cast<oe::models::Player*>(sta->getOwnship());  // DDH
   }
   return p;
}

oe::simulation::Simulation* TestDisplay::getSimulation()
{
   oe::simulation::Simulation* s = nullptr;
   oe::simulation::Station* sta = getStation();
   if (sta != nullptr) s = sta->getSimulation();
   return s;
}

oe::simulation::Station* TestDisplay::getStation()
{
   if (myStation == nullptr) {
      const auto s = dynamic_cast<oe::simulation::Station*>( findContainerByType(typeid(oe::simulation::Station)) );
      if (s != nullptr) myStation = s;
   }
   return myStation;
}

//------------------------------------------------------------------------------
// updatePfd() --
//------------------------------------------------------------------------------
void TestDisplay::updatePfd(const double)
{
    const auto av = static_cast<oe::models::AirVehicle*>(getOwnship());

    // pitch
    pitch = av->getPitchD();

    // roll
    roll = av->getRollD();

    // heading
    trueHdg = av->getHeadingD();
    if (trueHdg > 360) trueHdg = 0;

    // selected heading
    cmdHdg = 0;
    if (cmdHdg > 360) {
        cmdHdg = 0;
    }

    // here is sideslip
    slip = av->getSideSlipD();

    // airspeed
    airSpd = av->getCalibratedAirspeed();

    // test data
    double mach = av->getMach();

    // commanded speed
    cmdSpd = 150;

    // altitude
    alt = av->getAltitudeFt();

    // commanded alt
    cmdAlt = 1500;

    // glideslope
    gSlope = 0;

    // lat dev
    latDev = 0;

    // vvi tape gauge test
    const oe::base::Vec3d vel = av->getVelocity();
    const double vvMps = -vel[2];
    vvi = vvMps * 60.0f * oe::base::distance::M2FT;

    // flight director stuff
    // flight diretor bank angle
    fDirBank = 0;

    // flight director pitch angle
    fDirPitch = 0;

    // barometric pressure (selected)
    baro = 29.92;

    oe::base::Pair* pair = findByType(typeid(oe::xpanel::Pfd));
    if (pair != nullptr) {
        const auto p = static_cast<oe::xpanel::Pfd*>(pair->object());
        if (p != nullptr) {
            p->setPitchDeg(pitch);
            p->setRollDeg(roll);
            p->setTrueHeading(trueHdg);
            p->setCmdHdg(cmdHdg);
            p->setAirSpeedKts(airSpd);
            p->setAltitudeFt(alt);
            p->setMach(mach);
            p->setSideSlip(slip);
            p->setGlideslope(gSlope);
            p->setLatDev(latDev);
            p->setCmdAirSpdKts(cmdSpd);
            p->setCmdAltFt(cmdAlt);
            p->setVVI(vvi);
            p->setFltDirBankDeg(fDirBank);
            p->setFltDirPitchDeg(fDirPitch);
            p->setBaroPress(baro);
        }
    }
}
