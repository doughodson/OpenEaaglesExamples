//------------------------------------------------------------------------------
// Class: PrintMyData
//------------------------------------------------------------------------------
#ifndef __oe_Test_PrintMyData_H__
#define __oe_Test_PrintMyData_H__

#include "openeaagles/recorder/PrintHandler.h"

namespace oe {
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
   void processRecordImp(const Recorder::DataRecordHandle* const handle) override;

private:
   void initData();
};

}
}

#endif
