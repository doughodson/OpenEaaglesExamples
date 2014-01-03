//------------------------------------------------------------------------------
// Class: MfdPage
//
// Description: Example MFD page
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_MfdPage_H__
#define __Eaagles_Example_MfdPage_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Example {

class MfdPage : public BasicGL::Page {
   DECLARE_SUBCLASS(MfdPage,BasicGL::Page)

public:
   MfdPage();
   
   virtual bool onEntry();
   
   virtual bool event(const int event, Basic::Object* const obj = 0);
   virtual void updateData(const LCreal dt = 0);

private:
    LCreal rotate;
    LCreal rotateRate;
    SendData rSD;
};

} // End Example namespace
} // End Eaagles namespace

#endif
