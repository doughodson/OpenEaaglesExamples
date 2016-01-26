//------------------------------------------------------------------------------
// Class: DataRecorder
//------------------------------------------------------------------------------
#include "DataRecorder.h"
#include "protobuf/DataRecord.pb.h"
#include "dataRecorderTokens.h"

namespace oe {
namespace xRecorder {

IMPLEMENT_SUBCLASS(DataRecorder,"XDataRecorder")
EMPTY_SERIALIZER(DataRecorder)
EMPTY_SLOTTABLE(DataRecorder)
EMPTY_DELETEDATA(DataRecorder)

//------------------------------------------------------------------------------
// DataRecorder dispatch table
//------------------------------------------------------------------------------
BEGIN_RECORDER_HANDLER_TABLE(DataRecorder)
   ON_RECORDER_EVENT_ID( REID_MY_DATA_EVENT,   recordMyData )
END_RECORDER_HANDLER_TABLE()

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
DataRecorder::DataRecorder()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

void DataRecorder::initData()
{
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void DataRecorder::copyData(const DataRecorder& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();
}

//------------------------------------------------------------------------------
// My Data event handler
//    value[0] => fee
//    value[1] => fi
//    value[2] => fo
//------------------------------------------------------------------------------
bool DataRecorder::recordMyData(const basic::Object* objs[4], const double values[4])
{
   //const Simulation::Player* player = dynamic_cast<const Simulation::Player*>( objs[0] );
   recorder::pb::DataRecord* msg = new recorder::pb::DataRecord();
   
   // DataRecord header
   timeStamp(msg);
   msg->set_id( REID_MY_DATA_EVENT );

   // new Marker message
   pb::MyDataMsg* myDataMsg = msg->MutableExtension( pb::my_data_msg );
   myDataMsg->set_fee( static_cast<unsigned int>(oe::nintd(values[0])) );
   myDataMsg->set_fi( static_cast<unsigned int>(oe::nintd(values[1])) );
   myDataMsg->set_fo( static_cast<unsigned int>(oe::nintd(values[2])) );

   // Send the message for processing
   sendDataRecord(msg);

   return true;
}


//------------------------------------------------------------------------------
// (Overloaded) Marker event handler
//    value[0] => marker ID
//    value[1] => marker source ID
//    value[2] => foo
//------------------------------------------------------------------------------
bool DataRecorder::recordMarker(const basic::Object* objs[4], const double values[4])
{
   //const Simulation::Player* player = dynamic_cast<const Simulation::Player*>( objs[0] );
   recorder::pb::DataRecord* msg = new recorder::pb::DataRecord();
   
   // DataRecord header
   timeStamp(msg);
   msg->set_id( REID_MARKER );

   // Marker message
   recorder::pb::MarkerMsg* markerMsg = msg->mutable_marker_msg();
   markerMsg->set_id( static_cast<unsigned int>(oe::nintd(values[0])) );
   markerMsg->set_source_id( static_cast<unsigned int>(oe::nintd(values[1])) );

   // Extended value: foo
   markerMsg->SetExtension( pb::foo, static_cast<unsigned int>(oe::nintd(values[2])) ) ;

   // Send the message for processing
   sendDataRecord(msg);

   return true;
}

} // End xDataRecorder namespace
} // End oe namespace

