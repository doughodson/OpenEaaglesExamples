//------------------------------------------------------------------------------
// Class:	Station
// Base class:	Object -> Component -> Eaagles::Station
//
//------------------------------------------------------------------------------
#ifndef __Station_H_3D4A0F8C_5731_4cc9_A0AF_DEB89377FAA6
#define __Station_H_3D4A0F8C_5731_4cc9_A0AF_DEB89377FAA6

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
namespace mainFox {

class Application;
class Display;

class Station : public Simulation::Station
{
    DECLARE_SUBCLASS(Station, Simulation::Station)

public:
    Station();

  //  Application* getApplication()               { return app; }
//    void setApplication(Application* const p)   { app = p; }

    // Displays
    Display* getMainDisplay()    { return display; }

    // Component Interface
    virtual void updateTC(const LCreal dt = 0.0f);
    virtual void updateData(const LCreal dt = 0.0f);

protected:
    // Slot functions
    bool setSlotMainDisplay(Display* const msg);

private:

//   Application* app;           // Our Fox Toolkit Application

   SPtr<Display>  display;
};

} // End mainFox namespace
} // End Eaagles namespace

#endif // __Station_H_3D4A0F8C_5731_4cc9_A0AF_DEB89377FAA6

