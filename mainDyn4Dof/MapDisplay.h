// -------------------------------------------------------------------------------
// Class: MapDisplay
//
// Description:
//      Derived MapDisplay that will simply make our map page move.
// -------------------------------------------------------------------------------
#ifndef __Eaagles_MainDyn4Dof_MapDisplay_H__
#define __Eaagles_MainDyn4Dof_MapDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Simulation { 
      class Station; 
      class Aircraft; 
   }

namespace MainDyn4Dof {

class MapDisplay : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(MapDisplay, Glut::GlutDisplay)

public:
   MapDisplay();  

   Simulation::Aircraft* getOwnship();
   Simulation::Station* getStation();


   // MapDisplay interface
   virtual void mouseMotionEvent(const int x, const int y);
   virtual void mouseEvent(const int button, const int state, const int x, const int y);
   virtual void passiveMotionEvent(const int x, const int y);
   virtual void buttonEvent(const int b);
   virtual void updateData(const LCreal dt = 0.000000);

private:
   SPtr<Simulation::Station> myStation;

   int startX;         // startX of our last mouse position
   int startY;         // startY of our last mouse position
   bool dragging;      // are we dragging the map?

   double cmdAirspeed;
   double cmdAltitude;
   double cmdHeading;

   SendData cmdRangeSD;
   SendData cmdAirspeedSD;
   SendData cmdAltitudeSD;
   SendData cmdHeadingSD;

   bool passiveEnable;
};

}  
}  

#endif

