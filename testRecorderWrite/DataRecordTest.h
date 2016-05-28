
#ifndef __DataRecordTest_H__
#define __DataRecordTest_H__

#include "openeaagles/base/Component.h"
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
}

//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
class DataRecordTest : public oe::recorder::OutputHandler
{
    DECLARE_SUBCLASS(DataRecordTest, oe::recorder::OutputHandler)

public:

    DataRecordTest();

    // Slot functions
    virtual bool setSlotFileName(oe::base::String* const msg);
    virtual bool setSlotTabPrinter(oe::recorder::TabPrinter* msg);
    virtual bool setSlotFileWriter(oe::recorder::FileWriter* msg);
    virtual bool setSlotFileReader(oe::recorder::FileReader* msg);
    virtual bool setSlotRecordData(oe::simulation::DataRecorder* const msg);
    virtual bool setSlotPrintPlayer(oe::recorder::PrintPlayer* msg);
    virtual bool setSlotPrintSelected(oe::recorder::PrintSelected* msg);
    virtual bool setSlotPrintSelected2(oe::recorder::PrintSelected* msg);

    // Select one of these in main.cpp
    bool testEvents();      // switch to test each possible event message
    bool testSerialize();   // Test to serialize and parse a set of messages

protected:
    void eventTestMenu();
    void readSerialFromFile();

   // all messages:
   oe::recorder::DataRecordHandle* testFileIdMsg(int run);
   oe::recorder::DataRecordHandle* testNewPlayerEventMsg();
   oe::recorder::DataRecordHandle* testPlayerRemovedEventMsg();
   oe::recorder::DataRecordHandle* testPlayerDataMsg();
   oe::recorder::DataRecordHandle* testPlayerDamagedEventMsg();
   oe::recorder::DataRecordHandle* testPlayerCollisionEventMsg();
   oe::recorder::DataRecordHandle* testPlayerCrashEventMsg();
   oe::recorder::DataRecordHandle* testPlayerKilledEventMsg(unsigned int type);
   oe::recorder::DataRecordHandle* testWeaponReleaseEventMsg(unsigned int side);
   oe::recorder::DataRecordHandle* testWeaponHungEventMsg();
   oe::recorder::DataRecordHandle* testWeaponDetonationEventMsg();
   oe::recorder::DataRecordHandle* testGunFiredEventMsg();
   oe::recorder::DataRecordHandle* testNewTrackEventMsg();
   oe::recorder::DataRecordHandle* testTrackRemovedEventMsg();
   oe::recorder::DataRecordHandle* testTrackDataMsg();

   oe::recorder::DataRecordHandle* testLastMsg();

   // Recursive function to look at each embedded message
   bool processMessage(const google::protobuf::Message* const msg);

   // Set comparison criteria:
   bool setMsgToken(const unsigned int token);
   bool setFieldOfInterest(const std::string fieldName );
   bool setCompareToValue(const std::string strVal);
   bool setCompareToValue(const int numVal );
   bool setCompareToValue(const double dblVal );
   bool setCompareCondition(const oe::recorder::PrintSelected::Condition cc);
   bool setTimeOnly(const bool flg );

   double getSimTime();
   double getExecTime();
   double getUtcTime();

private:
   const char* fileName;
   oe::base::safe_ptr<oe::recorder::PrintPlayer> myPrintPlayer;
   oe::base::safe_ptr<oe::recorder::PrintSelected> myPrintSelected;
   oe::base::safe_ptr<oe::recorder::PrintSelected> myPrintSelected2;
   oe::base::safe_ptr<oe::recorder::TabPrinter> myRecPrint;
   oe::base::safe_ptr<oe::recorder::FileWriter> myFileWrite;
   oe::base::safe_ptr<oe::recorder::FileReader> myFileRead;
   oe::base::safe_ptr<oe::simulation::DataRecorder> myDataRec;

   std::string fieldName;
   oe::recorder::PrintSelected::Condition condition;
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
      oe::recorder::PrintSelected::Condition condition;
      bool timeOnly;
   };
   SelectionCriteria selection[20];

};

#endif
