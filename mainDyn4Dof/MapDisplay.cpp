#include "./MapDisplay.h"

#include "./TestStation.h"
#include "./MapPage.h"

#include "openeaagles/vehicles/Dyn4DofModel.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Player.h"

#include "openeaagles/basic/osg/Vec3"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/units/Times.h"

#include <GL/glut.h>
#include <iomanip>

namespace Eaagles {
namespace MainDyn4Dof {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MapDisplay,"MapTestDisplay")
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

   cmdAirspeed  = 200.0;
   cmdAltitude  = 8000.0;
   cmdHeading   = 0;

   cmdRangeSD.empty();
   cmdAirspeedSD.empty();
   cmdAltitudeSD.empty();
   cmdHeadingSD.empty();

   passiveEnable = false;
}  

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void MapDisplay::copyData(const MapDisplay& org, const bool cc)
{
   // copy base class stuff first
   BaseClass::copyData(org);

   startX = org.startX;
   startY = org.startY;
   dragging = org.dragging;

   cmdAirspeed  = org.cmdAirspeed;
   cmdAltitude  = org.cmdAltitude;
   cmdHeading   = org.cmdHeading;

   cmdRangeSD.empty();
   cmdAirspeedSD.empty();
   cmdAltitudeSD.empty();
   cmdHeadingSD.empty();

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

   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      int winX = glutGet(GLUT_WINDOW_X);
      int winY = glutGet(GLUT_WINDOW_Y);
      int winW = glutGet(GLUT_WINDOW_WIDTH);
      int winH = glutGet(GLUT_WINDOW_HEIGHT);

      std::cout << "===========================================" << std::endl;
      std::cout << "winX = " << std::setw(5) << winX << "    " << "winY = " << std::setw(5) << winY << std::endl;
      std::cout << "winW = " << std::setw(5) << winW 
                << "    "
                << "winH = " << std::setw(5) << winH 
                << std::endl;

      std::cout << "x    = " << std::setw(5) << x 
                << "    "
                << "y    = " << std::setw(5) << y 
                << std::endl;

      GLdouble l = 0, r = 0, t = 0, b = 0, n = 0, f = 0;
      getOrtho(l, r, b, t, n, f);
      std::cout << "l = " << std::setw(5) << l <<  "    " 
                << "r = " << std::setw(5) << r << std::endl;
      std::cout << "b = " << std::setw(5) << b <<  "    " 
                << "t = " << std::setw(5) << t << std::endl;
      std::cout << "n = " << std::setw(5) << n <<  "    " 
                << "f = " << std::setw(5) << f << std::endl;
   }

   if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {

   }
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
   if (passiveEnable) {
      std::cout << "x = " << std::setw(5) << x 
                << "    "
                << "y = " << std::setw(5) << y 
                << std::endl;
   }
}

// ----------------------------------------------------------------------------
// mouseMotionEvent() override this to move our map.
// ----------------------------------------------------------------------------
void MapDisplay::mouseMotionEvent(const int x, const int y)
{
    if (dragging) {
        MapPage* page = (MapPage*)(subpage());
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
   //// cmdRange up, down
   //MapPage* page = (MapPage*)(subpage());

   //// cmdAirspeed, cmdAltitude, cmdHeading up, down
   //Simulation::Aircraft* pA = getOwnship();
   //Vehicle::Dyn4DofModel* pR = 0;
   //if (pA != 0) {
   //   pR = (Vehicle::Dyn4DofModel*)pA->getDynamicsModel();   
   //}
   ////MainDyn4Dof::Dyn4DofModel* pR = getRacModel();
   ////Dyn4DofModel* pR = (Dyn4DofModel*) getOwnship();


   //if (page != 0 && pA != 0 && pR != 0) {

   //   switch (b) { 
   //      //-------------------------------------------------
   //      // decrease range
   //      //-------------------------------------------------
   //      case 101:   if (page->getRange() > 5) {
   //                     page->setRange(page->getRange() - 5);
   //                     
   //                  }
   //                  break;

   //      //-------------------------------------------------
   //      // increase range
   //      //-------------------------------------------------
   //      case 102:   if (page->getRange() < 320) {
   //                     page->setRange(page->getRange() + 5);
   //                  }
   //                  break;

   //      //-------------------------------------------------
   //      // decrease cmdAirspeed
   //      //-------------------------------------------------
   //      case 103:   if (cmdAirspeed > 100) {
   //                     cmdAirspeed -= 10;
   //                     pR->setCmdVel(cmdAirspeed);
   //                  }
   //                  break;

   //      //-------------------------------------------------
   //      // increase cmdAirspeed
   //      //-------------------------------------------------
   //      case 104:   if (cmdAirspeed < 400) {
   //                     cmdAirspeed += 10;
   //                     pR->setCmdVel(cmdAirspeed);
   //                  }
   //                  break;

   //      //-------------------------------------------------
   //      // decrease cmdAltitude
   //      //-------------------------------------------------
   //      case 105:   if (cmdAltitude > 1000) {
   //                     cmdAltitude -= 500;
   //                     pR->setCmdAlt(cmdAltitude);
   //                  }
   //                  break;

   //      //-------------------------------------------------
   //      // increase cmdAltitude
   //      //-------------------------------------------------
   //      case 106:   if (cmdAltitude < 40000) {
   //                     cmdAltitude += 500;
   //                     pR->setCmdAlt(cmdAltitude);
   //                  }
   //                  break;

   //      //-------------------------------------------------
   //      // decrease cmdHeading
   //      //-------------------------------------------------
   //      case 107:   cmdHeading -= 10;
   //                  if (cmdHeading < -180.0) cmdHeading += 360;
   //                     pR->setCmdHdg(cmdHeading);
   //                  break;

   //      //-------------------------------------------------
   //      // increase cmdHeading
   //      //-------------------------------------------------
   //      case 108:   cmdHeading += 10;
   //                  if (cmdHeading > 180.0) cmdHeading -= 360;
   //                     pR->setCmdHdg(cmdHeading);
   //                  break;

   //      //-------------------------------------------------
   //      case 111:   passiveEnable = true; 
   //                  break;

   //      case 112:   passiveEnable = false; 
   //                  break;

   //      default:    break;
   //   }
   //}
}

// ----------------------------------------------------------------------------
// updateData() - update background data
// ----------------------------------------------------------------------------
void MapDisplay::updateData(const LCreal dt)
{
   BaseClass::updateData(dt);

   // get pointer to MapPage data
   int cmdRange = 0;
   MapPage* page = (MapPage*)(subpage());
   if (page != 0) {
      cmdRange = (int) page->getRange();
   }

   //// get pointer to Aircraft data
   //Dyn4DofModel* pR = 0;
   //Simulation::Aircraft* pA = (Simulation::Aircraft*)getOwnship();
   //if (pA != 0) {
   //   pR = (Dyn4DofModel*) pA->getDynamicsModel();
   //}

   // get pointer to Dyn4DofModel data
   send("cmdRange",     UPDATE_VALUE, cmdRange,     cmdRangeSD);
   send("cmdAirspeed",  UPDATE_VALUE, cmdAirspeed,  cmdAirspeedSD);
   send("cmdAltitude",  UPDATE_VALUE, cmdAltitude,  cmdAltitudeSD);
   send("cmdHeading",   UPDATE_VALUE, cmdHeading,   cmdHeadingSD);
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

