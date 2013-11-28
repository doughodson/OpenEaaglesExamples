//------------------------------------------------------------------------------
// Class: PrintMyData
//------------------------------------------------------------------------------
#ifndef __TestRecorder_PrintMyData_H__
#define __TestRecorder_PrintMyData_H__

#include "openeaagles/recorder/PrintHandler.h"

namespace TestRecorder {

//------------------------------------------------------------------------------
// Class: PrintMyData
// Description: Print my extended recorder data
//
// Form name: PrintMyData
//------------------------------------------------------------------------------
class PrintMyData : public Eaagles::Recorder::PrintHandler
{
    DECLARE_SUBCLASS(PrintMyData, Eaagles::Recorder::PrintHandler)

public:
   PrintMyData();

protected:
   // OutputHandler class private functions
   virtual void processRecordImp(const Eaagles::Recorder::DataRecordHandle* const handle);

private:
   void initData();
};

} // End TestRecorder namespace

#endif

