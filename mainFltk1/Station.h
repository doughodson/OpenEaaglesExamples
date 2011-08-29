// ----------------------------------------------------------------------------
// Classname:   Station
// Namespace:   Eaagles::Fltk1
// Description: Station to start our fltk drawing 
// NOTE: If you don't want to use Eaagles simulation class, you create your
// own basic derived component to do this same functionality.  I am just
// using a Station so we can test interfacing and make sure our threads all
// still run correctly and work.
// ----------------------------------------------------------------------------
#ifndef _EAAGLES_FLTK1_STATION_H__
#define _EAAGLES_FLTK1_STATION_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
namespace Fltk1 {

class MainWindow;
class Display;

class Station : public Simulation::Station {
   DECLARE_SUBCLASS(Station, Simulation::Station)

public:
    Station();

    virtual void reset();
    virtual void updateData(const LCreal dt = 0.000000);

protected:
    bool setSlotDisplay(Display* const x);
    bool setSlotDisplay2(Display* const x);

private:
    bool init;                  // our we initialized
    Display* display;           // our first display
    Display* display2;           // our first display
    MainWindow* mainWin;        // our main Fltk window
};

}; // end Fltk1 namespace
}; // end Eaagles namespace

#endif  // _EAAGLES_FLTK1_STATION_H__
