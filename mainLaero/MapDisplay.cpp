// -------------------------------------------------------------------------------
// Class: MapDisplay
// -------------------------------------------------------------------------------

#include "MapDisplay.h"
#include "TestStation.h"
#include "MapPage.h"

#include "openeaagles/dynamics/LaeroModel.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Autopilot.h"
#include "openeaagles/simulation/Player.h"

#include "openeaagles/basic/osg/Vec3"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/units/Times.h"

#include <GL/glut.h>
#include <iomanip>

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MapDisplay, "MapTestDisplay")
EMPTY_SERIALIZER(MapDisplay)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MapDisplay::MapDisplay()
{
   STANDARD_CONSTRUCTOR()
   startX = 0;
   startY = 0;
   dragging = false;

   cmdRangeSD.empty();
   cmdAirspeedSD.empty();
   cmdAltitudeSD.empty();
   cmdHeadingSD.empty();
   apReqButtonVisSD.empty();
   apModeSD.empty();
   maxAccelSD.empty();
   maxClimbSD.empty();
   maxBankSD.empty();
   maxTurnSD.empty();

   passiveEnable = false;
}  

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void MapDisplay::copyData(const MapDisplay& org, const bool)
{
   // copy base class stuff first
   BaseClass::copyData(org);

   startX = org.startX;
   startY = org.startY;
   dragging = org.dragging;

   cmdRangeSD.empty();
   cmdAirspeedSD.empty();
   cmdAltitudeSD.empty();
   cmdHeadingSD.empty();
   apReqButtonVisSD.empty();
   apModeSD.empty();
   maxAccelSD.empty();
   maxClimbSD.empty();
   maxBankSD.empty();
   maxTurnSD.empty();

   passiveEnable = org.passiveEnable;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void MapDisplay::deleteData()
{
}

// ----------------------------------------------------------------------------
// mouseEvent() override this to set our start position.
// ----------------------------------------------------------------------------
void MapDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
   BaseClass::mouseEvent(button, state, x, y);

   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      dragging = false;
      //std::cout << "LEFT_BUTTON = UP" << std::endl;
   }

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !dragging) {
      dragging = true;
      //std::cout << "LEFT_BUTTON = DRAGGING" << std::endl;
   }

   //if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
   //   int winX = glutGet(GLUT_WINDOW_X);
   //   int winY = glutGet(GLUT_WINDOW_Y);
   //   int winW = glutGet(GLUT_WINDOW_WIDTH);
   //   int winH = glutGet(GLUT_WINDOW_HEIGHT);

   //   std::cout << "===========================================" << std::endl;
   //   std::cout << "winX = " << std::setw(5) << winX << "    " << "winY = " << std::setw(5) << winY << std::endl;
   //   std::cout << "winW = " << std::setw(5) << winW 
   //             << "    "
   //             << "winH = " << std::setw(5) << winH 
   //             << std::endl;

   //   std::cout << "x    = " << std::setw(5) << x 
   //             << "    "
   //             << "y    = " << std::setw(5) << y 
   //             << std::endl;

   //   GLdouble l = 0, r = 0, t = 0, b = 0, n = 0, f = 0;
   //   getOrtho(l, r, b, t, n, f);
   //   std::cout << "l = " << std::setw(5) << l <<  "    " 
   //             << "r = " << std::setw(5) << r << std::endl;
   //   std::cout << "b = " << std::setw(5) << b <<  "    " 
   //             << "t = " << std::setw(5) << t << std::endl;
   //   std::cout << "n = " << std::setw(5) << n <<  "    " 
   //             << "f = " << std::setw(5) << f << std::endl;
   //}

   //if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {

   //}
}

// ----------------------------------------------------------------------------
// passiveMotionEvent() .
// ----------------------------------------------------------------------------
void MapDisplay::passiveMotionEvent(const int x, const int y)
{
   BaseClass::passiveMotionEvent(x,y);
   if (!dragging) {
      startX = x;
      startY = y;
   }

   //std::cout << "passiveEnable = " << passiveEnable << std::endl;
   //if (passiveEnable) {
   //   std::cout << "x = " << std::setw(5) << x 
   //             << "    "
   //             << "y = " << std::setw(5) << y 
   //             << std::endl;
   //}
}

