//------------------------------------------------------------------------------
// Class:	MfdPage
// Base class:	Object > BasicGL::Graphic > Page -> MfdPage
//
// Description:	Example MFD page
//
//------------------------------------------------------------------------------
#ifndef	__MfdPage_H__
#define __MfdPage_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace MainW {

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

} // End MainW namespace
} // End Eaagles namespace

#endif	/* __MfdPage_H__ */
