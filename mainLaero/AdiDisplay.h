//------------------------------------------------------------------------------
// Class: AdiDisplay
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_AdiDisplay_H__
#define __Eaagles_Example_AdiDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Simulation { 
      class Station; 
      class Aircraft; 
   }

namespace Example {

class AdiDisplay : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(AdiDisplay, Glut::GlutDisplay)

public:
   AdiDisplay();

   Simulation::Aircraft* getOwnship();
   Simulation::Station* getStation();

   virtual void updateData(const LCreal dt = 0.0f);

private:
   SPtr<Simulation::Station> myStation;

   //-----------------------------
   double psiRO;     // [deg]
   double thtRO;     // [deg]
   double phiRO;     // [deg]
   double velRO;     // [kts]
   double altRO;     // [ft]

   double pRO;       // [deg/sec]
   double qRO;       // [deg/sec]
   double rRO;       // [deg/sec]

   double bankADI;   // [deg]
   double pitchADI;  // [deg]

   //-----------------------------
   SendData psiRO_SD;
   SendData thtRO_SD;
   SendData phiRO_SD;
   SendData velRO_SD;
   SendData altRO_SD;
    
   SendData pRO_SD;
   SendData qRO_SD;
   SendData rRO_SD;
    
   SendData bankADI_SD;
   SendData pitchADI_SD;
};

}
}

#endif
