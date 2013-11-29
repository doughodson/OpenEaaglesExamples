//------------------------------------------------------------------------------
// Form function
//------------------------------------------------------------------------------
#include "./formFunc.h"

#include "./DataRecordTest.h"
#include "./PrintMyData.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/recorder/recorderFF.h"
#include "openeaagles/simulation/simulationFF.h"

namespace TestRecorder {

Eaagles::Basic::Object* mainFormFunc(const char* formname)
{
   Eaagles::Basic::Object* newform = 0;

   if ( strcmp(formname, DataRecordTest::getFormName()) == 0 ) {
      newform = new DataRecordTest();
   }
   else if ( strcmp(formname, PrintMyData::getFormName()) == 0 ) {
      newform = new PrintMyData();
   }

   else {
      if (newform == 0) newform = Eaagles::Simulation::simulationFormFunc(formname);
      if (newform == 0) newform = Eaagles::Basic::basicFormFunc(formname);
      if (newform == 0) newform = Eaagles::Recorder::recorderFormFunc(formname);
   }

   return newform;
}

} // End TestRecorder namespace
