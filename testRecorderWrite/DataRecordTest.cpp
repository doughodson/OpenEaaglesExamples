//------------------------------------------------------------------------------
// Class: DataRecordTest
//------------------------------------------------------------------------------

#include "DataRecordTest.h"

#include "openeaagles/recorder/FileReader.h"
#include "openeaagles/recorder/FileWriter.h"
#include "openeaagles/recorder/InputHandler.h"
#include "openeaagles/recorder/NetInput.h"

#include "openeaagles/recorder/DataRecorder.h"
#include "openeaagles/recorder/OutputHandler.h"
#include "openeaagles/recorder/NetOutput.h"
#include "openeaagles/recorder/DataRecordHandle.h"
#include "openeaagles/recorder/TabPrinter.h"
#include "openeaagles/recorder/PrintPlayer.h"
#include "openeaagles/recorder/PrintSelected.h"

#include "openeaagles/recorder/DataRecord.pb.h"

#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/Station.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/DataRecorder.h"

#include "openeaagles/basic/String.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/support.h"

#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Test {


//==============================================================================
// DataRecordTest
//==============================================================================

IMPLEMENT_SUBCLASS(DataRecordTest,"DataRecordTest")
EMPTY_SERIALIZER(DataRecordTest)

BEGIN_SLOTTABLE(DataRecordTest)
   "tabPrinter",         // 1) Pb buffer data record tab printer
   "dataFileWriter",     // 2) Pb buffer data file writer (serialized)
   "dataFileReader",     // 3) Pb buffer data file reader (serialized)
   "fileName",           // 4) for message data output
   "printPlayer",        // 5) another printer
   "printSelected",      // 6) printer using reflection
   "printSelected2",      // 7) printer using reflection (std out only)
END_SLOTTABLE(DataRecordTest)

// Map slot table to handles 
BEGIN_SLOT_MAP(DataRecordTest)
   ON_SLOT(1, setSlotTabPrinter,     Recorder::TabPrinter)
   ON_SLOT(2, setSlotFileWriter,     Recorder::FileWriter)
   ON_SLOT(3, setSlotFileReader,     Recorder::FileReader)
   ON_SLOT(4, setSlotFileName,       Basic::String)
   ON_SLOT(5, setSlotPrintPlayer,    Recorder::PrintPlayer)
   ON_SLOT(6, setSlotPrintSelected,  Recorder::PrintSelected)
   ON_SLOT(7, setSlotPrintSelected2, Recorder::PrintSelected)

