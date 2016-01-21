// ----------------------------------------------------------------------------
// Class: FltkStation
//
// Description: Station to start our fltk drawing 
// NOTE: If you don't want to use the OpenEaagles simulation class, you create your
// own basic derived component to do this same functionality.  I am just
// using a Station so we can test interfacing and make sure our threads all
// still run correctly and work.
// ----------------------------------------------------------------------------
#ifndef __oe_example_FoxStation_H__
#define __oe_example_FoxStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace example {

class MainWindow;
class FltkDisplay;

class FltkStation : public Simulation::Station
{
   DECLARE_SUBCLASS(FltkStation, Simulation::Station)

public:

   FltkStation();

   void reset() override;
   void updateData(const LCreal dt = 0.0) override;

protected:

   void initData();

   bool setSlotDisplay1(FltkDisplay* const x);
   bool setSlotDisplay2(FltkDisplay* const x);

private:

   bool init;                  // initialized flag
   FltkDisplay* display1;      // first display
   FltkDisplay* display2;      // second display
   MainWindow* mainWin;        // main Fltk window
};

} // end example namespace
} // end oe namespace

#endif
