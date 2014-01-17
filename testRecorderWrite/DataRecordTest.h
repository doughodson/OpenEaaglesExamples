//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_DataRecordTest_H__
#define __Eaagles_Test_DataRecordTest_H__

#include "openeaagles/basic/Component.h"
#include "openeaagles/recorder/TabPrinter.h"
#include "openeaagles/recorder/PrintPlayer.h"
#include "openeaagles/recorder/PrintSelected.h"
#include "openeaagles/recorder/FileWriter.h"
#include "openeaagles/recorder/FileReader.h"
#include "openeaagles/recorder/DataRecorder.h"
#include "openeaagles/recorder/DataRecord.pb.h"

#include "openeaagles/simulation/Simulation.h"

namespace Eaagles {

namespace Recorder { class DataRecorder; class TabPrinter; class FileWriter; class PrintSelected; }

namespace Test {

//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
class DataRecordTest : public Recorder::OutputHandler
{
    DECLARE_SUBCLASS(DataRecordTest, Recorder::OutputHandler)

public:

    DataRecordTest();

    // Slot functions
    virtual bool setSlotFileName(Basic::String* const msg);
    virtual bool setSlotTabPrinter(Recorder::TabPrinter* msg);
    virtual bool setSlotFileWriter(Recorder::FileWriter* msg);
    virtual bool setSlotFileReader(Recorder::FileReader* msg);
    virtual bool setSlotRecordData(Simulation::DataRecorder* const msg);
    virtual bool setSlotPrintPlayer(Recorder::PrintPlayer* msg);
    virtual bool setSlotPrintSelected(Recorder::PrintSelected* msg);
    virtual bool setSlotPrintSelected2(Recorder::PrintSelected* msg);

    // Select one of these in main.cpp
    bool testEvents();      // switch to test each possible event message
    bool testSerialize();   // Test to serialize and parse a set of messages

protected:
    void eventTestMenu();
    void readSerialFromFile();

   // all messages:
   Recorder::DataRecordHandle* testFileIdMsg(int run);
   Recorder::DataRecordHandle* testNewPlayerEventMsg();
   Recorder::DataRecordHandle* testPlayerRemovedEventMsg();
   Recorder::DataRecordHandle* testPlayerDataMsg();
   Recorder::DataRecordHandle* testPlayerDamagedEventMsg();
   Recorder::DataRecordHandle* testPlayerCollisionEventMsg();
   Recorder::DataRecordHandle* testPlayerCrashEventMsg();
   Recorder::DataRecordHandle* testPlayerKilledEventMsg(unsigned int type);
   Recorder::DataRecordHandle* testWeaponReleaseEventMsg(unsigned int side);
   Recorder::DataRecordHandle* testWeaponHungEventMsg();
   Recorder::DataRecordHandle* testWeaponDetonationEventMsg();
   Recorder::DataRecordHandle* testGunFiredEventMsg();
   Recorder::DataRecordHandle* testNewTrackEventMsg();
   Recorder::DataRecordHandle* testTrackRemovedEventMsg();
   Recorder::DataRecordHandle* testTrackDataMsg();

   Recorder::DataRecordHandle* testLastMsg();

   // Recursive function to look at each embedded message
   bool processMessage(const google::protobuf::Message* const msg);

   // Set comparison criteria:
   bool setMsgToken(const unsigned int token);
   bool setFieldOfInterest(const std::string fieldName );
   bool setCompareToValue(const std::string strVal);
   bool setCompareToValue(const int numVal );
   bool setCompareToValue(const double dblVal );
   bool setCompareCondition(const Recorder::PrintSelected::Condition cc );
   bool setTimeOnly(const bool flg );

   double getSimTime();
   double getExecTime();
   double getUtcTime();

private:
   const char* fileName;
   SPtr<Recorder::PrintPlayer> myPrintPlayer;
   SPtr<Recorder::PrintSelected> myPrintSelected;
   SPtr<Recorder::PrintSelected> myPrintSelected2;
   SPtr<Recorder::TabPrinter> myRecPrint;
   SPtr<Recorder::FileWriter> myFileWrite;
   SPtr<Recorder::FileReader> myFileRead;
   SPtr<Simulation::DataRecorder> myDataRec;

   std::string fieldName;
   Recorder::PrintSelected::Condition condition;
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
      Recorder::PrintSelected::Condition condition;
      bool timeOnly;
   };
   SelectionCriteria selection[20];

};

}
}

#endif