END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
DataRecordTest::DataRecordTest()
{
   STANDARD_CONSTRUCTOR()
   fileName = "";
   myRecPrint = 0;
   myPrintPlayer = 0;
   myPrintSelected = 0;
   myFileWrite = 0;
   myFileRead = 0;
   myDataRec = 0;
   fieldSelected = false;
   timesCalled = 0;
   selectionNum = 0;

   // Initialize array for saving multiple sets of selection criteria
   for (unsigned int i = 0; i < 20; i++) {
      selection[i].msgToken = 0;
      selection[i].fieldName = "";
      selection[i].compareValD = 0;
      selection[i].compareValS = "";
      selection[i].compareValI = 0;
      selection[i].condition = Eaagles::Recorder::PrintSelected::EQ;
      selection[i].timeOnly = false;
   }

}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void DataRecordTest::copyData(const DataRecordTest& org, const bool cc)
{
   BaseClass::copyData(org);
   fileName = org.fileName;

   if (cc) {
      myRecPrint = 0;
      myFileWrite = 0;
      myFileRead = 0;
      myDataRec = 0;
      myPrintPlayer = 0;
      myPrintSelected = 0;
      myPrintSelected2 = 0;
      fieldSelected = false;
      selectionNum = 0;
   }
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void DataRecordTest::deleteData()
{
   myRecPrint = 0;
   myFileWrite = 0;
   myFileRead = 0;
   myDataRec = 0;
   myPrintPlayer = 0;
   myPrintSelected = 0;
   myPrintSelected2 = 0;
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//setSlotTabPrinter() -- Set slot for pointer to the TabPrinter class
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotTabPrinter(Recorder::TabPrinter* const p)
{
   bool ok = false;
   if (p != 0) {
      myRecPrint = p;
      myRecPrint ->ref();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
//setSlotPrintPlayer() -- Set slot for pointer to the another print class
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotPrintPlayer(Recorder::PrintPlayer* const p)
{
   bool ok = false;
   if (p != 0) {
      myPrintPlayer = p;
      myPrintPlayer ->ref();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
//setSlotPrintSelected() -- Set slot for pointer to the printer using reflection
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotPrintSelected(Recorder::PrintSelected* const p)
{
   bool ok = false;
   if (p != 0) {
      myPrintSelected = p;
      myPrintSelected ->ref();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
//setSlotPrintSelected2() -- Set slot for pointer to the printer using reflection (std out only)
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotPrintSelected2(Recorder::PrintSelected* const p)
{
   bool ok = false;
   if (p != 0) {
      myPrintSelected2 = p;
      myPrintSelected2 ->ref();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
//setSlotFileWriter() -- Set slot for pointer to the file (serialized) write class
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotFileWriter(Recorder::FileWriter* const p)
{
   bool ok = false;
   if (p != 0) {
      myFileWrite = p;
      myFileWrite ->ref();
      ok = true;
   }
   return ok;
}


//------------------------------------------------------------------------------
//setSlotFileReader() -- Set slot for pointer to the file (serialized) read class
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotFileReader(Recorder::FileReader* const p)
{
   bool ok = false;
   if (p != 0) {
      myFileRead = p;
      myFileRead ->ref();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
//setSlotFileName() -- Get file name for test message output
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotFileName(Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      fileName = msg->getCopyString();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
//setSlotRecordData() -- Set slot for pointer to the RecorderComponent class
//------------------------------------------------------------------------------
bool DataRecordTest::setSlotRecordData(Simulation::DataRecorder* const p)
{
   bool ok = false;
   if (p != 0) {
      myDataRec = p;
      myDataRec ->ref();
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Component
//------------------------------------------------------------------------------
Basic::Object* DataRecordTest::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// testSerialize - Test serialize/parsing to/from a file
//------------------------------------------------------------------------------
bool DataRecordTest::testSerialize()
{
   int exitTest = 1;

   while (exitTest == 1) {

      std::cout << "Serializing to file:" << std::endl;
      myFileWrite->openFile();
      int runNum = 1;

      // Write message
      myFileWrite->processRecord(testFileIdMsg(runNum));

      // test the "isDataEnabled" member function
      bool writeEnabled = myFileWrite->isDataEnabled(REID_NEW_PLAYER);

      //  Write messages
      myFileWrite->processRecord(testNewPlayerEventMsg());
      myFileWrite->processRecord(testWeaponDetonationEventMsg());
      myFileWrite->processRecord(testNewPlayerEventMsg());
      myFileWrite->processRecord(testNewTrackEventMsg());
      myFileWrite->processRecord(testPlayerRemovedEventMsg());
      myFileWrite->processRecord(testPlayerDataMsg());
      myFileWrite->processRecord(testPlayerDamagedEventMsg());
      myFileWrite->processRecord(testPlayerCollisionEventMsg());
      myFileWrite->processRecord(testPlayerCrashEventMsg());

      // Call testPlayerKilledEventMsg with input parameters
      myFileWrite->processRecord(testPlayerKilledEventMsg(0));
      myFileWrite->processRecord(testPlayerKilledEventMsg(0));
      myFileWrite->processRecord(testPlayerKilledEventMsg(1));


      // Call testWeaponReleaseEventMsg with input parameters
      myFileWrite->processRecord(testWeaponReleaseEventMsg(0));
      myFileWrite->processRecord(testWeaponReleaseEventMsg(1));
      myFileWrite->processRecord(testWeaponHungEventMsg());
      myFileWrite->processRecord(testGunFiredEventMsg());
      myFileWrite->processRecord(testTrackRemovedEventMsg());
      myFileWrite->processRecord(testTrackDataMsg());

      // Write last message
      myFileWrite->processRecord(testLastMsg());

      // close the file
      myFileWrite->closeFile();

      // get the file name:
      const char* fullname = myFileWrite->getFullFilename();
      std::cout << "full file name: " << fullname << std::endl;

      // 3) read the file back:
      readSerialFromFile();

      std::cout << "enter 0 to exit test: " << std::endl;
      std::cin >> exitTest;

   }  // end while not exit test

   return true;
}

//------------------------------------------------------------------------------
// readSerialFromFile - Read and parse serialized messages from a file
//------------------------------------------------------------------------------
void DataRecordTest::readSerialFromFile()
{
   // Read all the messages on the file till "done"

   int outType = 0;
   std::cout << "select output: " << std::endl;
   std::cout << "  1: Tab printer " << std::endl;
   std::cout << "  2: Print Player " << std::endl;
   std::cout << "  3: Print Selection to file" << std::endl;
 //  std::cout << "  4: Print Selection to std out" << std::endl;

//   std::cout << "enter 1 for tab printer: " << std::endl;
   std::cin >> outType;

   bool fileDone = false;
   int msgNum = 0;
   myFileRead->openFile();
   if (outType == 1) {
      myRecPrint->openFile();
   }

   if (outType == 2) {
      // Need to open a file for print player if that's what we're using
      //    myPrintPlayer->openFile();
   }

   if ((outType == 3) && (myPrintSelected != 0)) {
      // Need to open a file for print selection if that's what we're using
      myPrintSelected->openFile();
      // For more than one set of criteria, loop till done
      bool selectDone = false;
      while (!selectDone) {
         std::cout << "Select More Fields? Y/N: ";
         std::string selFields;
         std::cin >> selFields;
         if ((selFields == "Y") || (selFields == "y")) {
            fieldSelected = false;
            // Time?
            {
               std::cout << "select by Time? Y/N: " ;
               std::string selTime = "N";
               std::cin >> selTime;
               if ((selTime == "Y") || (selTime == "y")) {
                  const Recorder::Pb::DataRecord* dataRecord = new Recorder::Pb::DataRecord();
                  processMessage(&dataRecord->time());
               }
            }

            // ask for msg event token and other data
            std::cout << "Select message by event token number? Y/N: ";
            std::string selMsg;
            std::cin  >> selMsg;
            if ((selMsg == "N") || (selMsg == "n")) {
               // Select all messages
               setMsgToken(REID_UNHANDLED_ID_TOKEN);
               setTimeOnly(true);
               selectionNum++;
            }
            if ((selMsg == "Y") || (selMsg == "y")) {
               std::cout << "Enter message event token number: ";
               unsigned int eventNum;
               std::cin  >> eventNum;
               if (eventNum >= REID_END_OF_DATA &&  eventNum <= REID_LAST_USER_EVENT) {
                  // Select this message
                  setMsgToken(eventNum);

                  // Go through the message to select the field and criteria to match
                  const google::protobuf::Message* processMsg = 0;
                  const Recorder::Pb::DataRecord* testDr = new Recorder::Pb::DataRecord();
                  switch (eventNum) {
                     case REID_FILE_ID:           processMsg = &testDr->file_id_msg();                 break;
                     case REID_NEW_PLAYER:        processMsg = &testDr->new_player_event_msg();        break;
                     case REID_PLAYER_REMOVED:    processMsg = &testDr->player_removed_event_msg();    break;
                     case REID_PLAYER_DATA:       processMsg = &testDr->player_data_msg();             break;
                     case REID_PLAYER_DAMAGED:    processMsg = &testDr->player_damaged_event_msg();    break;
                     case REID_PLAYER_COLLISION:  processMsg = &testDr->player_collision_event_msg();  break;
                     case REID_PLAYER_CRASH:      processMsg = &testDr->player_crash_event_msg();      break;
                     case REID_PLAYER_KILLED:     processMsg = &testDr->player_killed_event_msg();     break;
                     case REID_WEAPON_RELEASED:   processMsg = &testDr->weapon_release_event_msg();    break;
                     case REID_WEAPON_HUNG:       processMsg = &testDr->weapon_hung_event_msg();       break;
                     case REID_WEAPON_DETONATION: processMsg = &testDr->weapon_detonation_event_msg(); break;
                     case REID_GUN_FIRED:         processMsg = &testDr->gun_fired_event_msg();         break;
                     case REID_NEW_TRACK:         processMsg = &testDr->new_track_event_msg();         break;
                     case REID_TRACK_REMOVED:     processMsg = &testDr->track_removed_event_msg();     break;
                     case REID_TRACK_DATA:        processMsg = &testDr->track_data_msg();              break;
                     default: break;
                  }

                  // Traverse the message and save the selection criteria
                  if (processMsg != 0) {
                     fieldSelected = false;  // start over
                     processMessage(processMsg);
                     selectionNum++;
                  }
               }
            }
         }
         else {
            selectDone = true;
         }
      }
   }

   if (myFileRead != 0) {
      while (!fileDone) {
         std::cout << std::endl << "Parsing from file msg: " << msgNum+1 << std::endl;
         msgNum++;
         const Recorder::DataRecordHandle* readHandle = myFileRead->readRecord();

         if (readHandle != 0) {
            // Check for last message
            const Eaagles::Recorder::Pb::DataRecord* testDr = readHandle->getRecord();
            unsigned int recId = testDr->id();
            std::cout << "Data record ID: " << recId << std::endl;
            if (recId == REID_END_OF_DATA) {
               std::cout << "Found last record" << std::endl;
               fileDone = true;
            }

            // print the message
            if (outType == 1 && (myRecPrint != 0)) {
               myRecPrint->processRecord(readHandle);
            }
            if (outType == 2 && (myPrintPlayer != 0)) {
               myPrintPlayer->processRecord(readHandle);
            }
            if (outType == 3 && (myPrintSelected != 0)) {
               // Process the message according to criteria already set
               // Do for each set of selection criteria. It should append to already
               // opened file.
               // Need to set criteria here.
               for (unsigned int i = 0; i < selectionNum; i++) {
                  // This slot could be a single message (e.g., REID_NEW_PLAYER),
                  // a group of messages (e.g., PLAYER), or ALL
                  myPrintSelected->setMsgToken(selection[i].msgToken);
                  myPrintSelected->setFieldOfInterest(selection[i].fieldName);
                  myPrintSelected->setCompareToValue(selection[i].compareValD);
                  myPrintSelected->setCompareToValue(selection[i].compareValS);
                  myPrintSelected->setCompareToValue(selection[i].compareValI);
                  myPrintSelected->setCompareCondition(selection[i].condition);
                  myPrintSelected->setTimeOnly(selection[i].timeOnly);

                  // ----------------------------------------------------------------
                  // Process the message
                  // ----------------------------------------------------------------
                  myPrintSelected->processRecord(readHandle);
               }
            }
         }
         else std::cout << "readHandle is 0" << std::endl;
      }

      myFileRead->closeFile();

      // Close whichever output handler we're using for test
      if (outType == 1) {
         if (myRecPrint != 0) myRecPrint->closeFile();
      }
      if (outType == 2) {
         if (myPrintPlayer != 0) myPrintPlayer->closeFile();
      }
      if (outType == 3) {
         if (myPrintSelected != 0) myPrintSelected->closeFile();
      }

   }
   else std::cout << "myFileRead is 0 (failed to open file)" << std::endl;

}

//------------------------------------------------------------------------------
// Test Events
//------------------------------------------------------------------------------
bool DataRecordTest::testEvents()
{
   char ynCont = 'y';
   char ynMenu = 'y';
   unsigned int testNumber = 0;
 //  unsigned int outSelect;
 //  bool sendToFile = false;

   while (ynCont != 'n') {
      if (ynMenu != 'n') {
         eventTestMenu();   // put up the menu
      }
      
      std::cout << "Select an event to test: ";
      std::cin  >> testNumber;

      if (testNumber > 0) {
//         std::cout << "Select 0 to print to output, or 1 to print to a file: ";
//         std::cin  >> outSelect;
//         if (outSelect > 0) sendToFile = true;

        const Eaagles::Recorder::DataRecordHandle* handle = 0;

         switch (testNumber) {
            case  1: { handle = testFileIdMsg(1); break; }
            case  2: { handle = testNewPlayerEventMsg(); break; }
            case  3: { handle = testPlayerRemovedEventMsg(); }
            case  4: { handle = testPlayerDataMsg(); break; }
            case  5: { handle = testPlayerDamagedEventMsg(); break; }
            case  6: { handle = testPlayerCollisionEventMsg(); break; }
            case  7: { handle = testPlayerCrashEventMsg(); break; }
            case  8: { handle = testPlayerKilledEventMsg(0); break; }
            case  9: { handle = testWeaponReleaseEventMsg(0); break; }
            case 10: { handle = testWeaponHungEventMsg(); break; }
            case 11: { handle = testWeaponDetonationEventMsg(); break; }
            case 12: { handle = testGunFiredEventMsg(); break; }
            case 13: { handle = testNewTrackEventMsg(); break; }
            case 14: { handle = testTrackRemovedEventMsg(); break; }
            case 15: { handle = testTrackDataMsg(); break; }
            case 16: { handle = testLastMsg(); break; }
            default:
               { ynCont = 'n'; handle = 0; exit(0);  break; }
         }
      }
      else ynCont = 'n';

   }

   return true;
}

//------------------------------------------------------------------------------
// Event Test Menu
//------------------------------------------------------------------------------
void DataRecordTest::eventTestMenu()
{
   std::cout << "=====================================================" << std::endl;
   std::cout << "Event Tests" << std::endl;
   std::cout << "=====================================================" << std::endl;
   

   std::cout <<
         "case  1:  testFileIdMsg" << std::endl <<
         "case  2:  testNewPlayerEventMsg"        << std::endl <<
         "case  3:  testPlayerRemovedEventMsg"    << std::endl <<
         "case  4:  testPlayerDataMsg"            << std::endl <<
         "case  5:  testPlayerDamagedEventMsg"    << std::endl <<
         "case  6:  testPlayerCollisionEventMsg"  << std::endl <<
         "case  7:  testPlayerCrashEventMsg"      << std::endl <<
         "case  8:  testPlayerKilledEventMsg"     << std::endl <<
         "case  9:  testWeaponReleaseEventMsg"    << std::endl <<
         "case 10:  testWeaponHungEventMsg"       << std::endl <<
         "case 11:  testWeaponDetonationEventMsg" << std::endl <<
         "case 12:  testGunFiredEventMsg"         << std::endl <<
         "case 13:  testNewTrackEventMsg"         << std::endl <<
         "case 14:  testTrackRemovedEventMsg"     << std::endl <<
         "case 15:  testTrackDataMsg"             << std::endl <<
         "case 16:  testLastMsg"                  << std::endl <<
         "   0:     Exit"                         << std::endl;
}

// =================================================================================================
// All tests
// =================================================================================================

// ------------------------------------------------------------------------------------------------
// testFileIdMsg: Sets some File ID msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testFileIdMsg(int run)
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::FileIdMsg* msg = recordMsg->mutable_file_id_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_FILE_ID);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // other
   msg->set_application("app1");
   msg->set_case_num(135);
   msg->set_day(30);
   msg->set_event_name("event135");
   msg->set_mission_num(12);
   msg->set_month(2);
   msg->set_year(2012);
   msg->set_subject_num(6);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   // if (serializing) {
   //     myFileWrite->processRecord(handle);
   // }

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testNewPlayerEventMsg: Sets some New Player msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testNewPlayerEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::NewPlayerEventMsg* msg = recordMsg->mutable_new_player_event_msg();

   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();

   // required
   recordMsg->set_id(REID_NEW_PLAYER);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   unsigned int pId = 0;
   std::string pName = "";
   std::string pFedName = "";

   timesCalled++;
   pId = 123 * timesCalled;
      
   // required
   pIdMsg->set_id(pId);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   pIdMsg->set_side(1);

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testPlayerRemovedEventMsg: Sets some Player Removed msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testPlayerRemovedEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::PlayerRemovedEventMsg* msg = recordMsg->mutable_player_removed_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);
   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();

   // required
   recordMsg->set_id(REID_PLAYER_REMOVED);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // required
   pIdMsg->set_id(123);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testPlayerDataMsg: Sets some Player Data msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testPlayerDataMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::PlayerDataMsg* msg = recordMsg->mutable_player_data_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);
   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();

   // required
   recordMsg->set_id(REID_PLAYER_DATA);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // required
   pIdMsg->set_id(123);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testPlayerDamagedEventMsg: Sets some Player Damaged msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testPlayerDamagedEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::PlayerDamagedEventMsg* msg = recordMsg->mutable_player_damaged_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);
   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();

   const google::protobuf::Message* recMsg = new Eaagles::Recorder::Pb::DataRecord();
   const google::protobuf::Descriptor* descriptor = recMsg->GetDescriptor();
   const google::protobuf::FieldDescriptor* id_field = descriptor->FindFieldByName("id");

   const google::protobuf::Reflection* reflection = recMsg->GetReflection();
   unsigned int id = reflection->GetUInt32(*recMsg, id_field);


   // required
   recordMsg->set_id(REID_PLAYER_DAMAGED);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // required
   pIdMsg->set_id(123);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testPlayerCollisionEventMsg: Sets some Player Collision msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testPlayerCollisionEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::PlayerCollisionEventMsg* msg = recordMsg->mutable_player_collision_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);
   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();
   Eaagles::Recorder::Pb::PlayerId* other = msg->mutable_other_player_id();

   // required
   recordMsg->set_id(REID_PLAYER_COLLISION);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // required
   pIdMsg->set_id(123);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   //    optional PlayerId other_player_id = 3;
   msg->mutable_other_player_id()->set_fed_name("OtherFed");
   msg->mutable_other_player_id()->set_id(975);
   msg->mutable_other_player_id()->set_name("OtherPly");

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testPlayerCrashEventMsg: Sets some Player Crash msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testPlayerCrashEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::PlayerCrashEventMsg* msg = recordMsg->mutable_player_crash_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);
   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();

   // required
   recordMsg->set_id(REID_PLAYER_CRASH);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // required
   pIdMsg->set_id(123);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testPlayerKilledEventMsg: Sets some Player Killed msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testPlayerKilledEventMsg(unsigned int type)
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::PlayerKilledEventMsg* msg = recordMsg->mutable_player_killed_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);
   Eaagles::Recorder::Pb::PlayerId* pIdMsg = msg->mutable_id();
   Eaagles::Recorder::Pb::PlayerState* pStMsg = msg->mutable_state();

   // required
   recordMsg->set_id(REID_PLAYER_KILLED);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // required
   pIdMsg->set_id(123);
   pIdMsg->set_name("Player123");
   pIdMsg->set_fed_name("Fed123");

   // required
   pStMsg->mutable_pos()->set_x(10);
   pStMsg->mutable_pos()->set_y(20);
   pStMsg->mutable_pos()->set_z(30);

   // required
   pStMsg->mutable_angles()->set_x(.2);
   pStMsg->mutable_angles()->set_y(.3);
   pStMsg->mutable_angles()->set_z(.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testWeaponReleaseEventMsg: Sets some Weapon Released msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testWeaponReleaseEventMsg(unsigned int side)
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::WeaponReleaseEventMsg* msg = recordMsg->mutable_weapon_release_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_WEAPON_RELEASED);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   msg->mutable_wpn_id()->set_id(10);
   msg->mutable_wpn_id()->set_fed_name("wpnFed");
   msg->mutable_wpn_id()->set_name("wpnName");

   msg->mutable_wpn_state()->mutable_angles()->set_x(10);
   msg->mutable_wpn_state()->mutable_angles()->set_y(11);
   msg->mutable_wpn_state()->mutable_angles()->set_z(12);
   msg->mutable_wpn_state()->mutable_pos()->set_x(20);
   msg->mutable_wpn_state()->mutable_pos()->set_y(21);
   msg->mutable_wpn_state()->mutable_pos()->set_z(22);
   msg->mutable_wpn_state()->mutable_vel()->set_x(100);
   msg->mutable_wpn_state()->mutable_vel()->set_y(101);
   msg->mutable_wpn_state()->mutable_vel()->set_z(102);

   msg->mutable_shooter_id()->set_id(20);
   msg->mutable_shooter_id()->set_fed_name("shooterFed");
   msg->mutable_shooter_id()->set_name("shooterName");
   msg->mutable_shooter_id()->set_side(side);

   msg->mutable_tgt_id()->set_id(50);
   msg->mutable_tgt_id()->set_fed_name("tgtFed");
   msg->mutable_tgt_id()->set_name("tgtName");

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;
   return handle;
}

// ------------------------------------------------------------------------------------------------
// testWeaponHungEventMsg: Sets some Weapon Hung msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testWeaponHungEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::WeaponHungEventMsg* msg = recordMsg->mutable_weapon_hung_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_WEAPON_HUNG);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());


   msg->mutable_wpn_id()->set_id(10);
   msg->mutable_wpn_id()->set_fed_name("wpnFed");
   msg->mutable_wpn_id()->set_name("wpnName");

   msg->mutable_wpn_state()->mutable_angles()->set_x(10);
   msg->mutable_wpn_state()->mutable_angles()->set_y(11);
   msg->mutable_wpn_state()->mutable_angles()->set_z(12);
   msg->mutable_wpn_state()->mutable_pos()->set_x(20);
   msg->mutable_wpn_state()->mutable_pos()->set_y(21);
   msg->mutable_wpn_state()->mutable_pos()->set_z(22);
   msg->mutable_wpn_state()->mutable_vel()->set_x(100);
   msg->mutable_wpn_state()->mutable_vel()->set_y(101);
   msg->mutable_wpn_state()->mutable_vel()->set_z(102);

   msg->mutable_shooter_id()->set_id(20);
   msg->mutable_shooter_id()->set_fed_name("shooterFed");
   msg->mutable_shooter_id()->set_name("shooterName");

   msg->mutable_tgt_id()->set_id(50);
   msg->mutable_tgt_id()->set_fed_name("tgtFed");
   msg->mutable_tgt_id()->set_name("tgtName");


   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testWeaponDetonationEventMsg: Sets some Weapon Detonation msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testWeaponDetonationEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::WeaponDetonationEventMsg* msg = recordMsg->mutable_weapon_detonation_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_WEAPON_DETONATION);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());


   msg->set_det_type(Eaagles::Recorder::Pb::WeaponDetonationEventMsg_DetonationType_DETONATE_GROUND_IMPACT);

   // required PlayerId    wpn_id       = 1;
   msg->mutable_wpn_id()->set_id(531);
   msg->mutable_wpn_id()->set_fed_name("fed531");
   msg->mutable_wpn_id()->set_name("wpn 531");

   msg->mutable_shooter_id()->set_id(642);
   msg->mutable_shooter_id()->set_fed_name("fed642");
   msg->mutable_shooter_id()->set_name("shooter 642");

   msg->mutable_tgt_id()->set_id(23);
   msg->mutable_tgt_id()->set_fed_name("fed23");
   msg->mutable_tgt_id()->set_name("Tgt 23");


   // weapon state position:
   msg->mutable_wpn_state()->mutable_pos()->set_x(10);
   msg->mutable_wpn_state()->mutable_pos()->set_y(20);
   msg->mutable_wpn_state()->mutable_pos()->set_z(30);

   // weapon state angles:
   msg->mutable_wpn_state()->mutable_angles()->set_x(.2);
   msg->mutable_wpn_state()->mutable_angles()->set_y(.3);
   msg->mutable_wpn_state()->mutable_angles()->set_z(.4);

   // weapon state velocity:
   msg->mutable_wpn_state()->mutable_vel()->set_x(1.2);
   msg->mutable_wpn_state()->mutable_vel()->set_y(1.3);
   msg->mutable_wpn_state()->mutable_vel()->set_z(1.4);

   // missile distance:
   msg->set_miss_dist(123.4);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;
   return handle;

}

// ------------------------------------------------------------------------------------------------
// testGunFiredEventMsg: Sets some Gun Fired msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testGunFiredEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::GunFiredEventMsg* msg = recordMsg->mutable_gun_fired_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_GUN_FIRED);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   msg->mutable_shooter_id()->set_id(300);
   msg->mutable_shooter_id()->set_fed_name("shooterFed");
   msg->mutable_shooter_id()->set_name("shooterName");
   msg->set_rounds(25);


   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;

}

// ------------------------------------------------------------------------------------------------
// testNewTrackEventMsg: Sets some New Track msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testNewTrackEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::NewTrackEventMsg* msg = recordMsg->mutable_new_track_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_NEW_TRACK);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // Player Id:
   msg->mutable_player_id()->set_id(999);
   msg->mutable_player_id()->set_fed_name("fed999");
   msg->mutable_player_id()->set_name("plytrk 999");

   msg->set_track_id("track1");

   // track data
   msg->mutable_track_data()->set_altitude(1000);
   msg->mutable_track_data()->set_type(5);
   msg->mutable_track_data()->set_quality(1);
   msg->mutable_track_data()->set_true_az(.1);
   msg->mutable_track_data()->set_rel_az(.2);
   msg->mutable_track_data()->set_elevation(35);
   msg->mutable_track_data()->set_range(135);
   msg->mutable_track_data()->set_latitude(35);
   msg->mutable_track_data()->set_longitude(160);
   msg->mutable_track_data()->set_avg_signal(12);
   msg->mutable_track_data()->set_sl_index(5);
   msg->mutable_track_data()->mutable_position()->set_x(100);
   msg->mutable_track_data()->mutable_position()->set_y(200);
   msg->mutable_track_data()->mutable_position()->set_z(300);
   msg->mutable_track_data()->mutable_velocity()->set_x(1000);
   msg->mutable_track_data()->mutable_velocity()->set_y(1100);
   msg->mutable_track_data()->mutable_velocity()->set_z(1200);

   // player state player_state
   msg->mutable_player_state()->mutable_angles()->set_x(10);
   msg->mutable_player_state()->mutable_angles()->set_y(20);
   msg->mutable_player_state()->mutable_angles()->set_z(30);
   msg->mutable_player_state()->mutable_pos()->set_x(15);
   msg->mutable_player_state()->mutable_pos()->set_y(25);
   msg->mutable_player_state()->mutable_pos()->set_z(35);
   msg->mutable_player_state()->mutable_vel()->set_x(1234);
   msg->mutable_player_state()->mutable_vel()->set_y(2345);
   msg->mutable_player_state()->mutable_vel()->set_z(3456);
   msg->mutable_player_state()->set_damage(.5);

   // player state trk_player_state
   msg->mutable_trk_player_state()->mutable_angles()->set_x(10);
   msg->mutable_trk_player_state()->mutable_angles()->set_y(20);
   msg->mutable_trk_player_state()->mutable_angles()->set_z(30);
   msg->mutable_trk_player_state()->mutable_pos()->set_x(15);
   msg->mutable_trk_player_state()->mutable_pos()->set_y(25);
   msg->mutable_trk_player_state()->mutable_pos()->set_z(35);
   msg->mutable_trk_player_state()->mutable_vel()->set_x(1234);
   msg->mutable_trk_player_state()->mutable_vel()->set_y(2345);
   msg->mutable_trk_player_state()->mutable_vel()->set_z(3456);
   msg->mutable_trk_player_state()->set_damage(.5);

   // Player Id trk_player_id:
   msg->mutable_trk_player_id()->set_id(911);
   msg->mutable_trk_player_id()->set_fed_name("trkfed911");
   msg->mutable_trk_player_id()->set_name("trk 911");

   // Emission Data
   msg->mutable_emission_data()->set_azimuth_aoi(1350);
   msg->mutable_emission_data()->set_elevation_aoi(2460);
   msg->mutable_emission_data()->set_frequency(975);
   msg->mutable_emission_data()->set_wave_length(1000);
   msg->mutable_emission_data()->set_pulse_width(2000);
   msg->mutable_emission_data()->set_bandwidth(3000);
   msg->mutable_emission_data()->set_prf(4000);
   msg->mutable_emission_data()->set_power(5000);
   msg->mutable_emission_data()->set_polarization(Eaagles::Recorder::Pb::EmissionData_Polarization_NONE);

   // enum Polarization {
   //   NONE        = 0;
   //   VERTICAL    = 1;
   //   HORIZONTAL  = 2;
   //   SLANT       = 3;
   //   RHC         = 4;
   //   LHC         = 5;
   //};

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;

}

// ------------------------------------------------------------------------------------------------
// testTrackRemovedEventMsg: Sets some Track Removed msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testTrackRemovedEventMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::TrackRemovedEventMsg* msg = recordMsg->mutable_track_removed_event_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_TRACK_REMOVED);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   // Player Id:
   msg->mutable_player_id()->set_id(999);
   msg->mutable_player_id()->set_fed_name("fed999");
   msg->mutable_player_id()->set_name("plytrk 999");

   msg->set_track_id("track1");

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testTrackDataMsg: Sets some Track Data msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testTrackDataMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   Eaagles::Recorder::Pb::TrackDataMsg* msg = recordMsg->mutable_track_data_msg();
   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // required
   recordMsg->set_id(REID_TRACK_DATA);
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());


   // Player Id:
   msg->mutable_player_id()->set_id(999);
   msg->mutable_player_id()->set_fed_name("fed999");
   msg->mutable_player_id()->set_name("plytrk 999");

   msg->set_track_id("track1");

   // track data
   msg->mutable_track_data()->set_altitude(1000);
   msg->mutable_track_data()->set_type(5);
   msg->mutable_track_data()->set_quality(1);
   msg->mutable_track_data()->set_true_az(.1);
   msg->mutable_track_data()->set_rel_az(.2);
   msg->mutable_track_data()->set_elevation(35);
   msg->mutable_track_data()->set_range(135);
   msg->mutable_track_data()->set_latitude(35);
   msg->mutable_track_data()->set_longitude(160);
   msg->mutable_track_data()->set_avg_signal(12);
   msg->mutable_track_data()->set_sl_index(5);
   msg->mutable_track_data()->mutable_position()->set_x(100);
   msg->mutable_track_data()->mutable_position()->set_y(200);
   msg->mutable_track_data()->mutable_position()->set_z(300);
   msg->mutable_track_data()->mutable_velocity()->set_x(1000);
   msg->mutable_track_data()->mutable_velocity()->set_y(1100);
   msg->mutable_track_data()->mutable_velocity()->set_z(1200);

   // player state player_state
   msg->mutable_player_state()->mutable_angles()->set_x(10);
   msg->mutable_player_state()->mutable_angles()->set_y(20);
   msg->mutable_player_state()->mutable_angles()->set_z(30);
   msg->mutable_player_state()->mutable_pos()->set_x(15);
   msg->mutable_player_state()->mutable_pos()->set_y(25);
   msg->mutable_player_state()->mutable_pos()->set_z(35);
   msg->mutable_player_state()->mutable_vel()->set_x(1234);
   msg->mutable_player_state()->mutable_vel()->set_y(2345);
   msg->mutable_player_state()->mutable_vel()->set_z(3456);
   msg->mutable_player_state()->set_damage(.5);

   // player state trk_player_state
   msg->mutable_trk_player_state()->mutable_angles()->set_x(10);
   msg->mutable_trk_player_state()->mutable_angles()->set_y(20);
   msg->mutable_trk_player_state()->mutable_angles()->set_z(30);
   msg->mutable_trk_player_state()->mutable_pos()->set_x(15);
   msg->mutable_trk_player_state()->mutable_pos()->set_y(25);
   msg->mutable_trk_player_state()->mutable_pos()->set_z(35);
   msg->mutable_trk_player_state()->mutable_vel()->set_x(1234);
   msg->mutable_trk_player_state()->mutable_vel()->set_y(2345);
   msg->mutable_trk_player_state()->mutable_vel()->set_z(3456);
   msg->mutable_trk_player_state()->set_damage(.5);

   // Player Id trk_player_id:
   msg->mutable_trk_player_id()->set_id(911);
   msg->mutable_trk_player_id()->set_fed_name("trkfed911");
   msg->mutable_trk_player_id()->set_name("trk 911");

   // Emission Data
   msg->mutable_emission_data()->set_azimuth_aoi(1350);
   msg->mutable_emission_data()->set_elevation_aoi(2460);
   msg->mutable_emission_data()->set_frequency(975);
   msg->mutable_emission_data()->set_wave_length(1000);
   msg->mutable_emission_data()->set_pulse_width(2000);
   msg->mutable_emission_data()->set_bandwidth(3000);
   msg->mutable_emission_data()->set_prf(4000);
   msg->mutable_emission_data()->set_power(5000);
   msg->mutable_emission_data()->set_polarization(Eaagles::Recorder::Pb::EmissionData_Polarization_NONE);

   size_t messageSize = recordMsg->ByteSize();
   std::cout << "Message size: " << messageSize << std::endl;

   return handle;
}

