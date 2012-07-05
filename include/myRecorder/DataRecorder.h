//------------------------------------------------------------------------------
// OpenEaagles Data Recorder
//------------------------------------------------------------------------------
#ifndef __Eaagles_MyRecorder_DataRecorder_H__
#define __Eaagles_MyRecorder_DataRecorder_H__

#include "openeaagles/Recorder/DataRecorder.h"

namespace Eaagles {
namespace MyRecorder {

//------------------------------------------------------------------------------
// Class: DataRecorder
// Description: Example of an extended data recorder
//
// Form name: MyDataRecorder
//
//------------------------------------------------------------------------------
// Recorder events handled ---
//
// -- new handlers --
//    REID_MY_DATA_EVENT      ! v[0] => fee;  v[1] => fi;  v[2] => fo
//
// -- Overloaded base class handler
//    REID_MARKER             ! v[0] => id;  v[1] => source id;  v[2] => foo
//
//------------------------------------------------------------------------------
class DataRecorder : public Recorder::DataRecorder {
   DECLARE_SUBCLASS(DataRecorder, Recorder::DataRecorder)

public:
   DataRecorder();

protected:
   // Simulation::DataRecorder class protected interface functions
   virtual bool recordDataImp(
      const unsigned int id,              // Recorder event Id
      const Basic::Object* pObjects[4],   // Sample objects
      const double values[4]              // Sample values
   );


   // Recorder data event handlers
   virtual bool recordMyData(const Basic::Object* objs[4], const double values[4]);

   // Overloaded Recorder::DataRecorder event handlers
   virtual bool recordMarker(const Basic::Object* objs[4], const double values[4]);

private:
   void initData();
};

} // End MyRecorder namespace
} // End Eaagles namespace

#endif
