//------------------------------------------------------------------------------
// Class: PrintMyData
//------------------------------------------------------------------------------
#ifndef __oe_test_PrintMyData_H__
#define __oe_test_PrintMyData_H__

#include "openeaagles/recorder/PrintHandler.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class: PrintMyData
// Description: Print my extended recorder data
//
// Factory name: PrintMyData
//------------------------------------------------------------------------------
class PrintMyData : public recorder::PrintHandler
{
   DECLARE_SUBCLASS(PrintMyData, recorder::PrintHandler)

public:
   PrintMyData();

protected:
   virtual void processRecordImp(const recorder::DataRecordHandle* const handle) override;

private:
   void initData();
};

}
}

#endif