// ------------------------------------------------------------------------------------------------
// testLastMsg: Sets some Last msg data and returns a handle
// ------------------------------------------------------------------------------------------------
Eaagles::Recorder::DataRecordHandle* DataRecordTest::testLastMsg()
{
   Eaagles::Recorder::Pb::DataRecord* recordMsg = new Eaagles::Recorder::Pb::DataRecord();
   recordMsg->set_id(REID_END_OF_DATA);

   Eaagles::Recorder::DataRecordHandle* handle = new Eaagles::Recorder::DataRecordHandle(recordMsg);

   // Still need "required" data:
   recordMsg->mutable_time()->set_exec_time(getExecTime());
   recordMsg->mutable_time()->set_sim_time(getSimTime());
   recordMsg->mutable_time()->set_utc_time(getUtcTime());

   return handle;

}
//------------------------------------------------------------------------------
// processMessage(): Recursive function to go through all messages
//---------------------------------------------------------------------------
bool DataRecordTest::processMessage(const google::protobuf::Message* const msg)
{

   bool hasSubMessage = false;
   const google::protobuf::Message& root = *msg;
   const google::protobuf::Descriptor* descriptor = msg->GetDescriptor();
   const google::protobuf::Reflection* reflection = msg->GetReflection();

   int fieldCount = descriptor->field_count();
   const google::protobuf::FieldDescriptor* fieldDescriptor = 0;

   // look at fields to find a match with the slot condition
   if (fieldCount > 0) {

      // Look at each field in this message
      for (int i = 0; i < fieldCount && !fieldSelected; i++) {
         // Get field descriptor (includes messages)
         fieldDescriptor = descriptor->field(i);

         // what type is this field?
         google::protobuf::FieldDescriptor::CppType cppType = fieldDescriptor->cpp_type();

         // First look at all the fields in this message, then decide whether to continue
         if (!(cppType == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)) {
            // field is not a message.
            std::cout << "Field name: " << fieldDescriptor->full_name()<< std::endl;
            std::cout << "Select This Field? Y/N ";
            std::string select;
            std::cin >> select;
            if (select == "Y" || select == "y") {
               // save full field name
               fullFieldName = fieldDescriptor->full_name();
               fieldSelected = true;
               setFieldOfInterest(fullFieldName);
               if (cppType == google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
                  std::string str;
                  std::cout << "Enter string to match: ";
                  std::cin >> str;
                  myPrintSelected->setCompareToValue(str);
                  setCompareToValue(str);
               }
               // 
               else if ((cppType == google::protobuf::FieldDescriptor::CPPTYPE_INT32) ||
                    (cppType == google::protobuf::FieldDescriptor::CPPTYPE_INT64)     ||
                    (cppType == google::protobuf::FieldDescriptor::CPPTYPE_UINT32)    ||
                    (cppType == google::protobuf::FieldDescriptor::CPPTYPE_UINT64)    ||
                    (cppType == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)) {
                   int inValue;
                   std::cout << "Enter integer to match: ";
                   std::cin >> inValue;
                   setCompareToValue(inValue);
               }
               else if (cppType == google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
                  std::cout << "Enter 0 (false) or 1 (true) to match: ";
                  int boolVal = 0;
                  std::cin >> boolVal;
                  if (boolVal == 0) setCompareToValue(0);
                  else setCompareToValue(1);
               }
               else {
                  double val;
                  std::cout << "Enter double or float value to match: ";
                  std::cin >> val;
                  setCompareToValue(val);
               }
               if ((cppType != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) &&
                  (cppType != google::protobuf::FieldDescriptor::CPPTYPE_STRING)) {

                  std::cout << "Enter compare condition: 0=EQ, 1=LT, 2=GT: "; 
                  unsigned int cond;
                  std::cin >>  cond;
                  if (cond == 1) {
                     setCompareCondition(Eaagles::Recorder::PrintSelected::LT);
                  }
                  else if (cond == 2) {
                     setCompareCondition(Eaagles::Recorder::PrintSelected::GT);
                  }
                  else {
                     setCompareCondition(Eaagles::Recorder::PrintSelected::EQ);
                  }
               }
               else setCompareCondition(Eaagles::Recorder::PrintSelected::EQ); // not needed in this case
            }
            else if (select == "Q" || select == "q") {
               fieldSelected = true;  // force exit
            }
            else {
               // probably entered N or n, keep looking
               fieldSelected = false;
            }
         }

         // If this field is a message, then it has sub-fields
         else if (!fieldSelected) {
            std::cout << "Message name: " << fieldDescriptor->full_name() << std::endl;
            // Get sub message
            const google::protobuf::Message& sub_message = reflection->GetMessage(root, fieldDescriptor);

            // If sub message exists, process it
            if (&sub_message != NULL) {
               hasSubMessage = true;
               // Do we care?
               std::cout << "Select This Message? Y/N ";
               std::string select;
               std::cin >> select;
               if (select == "Y" || select == "y") {
                  // do the message

                  // call this until no more messages
                  processMessage(&sub_message);
               }
            }
         }
      }
   }
   return hasSubMessage;
}