// ----------------------------------------------------------------------------
// mouseMotionEvent() override this to move our map.
// ----------------------------------------------------------------------------
void MapDisplay::mouseMotionEvent(const int x, const int y)
{
    if (dragging) {
        MapPage* page = static_cast<MapPage*>(subpage());
        if (page != 0) {
            // get our ref lat, because we won't go passed 70 degrees lat (either way);
            double lat = page->getReferenceLatDeg();
            if ((-70 < lat) && (lat < 70)) {
                page->moveMap(startX, startY, x, y);
            }
            else {
                if (lat > 0) page->setReferenceLatDeg(65);
                else page->setReferenceLatDeg(-65);
            }

            startX = x;
            startY = y;
        }
    }

    setMouse(x, y);
}

// ----------------------------------------------------------------------------
// buttonEvent() - called when a button is pressed
// ----------------------------------------------------------------------------
void MapDisplay::buttonEvent(const int b)
{
   // cmdRange up, down
   MapPage* page = static_cast<MapPage*>(subpage());

   // cmdAirspeed, cmdAltitude, cmdHeading up, down
   Simulation::Player* pA = getOwnship();
   Simulation::Autopilot* ap = 0;
   if (pA != 0) {
      ap = static_cast<Simulation::Autopilot*>(pA->getPilot());
   }
   if (page != 0 && ap != 0) {
      if (b == DEC_RANGE) {
         if (page->getRange() > 5) {
            page->setRange(page->getRange() - 5);
         }
      }
      else if (b == INC_RANGE) {
         if (page->getRange() < 320) {
            page->setRange(page->getRange() + 5);
         }
      }
      else if (b == DEC_CMD_AS) {
         double cmdAirspeed = ap->getCommandedVelocityKts();
         if (cmdAirspeed > 100) {
            cmdAirspeed -= 10;
            ap->setCommandedVelocityKts(cmdAirspeed);
         }      
      }
      else if (b == INC_CMD_AS) {
         double cmdAirspeed = ap->getCommandedVelocityKts();
         if (cmdAirspeed < 400) {
            cmdAirspeed += 10;
            ap->setCommandedVelocityKts(cmdAirspeed);
         }
      }
      else if (b == DEC_CMD_ALT) {
         double cmdAltitude = ap->getCommandedAltitudeFt();
         if (cmdAltitude > 1000) {
            cmdAltitude -= 500;
            ap->setCommandedAltitudeFt(cmdAltitude);
         }      
      }
      else if (b == INC_CMD_ALT) {
         double cmdAltitude = ap->getCommandedAltitudeFt();
         if (cmdAltitude < 40000) {
            cmdAltitude += 500;
            ap->setCommandedAltitudeFt(cmdAltitude);
         }
      }
      else if (b == DEC_CMD_HDG) {
         double cmdHeading = ap->getCommandedHeadingD();
         cmdHeading -= 10;
         if (cmdHeading < -180.0) cmdHeading += 360;
         ap->setCommandedHeadingD(cmdHeading);
      }
      else if (b == INC_CMD_HDG) {
         double cmdHeading = ap->getCommandedHeadingD();
         cmdHeading += 10;
         if (cmdHeading > 180.0) cmdHeading -= 360;
         ap->setCommandedHeadingD(cmdHeading);
      }
      else if (b == INC_CMD_AS_NPS) {
         double maxAccel = ap->getMaxVelAcc();
         if (maxAccel < 20) maxAccel++;
         ap->setMaxVelAccNps(maxAccel);
      }
      else if (b == DEC_CMD_AS_NPS) {
         double maxAccel = ap->getMaxVelAcc();
         if (maxAccel > 1) maxAccel--;
         ap->setMaxVelAccNps(maxAccel);
      }
      // Climb rate in meters per second
      else if (b == INC_CMD_ALT_MPS) {
         double maxClimb = ap->getMaxClimbRate();
         if (maxClimb < 100) maxClimb += 5;
         ap->setMaxClimbRateMps(maxClimb);
      }
      else if (b == DEC_CMD_ALT_MPS) {
         double maxClimb = ap->getMaxClimbRate();
         if (maxClimb > 5) maxClimb -= 5;
         ap->setMaxClimbRateMps(maxClimb);
      }
      // Turn rate in degrees per second
      else if (b == INC_CMD_HDG_ROT) {
         double maxTR = ap->getMaxTurnRate();
         if (maxTR < 25) maxTR++;
         ap->setMaxTurnRateDps(maxTR);
      }
      else if (b == DEC_CMD_HDG_ROT) {
         double maxTR = ap->getMaxTurnRate();
         if (maxTR > 0) maxTR--;
         ap->setMaxTurnRateDps(maxTR);
      }
      // Max bank (degrees)
      else if (b == INC_CMD_HDG_BNK) {
         double maxBank = ap->getMaxBankAngle();
         if (maxBank < 90) maxBank++;
         ap->setMaxBankAngleDeg(maxBank);
      }
      else if (b == DEC_CMD_HDG_BNK) {
         double maxBank = ap->getMaxBankAngle();
         if (maxBank > 0) maxBank--;
         ap->setMaxBankAngleDeg(maxBank);
      }
      else if (b == PASSIVE_ENABLE) {
         passiveEnable = true; 
      }
      else if (b == PASSIVE_DISABLE) {
         passiveEnable = false;
      }
      // get our autopilot mode and change it
      else if (b == CHANGE_AP_MODE) {
         // if off, go to nav
         bool navMode = ap->isNavModeOn();
         bool loiterMode = ap->isLoiterModeOn();
         bool flMode = ap->isFollowTheLeadModeOn();
         // if in nav mode, go to loiter mode
         if (navMode) {
            ap->setNavMode(false);
            ap->setLoiterMode(true);
         }
         // if in loiter mode, go to follow the lead mode
         else if (loiterMode) {
            ap->setLoiterMode(false);
            ap->setFollowTheLeadMode(true);
         }
         // if in follow the lead mode, turn off all modes
         else if (flMode) {
            ap->setFollowTheLeadMode(false);
         }
         // all modes off, go back to nav
         else ap->setNavMode(true);
      }
   }
}

