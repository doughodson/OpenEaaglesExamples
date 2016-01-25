//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#ifndef __oe_test_DataRecordTest_H__
#define __oe_test_DataRecordTest_H__

#include "openeaagles/basic/Component.h"
#include "openeaagles/recorder/TabPrinter.h"
#include "openeaagles/recorder/PrintPlayer.h"
#include "openeaagles/recorder/PrintSelected.h"
#include "openeaagles/recorder/FileWriter.h"
#include "openeaagles/recorder/FileReader.h"
#include "openeaagles/recorder/DataRecorder.h"
#include "openeaagles/recorder/protobuf/DataRecord.pb.h"

#include "openeaagles/simulation/Simulation.h"

namespace oe {

namespace Recorder { class DataRecorder; class TabPrinter; class FileWriter; class PrintSelected; }

namespace test {

//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
class DataRecordTest : public recorder::OutputHandler
{
    DECLARE_SUBCLASS(DataRecordTest, recorder::OutputHandler)

public:

    DataRecordTest();

    // Slot functions
    virtual bool setSlotFileName(basic::String* const msg);
    virtual bool setSlotTabPrinter(recorder::TabPrinter* msg);
    virtual bool setSlotFileWriter(recorder::FileWriter* msg);
    virtual bool setSlotFileReader(recorder::FileReader* msg);
    virtual bool setSlotRecordData(Simulation::DataRecorder* const msg);
    virtual bool setSlotPrintPlayer(recorder::PrintPlayer* msg);
    virtual bool setSlotPrintSelected(recorder::PrintSelected* msg);
    virtual bool setSlotPrintSelected2(recorder::PrintSelected* msg);

    // Select one of these in main.cpp
    bool testEvents();      // switch to test each possible event message
    bool testSerialize();   // Test to serialize and parse a set of messages

protected:
    void eventTestMenu();
    void readSerialFromFile();

   // all messages:
   recorder::DataRecordHandle* testFileIdMsg(int run);
   recorder::DataRecordHandle* testNewPlayerEventMsg();
   recorder::DataRecordHandle* testPlayerRemovedEventMsg();
   recorder::DataRecordHandle* testPlayerDataMsg();
   recorder::DataRecordHandle* testPlayerDamagedEventMsg();
   recorder::DataRecordHandle* testPlayerCollisionEventMsg();
   recorder::DataRecordHandle* testPlayerCrashEventMsg();
   recorder::DataRecordHandle* testPlayerKilledEventMsg(unsigned int type);
   recorder::DataRecordHandle* testWeaponReleaseEventMsg(unsigned int side);
   recorder::DataRecordHandle* testWeaponHungEventMsg();
   recorder::DataRecordHandle* testWeaponDetonationEventMsg();
   recorder::DataRecordHandle* testGunFiredEventMsg();
   recorder::DataRecordHandle* testNewTrackEventMsg();
   recorder::DataRecordHandle* testTrackRemovedEventMsg();
   recorder::DataRecordHandle* testTrackDataMsg();

   recorder::DataRecordHandle* testLastMsg();

   // Recursive function to look at each embedded message
   bool processMessage(const google::protobuf::Message* const msg);

   // Set comparison criteria:
   bool setMsgToken(const unsigned int token);
   bool setFieldOfInterest(const std::string fieldName );
   bool setCompareToValue(const std::string strVal);
   bool setCompareToValue(const int numVal );
   bool setCompareToValue(const double dblVal );
   bool setCompareCondition(const recorder::PrintSelected::Condition cc);
   bool setTimeOnly(const bool flg );

   double getSimTime();
   double getExecTime();
   double getUtcTime();

private:
   const char* fileName;
   basic::safe_ptr<recorder::PrintPlayer> myPrintPlayer;
   basic::safe_ptr<recorder::PrintSelected> myPrintSelected;
   basic::safe_ptr<recorder::PrintSelected> myPrintSelected2;
   basic::safe_ptr<recorder::TabPrinter> myRecPrint;
   basic::safe_ptr<recorder::FileWriter> myFileWrite;
   basic::safe_ptr<recorder::FileReader> myFileRead;
   basic::safe_ptr<Simulation::DataRecorder> myDataRec;

   std::string fieldName;
   recorder::PrintSelected::Condition condition;
   int compareI;
   std::string compareS;
   double compareD;
   std::string fullFieldName;
   bool fieldSelected;
   unsigned int timesCalled;

   // Struct and array for saving multiple sets of selection criteria
   unsigned int selectionNum;
   struct SelectionCriteria {
      unsigned int msgToken;
      std::string fieldName;
      double compareValD;
      std::string compareValS;
      int compareValI;
      recorder::PrintSelected::Condition condition;
      bool timeOnly;
   };
   SelectionCriteria selection[20];

};

}
}

#endif
