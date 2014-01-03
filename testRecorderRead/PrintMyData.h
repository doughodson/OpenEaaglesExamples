//------------------------------------------------------------------------------
// Class: PrintMyData
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_PrintMyData_H__
#define __Eaagles_Test_PrintMyData_H__

#include "openeaagles/recorder/PrintHandler.h"

namespace Eaagles {
namespace Test {

//------------------------------------------------------------------------------
// Class: PrintMyData
// Description: Print my extended recorder data
//
// Factory name: PrintMyData
//------------------------------------------------------------------------------
class PrintMyData : public Recorder::PrintHandler
{
    DECLARE_SUBCLASS(PrintMyData, Recorder::PrintHandler)

public:
   PrintMyData();

protected:
   // OutputHandler class private functions
   virtual void processRecordImp(const Recorder::DataRecordHandle* const handle);

private:
   void initData();
};

}
}

#endif
