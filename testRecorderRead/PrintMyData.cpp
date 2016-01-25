//------------------------------------------------------------------------------
// Class: PrintMyData
//------------------------------------------------------------------------------
#include "PrintMyData.h"

#include "xRecorder/protobuf/DataRecord.pb.h"
#include "xRecorder/dataRecorderTokens.h"
#include "openeaagles/recorder/DataRecordHandle.h"

namespace oe {
namespace test {

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
void PrintMyData::processRecordImp(const oe::recorder::DataRecordHandle* const handle)
{
   if (handle == nullptr) return;  // cannot continue
   const oe::recorder::Pb::DataRecord* dataRecord = handle->getRecord();
   if (dataRecord == nullptr) return;  // cannot continue

   // Get the time msg
   const oe::recorder::Pb::Time* timeMsg = nullptr;
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
            if (timeMsg != nullptr) {
               if (timeMsg->has_exec_time()) {
                  sout << timeMsg->exec_time() << ";  ";
               }
            }

            const oe::recorder::Pb::MarkerMsg* msg = &dataRecord->marker_msg();

            if (msg->has_id()) sout << "id= " << msg->id() << ";  ";
            if (msg->has_source_id()) sout << "source_id= " << msg->source_id() << ";  ";

            if (msg->HasExtension( oe::xRecorder::Pb::foo )) sout << "foo= " << msg->GetExtension( oe::xRecorder::Pb::foo ) << ";  ";

            printToOutput( sout.str().c_str() );
         }
         break; 
      }

      // MyData message event
      case REID_MY_DATA_EVENT : {
         if (dataRecord->HasExtension( oe::xRecorder::Pb::my_data_msg )) {
            std::stringstream sout;

            sout << "MY_DATA " << "   ";
            if (timeMsg != nullptr) {
               if (timeMsg->has_exec_time()) {
                  sout << timeMsg->exec_time() << ";  ";
               }
            }

            const oe::xRecorder::Pb::MyDataMsg* msg = &dataRecord->GetExtension( oe::xRecorder::Pb::my_data_msg );

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