// Set selection data by function call:
//------------------------------------------------------------------------------
// setMsgToken(): Set Event Token of interest
//---------------------------------------------------------------------------
bool DataRecordTest::setMsgToken(const unsigned int token)
{
   selection[selectionNum].msgToken = token;
   return true;
}

//------------------------------------------------------------------------------
// setFieldOfInterest(): Set field of interest
//---------------------------------------------------------------------------
bool DataRecordTest::setFieldOfInterest(const std::string field )
{
   selection[selectionNum].fieldName = field;
   return true;
}

//------------------------------------------------------------------------------
// setCompareToValue(): Set string to compare to field
//---------------------------------------------------------------------------
bool DataRecordTest::setCompareToValue(const std::string strVal)
{
   selection[selectionNum].compareValS = strVal;
   return true;
}

//------------------------------------------------------------------------------
// setCompareToValue(): Set integer value to compare to field
//---------------------------------------------------------------------------
bool DataRecordTest::setCompareToValue(const int numVal )
{
   selection[selectionNum].compareValI = numVal;
   return true;
}

//------------------------------------------------------------------------------
// setCompareToValue(): Set double value to compare to field
//---------------------------------------------------------------------------
bool DataRecordTest::setCompareToValue(const double dblVal )
{
   selection[selectionNum].compareValD = dblVal;
   return true;
}

//------------------------------------------------------------------------------
// setCompareCondition(): Set comparison condition
//---------------------------------------------------------------------------
bool DataRecordTest::setCompareCondition(const Eaagles::Recorder::PrintSelected::Condition cc )
{
   selection[selectionNum].condition = cc;
   return true;
}

//------------------------------------------------------------------------------
// setTimeOnly(): Set time only flag
//---------------------------------------------------------------------------
bool DataRecordTest::setTimeOnly(const bool flg )
{
   selection[selectionNum].timeOnly = flg;
   return true;
}

double DataRecordTest::getSimTime()
{
   static double simTime = 1000;
   simTime += 100;
   return simTime;
}

double DataRecordTest::getExecTime()
{
   static double execTime = 2000;
   execTime += 100;
   return execTime;
}

double DataRecordTest::getUtcTime()
{
   static double utcTime = 3000;
   utcTime += 100;
   return utcTime;
}


}
}
