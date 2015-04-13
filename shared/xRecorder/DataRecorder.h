//------------------------------------------------------------------------------
// Class: DataRecorder
//------------------------------------------------------------------------------
#ifndef __Eaagles_xRecorder_DataRecorder_H__
#define __Eaagles_xRecorder_DataRecorder_H__

#include "openeaagles/recorder/DataRecorder.h"

namespace Eaagles {
namespace xRecorder {

//------------------------------------------------------------------------------
// Class: DataRecorder
// Description: Example of an extended data recorder
//
// Factory name: XDataRecorder
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
class DataRecorder : public Recorder::DataRecorder
{
   DECLARE_SUBCLASS(DataRecorder, Recorder::DataRecorder)

public:
   DataRecorder();

protected:
   bool recordDataImp(
      const unsigned int id,              // Recorder event Id
      const Basic::Object* pObjects[4],   // Sample objects
      const double values[4]              // Sample values
   ) override;

   // Recorder data event handlers
   virtual bool recordMyData(const Basic::Object* objs[4], const double values[4]);

   bool recordMarker(const Basic::Object* objs[4], const double values[4]) override;

private:
   void initData();
};

} // End xDataRecorder namespace
} // End Eaagles namespace

#endif

