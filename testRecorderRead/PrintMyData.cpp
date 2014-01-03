//------------------------------------------------------------------------------
// Class: PrintMyData
//------------------------------------------------------------------------------
#include "PrintMyData.h"

#include "xRecorder/DataRecord.pb.h"
#include "xRecorder/dataRecorderTokens.h"
#include "openeaagles/recorder/DataRecordHandle.h"

namespace Eaagles {
namespace Test {

//==============================================================================
// Class PrintMyData
//==============================================================================
IMPLEMENT_SUBCLASS(PrintMyData,"PrintMyData")
EMPTY_SLOTTABLE(PrintMyData)
EMPTY_SERIALIZER(PrintMyData)
EMPTY_CONSTRUCTOR(PrintMyData)
EMPTY_COPYDATA(PrintMyData)
EMPTY_DELETEDATA(PrintMyData)


//------------------------------------------------------------------------------
// Print the data
//------------------------------------------------------------------------------
void PrintMyData::processRecordImp(const Eaagles::Recorder::DataRecordHandle* const handle)
{
   if (handle == 0) return;  // cannot continue
   const Eaagles::Recorder::Pb::DataRecord* dataRecord = handle->getRecord();
   if (dataRecord == 0) return;  // cannot continue

   // Get the time msg
   const Eaagles::Recorder::Pb::Time* timeMsg = 0;
   if (dataRecord->has_time()) {
      timeMsg = &dataRecord->time();
   }

   // Get message id
   unsigned int messageId = dataRecord->id();
   switch (messageId) {

      // Extended Marker event
      case REID_MARKER : {
         if (dataRecord->has_marker_msg()) {
            std::stringstream sout;

            sout << "MARKER " << "    ";
            if (timeMsg != 0) {
               if (timeMsg->has_exec_time()) {
                  sout << timeMsg->exec_time() << ";  ";
               }
            }

            const Eaagles::Recorder::Pb::MarkerMsg* msg = &dataRecord->marker_msg();

            if (msg->has_id()) sout << "id= " << msg->id() << ";  ";
            if (msg->has_source_id()) sout << "source_id= " << msg->source_id() << ";  ";

            if (msg->HasExtension( Eaagles::xRecorder::Pb::foo )) sout << "foo= " << msg->GetExtension( Eaagles::xRecorder::Pb::foo ) << ";  ";

            printToOutput( sout.str().c_str() );
         }
         break; 
      }

      // MyData message event
      case REID_MY_DATA_EVENT : {
         if (dataRecord->HasExtension( Eaagles::xRecorder::Pb::my_data_msg )) {
            std::stringstream sout;

            sout << "MY_DATA " << "   ";
            if (timeMsg != 0) {
               if (timeMsg->has_exec_time()) {
                  sout << timeMsg->exec_time() << ";  ";
               }
            }

            const Eaagles::xRecorder::Pb::MyDataMsg* msg = &dataRecord->GetExtension( Eaagles::xRecorder::Pb::my_data_msg );

            if (msg->has_fee()) sout << "fee= " << msg->fee() << ";  ";
            if (msg->has_fi()) sout << "fi= " << msg->fi() << ";  ";
            if (msg->has_fo()) sout << "fo= " << msg->fo() << ";  ";

            printToOutput( sout.str().c_str() );
         }
         break; 
      }

   }

}

}
}
