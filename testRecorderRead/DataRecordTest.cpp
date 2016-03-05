//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#include "DataRecordTest.h"

#include "openeaagles/recorder/InputHandler.h"
#include "openeaagles/recorder/OutputHandler.h"
#include "openeaagles/recorder/DataRecordHandle.h"

#include "xrecorder/protobuf/DataRecord.pb.h"

namespace oe {
namespace test {

//==============================================================================
// DataRecordTest
//==============================================================================

IMPLEMENT_SUBCLASS(DataRecordTest,"DataRecordTest")
EMPTY_SERIALIZER(DataRecordTest)

BEGIN_SLOTTABLE(DataRecordTest)
   "inputHandler",
   "outputHandler",
END_SLOTTABLE(DataRecordTest)

// Map slot table to handles 
BEGIN_SLOT_MAP(DataRecordTest)
   ON_SLOT(1, setSlotInputHandler,   oe::recorder::InputHandler)
   ON_SLOT(2, setSlotOutputHandler,   oe::recorder::OutputHandler)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
DataRecordTest::DataRecordTest()
{
   STANDARD_CONSTRUCTOR()

   initData();
}

void DataRecordTest::initData()
{
   inputHandler = nullptr;
   outputHandler = nullptr;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void DataRecordTest::copyData(const DataRecordTest& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();

   {  // Clone input handler
      oe::recorder::InputHandler* clone = nullptr;
      if (org.inputHandler != nullptr) clone = org.inputHandler->clone();
      setSlotInputHandler(clone);
      if (clone != nullptr) clone->unref();
   }

   {  // Clone output handler
      oe::recorder::OutputHandler* clone = nullptr;
      if (org.outputHandler != nullptr) clone = org.outputHandler->clone();
      setSlotOutputHandler(clone);
      if (clone != nullptr) clone->unref();
   }
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void DataRecordTest::deleteData()
{
   setSlotInputHandler(nullptr);
   setSlotOutputHandler(nullptr);
}

//------------------------------------------------------------------------------
// Main test
//------------------------------------------------------------------------------
void DataRecordTest::runTest()
{
   if (inputHandler == nullptr) {
      std::cerr << "runTest() -- missing input handler!" << std::endl;
      return;
   }

   if (outputHandler == nullptr) {
      std::cerr << "runTest() -- missing output handler!" << std::endl;
      return;
   }

   bool finished = false;
   while (!finished) {
      const oe::recorder::DataRecordHandle* p = inputHandler->readRecord();
      if (p != nullptr) {
         outputHandler->processRecord(p);
      }
      finished = (p == nullptr) || (p->getRecord()->id() == REID_END_OF_DATA);
   }
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotInputHandler(oe::recorder::InputHandler* const msg)
{
   inputHandler = msg;
   if (inputHandler != nullptr) inputHandler->container(this);
   return true;
}

bool DataRecordTest::setSlotOutputHandler(oe::recorder::OutputHandler* const msg)
{
   outputHandler = msg;
   if (outputHandler != nullptr) outputHandler->container(this);
   return true;
}


//------------------------------------------------------------------------------
// getSlotByIndex() 
//------------------------------------------------------------------------------
base::Object* DataRecordTest::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}
}
