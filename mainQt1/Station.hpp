
#ifndef __Station_H__
#define __Station_H__

#include "openeaagles/simulation/Station.hpp"

class StnTimerObject;

//------------------------------------------------------------
// Class: StnTimerObject
// Description: create our window and startup any timers needed
//------------------------------------------------------------
class Station : public oe::simulation::Station
{
   DECLARE_SUBCLASS(Station, oe::simulation::Station)
public:
   Station();

   // create our top level windows
   virtual int createWindow(int argc, char *argv[]);

private:
   StnTimerObject* timerObj;
};

#endif
