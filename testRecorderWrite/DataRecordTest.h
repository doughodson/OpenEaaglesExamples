//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
#ifndef __DataRecordTest_H__
#define __DataRecordTest_H__

#include "openeaagles/basic/Component.h"
#include "openeaagles/basic/basicFF.h"
#include "openeaagles/recorder/recorderFF.h"
#include "openeaagles/recorder/TabPrinter.h"
#include "openeaagles/recorder/PrintPlayer.h"
#include "openeaagles/recorder/PrintSelected.h"
#include "openeaagles/recorder/FileWriter.h"
#include "openeaagles/recorder/FileReader.h"
#include "openeaagles/recorder/DataRecorder.h"
#include "openeaagles/recorder/DataRecord.pb.h"

#include "openeaagles/simulation/Simulation.h"

namespace Recorder { class DataRecorder; class TabPrinter; class FileWriter; class PrintSelected; }

namespace Eaagles {
namespace TestRecorder {


//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------
   class DataRecordTest : public Eaagles::Recorder::OutputHandler{
   DECLARE_SUBCLASS(DataRecordTest, Eaagles::Recorder::OutputHandler)

public:

    DataRecordTest();

    // Slot functions
    virtual bool setSlotFileName(Eaagles::Basic::String* const msg);
    virtual bool setSlotTabPrinter(Eaagles::Recorder::TabPrinter* msg);
    virtual bool setSlotFileWriter(Eaagles::Recorder::FileWriter* msg);
    virtual bool setSlotFileReader(Eaagles::Recorder::FileReader* msg);
    virtual bool setSlotRecordData(Eaagles::Simulation::DataRecorder* const msg);
    virtual bool setSlotPrintPlayer(Eaagles::Recorder::PrintPlayer* msg);
    virtual bool setSlotPrintSelected(Eaagles::Recorder::PrintSelected* msg);
    virtual bool setSlotPrintSelected2(Eaagles::Recorder::PrintSelected* msg);

    // Select one of these in main.cpp
    bool testEvents();      // switch to test each possible event message
    bool testSerialize();   // Test to serialize and parse a set of messages

protected:
    void eventTestMenu();
    void readSerialFromFile();

   // all messages:
   Eaagles::Recorder::DataRecordHandle* testFileIdMsg(int run);
   Eaagles::Recorder::DataRecordHandle* testNewPlayerEventMsg();
   Eaagles::Recorder::DataRecordHandle* testPlayerRemovedEventMsg();
   Eaagles::Recorder::DataRecordHandle* testPlayerDataMsg();
   Eaagles::Recorder::DataRecordHandle* testPlayerDamagedEventMsg();
   Eaagles::Recorder::DataRecordHandle* testPlayerCollisionEventMsg();
   Eaagles::Recorder::DataRecordHandle* testPlayerCrashEventMsg();
   Eaagles::Recorder::DataRecordHandle* testPlayerKilledEventMsg(unsigned int type);
   Eaagles::Recorder::DataRecordHandle* testWeaponReleaseEventMsg(unsigned int side);
   Eaagles::Recorder::DataRecordHandle* testWeaponHungEventMsg();
   Eaagles::Recorder::DataRecordHandle* testWeaponDetonationEventMsg();
   Eaagles::Recorder::DataRecordHandle* testGunFiredEventMsg();
   Eaagles::Recorder::DataRecordHandle* testNewTrackEventMsg();
   Eaagles::Recorder::DataRecordHandle* testTrackRemovedEventMsg();
   Eaagles::Recorder::DataRecordHandle* testTrackDataMsg();

   Eaagles::Recorder::DataRecordHandle* testLastMsg();

   // Recursive function to look at each embedded message
   bool processMessage(const google::protobuf::Message* const msg);

   // Set comparison criteria:
   bool setMsgToken(const unsigned int token);
   bool setFieldOfInterest(const std::string fieldName );
   bool setCompareToValue(const std::string strVal);
   bool setCompareToValue(const int numVal );
   bool setCompareToValue(const double dblVal );
   bool setCompareCondition(const Eaagles::Recorder::PrintSelected::Condition cc );
   bool setTimeOnly(const bool flg );

   double getSimTime();
   double getExecTime();
   double getUtcTime();

private:
   const char* fileName;
   SPtr<Eaagles::Recorder::PrintPlayer> myPrintPlayer;
   SPtr<Eaagles::Recorder::PrintSelected> myPrintSelected;
   SPtr<Eaagles::Recorder::PrintSelected> myPrintSelected2;
   SPtr<Eaagles::Recorder::TabPrinter> myRecPrint;
   SPtr<Eaagles::Recorder::FileWriter> myFileWrite;
   SPtr<Eaagles::Recorder::FileReader> myFileRead;
   SPtr<Eaagles::Simulation::DataRecorder> myDataRec;

   std::string fieldName;
   Eaagles::Recorder::PrintSelected::Condition condition;
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
      Eaagles::Recorder::PrintSelected::Condition condition;
      bool timeOnly;
   };
   SelectionCriteria selection[20];

};



}
}

#endif