// ----------------------------------------------------------------------------
// updateData() - update background data
// ----------------------------------------------------------------------------
void MapDisplay::updateData(const LCreal dt)
{
   BaseClass::updateData(dt);

   // get pointer to MapPage data
   int cmdRange = 0;
   MapPage* page = static_cast<MapPage*>(subpage());
   if (page != 0) {
      cmdRange = static_cast<int>(page->getRange());
   }

   double cmdAirspeed = 0, cmdAltitude = 0, cmdHeading = 0;
   bool apButtonsVis = false;
   // pilot max
   double maxAccel = 0, maxTurn = 0, maxBank = 0, maxClimb = 0;
   // default to autopilot mode off
   int apMode = 1;
   Simulation::Aircraft* pA = static_cast<Simulation::Aircraft*>(getOwnship());
   if (pA != 0) {
      Simulation::Autopilot* ap = static_cast<Simulation::Autopilot*>(pA->getPilot());
      if (ap != 0) {
         // button visibility is based on autopilot being in NO modes
         apButtonsVis = (ap->isNavModeOn() || ap->isLoiterModeOn() || ap->isFollowTheLeadModeOn());
         cmdAirspeed = ap->getCommandedVelocityKts();
         cmdAltitude = ap->getCommandedAltitudeFt();
         cmdHeading = ap->getCommandedHeadingD();
         if (ap->isNavModeOn()) apMode = 2;
         else if (ap->isLoiterModeOn()) apMode = 3;
         else if (ap->isFollowTheLeadModeOn()) apMode = 4;
         maxAccel = ap->getMaxVelAcc();
         maxTurn = ap->getMaxTurnRate();
         maxBank = ap->getMaxBankAngle();
         maxClimb = ap->getMaxClimbRate();
      }
   }

   // get pointer to LaeroModel data
   send("cmdRange",     UPDATE_VALUE, cmdRange,     cmdRangeSD);
   send("cmdAirspeed",  UPDATE_VALUE, cmdAirspeed,  cmdAirspeedSD);
   send("cmdAltitude",  UPDATE_VALUE, cmdAltitude,  cmdAltitudeSD);
   send("cmdHeading",   UPDATE_VALUE, cmdHeading,   cmdHeadingSD);
   // Autopilot mode
   send("apMode", SELECT, apMode, apModeSD);
   // button visibility
   send("apReqButtons", SET_VISIBILITY, !apButtonsVis, apReqButtonVisSD);
   // maximums
   send("cmdAccel",   UPDATE_VALUE, maxAccel,   maxAccelSD);
   send("cmdClimb",   UPDATE_VALUE, maxClimb,   maxClimbSD);
   send("cmdRot",   UPDATE_VALUE, maxTurn,   maxTurnSD);
   send("cmdBank", UPDATE_VALUE, maxBank, maxBankSD);
}

//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
Simulation::Station* MapDisplay::getStation()
{
    if (myStation == 0) {
        Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
        if (s != 0) myStation = s;
    }
    return myStation;
}

Simulation::Aircraft* MapDisplay::getOwnship()
{
   Simulation::Aircraft* p = 0;
   Simulation::Station* sta = getStation();
   if (sta != 0) {
      p = dynamic_cast<Simulation::Aircraft*>(sta->getOwnship());
   }
   return p;
}

}
}
