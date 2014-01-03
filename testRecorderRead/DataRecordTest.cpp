//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#include "DataRecordTest.h"

#include "openeaagles/recorder/InputHandler.h"
#include "openeaagles/recorder/OutputHandler.h"
#include "openeaagles/recorder/DataRecordHandle.h"

#include "xRecorder/DataRecord.pb.h"

namespace Eaagles {
namespace Test {

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
   ON_SLOT(1, setSlotInputHandler,   Eaagles::Recorder::InputHandler)
   ON_SLOT(2, setSlotOutputHandler,   Eaagles::Recorder::OutputHandler)
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
   inputHandler = 0;
   outputHandler = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void DataRecordTest::copyData(const DataRecordTest& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();

   {  // Clone input handler
      Eaagles::Recorder::InputHandler* clone = 0;
      if (org.inputHandler != 0) clone = org.inputHandler->clone();
      setSlotInputHandler(clone);
      if (clone != 0) clone->unref();
   }

   {  // Clone output handler
      Eaagles::Recorder::OutputHandler* clone = 0;
      if (org.outputHandler != 0) clone = org.outputHandler->clone();
      setSlotOutputHandler(clone);
      if (clone != 0) clone->unref();
   }
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void DataRecordTest::deleteData()
{
   setSlotInputHandler(0);
   setSlotOutputHandler(0);
}

//------------------------------------------------------------------------------
// Main test
//------------------------------------------------------------------------------
void DataRecordTest::runTest()
{
   if (inputHandler == 0) {
      std::cerr << "runTest() -- missing input handler!" << std::endl;
      return;
   }

   if (outputHandler == 0) {
      std::cerr << "runTest() -- missing output handler!" << std::endl;
      return;
   }

   bool finished = false;
   while (!finished) {
      const Eaagles::Recorder::DataRecordHandle* p = inputHandler->readRecord();
      if (p != 0) {
         outputHandler->processRecord(p);
      }
      finished = (p == 0) || (p->getRecord()->id() == REID_END_OF_DATA);
   }
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotInputHandler(Eaagles::Recorder::InputHandler* const msg)
{
   inputHandler = msg;
   if (inputHandler != 0) inputHandler->container(this);
   return true;
}

bool DataRecordTest::setSlotOutputHandler(Eaagles::Recorder::OutputHandler* const msg)
{
   outputHandler = msg;
   if (outputHandler != 0) outputHandler->container(this);
   return true;
}


//------------------------------------------------------------------------------
// getSlotByIndex() 
//------------------------------------------------------------------------------
Basic::Object* DataRecordTest::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}
}
