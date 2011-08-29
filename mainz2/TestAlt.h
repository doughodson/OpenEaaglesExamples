//------------------------------------------------------------------------------
// Class:	TestAlt
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestAlt
//
// Description:	Tests our altitude tape instrument
//------------------------------------------------------------------------------
#ifndef	__TestAlt_H__2D283360_1400_4d58_BD89_87FBE87BC155
#define __TestAlt_H__2D283360_1400_4d58_BD89_87FBE87BC155

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz2 {

class TestAlt : public BasicGL::Page {
   DECLARE_SUBCLASS(TestAlt,BasicGL::Page)

public:
    TestAlt();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal alt;             // our heading 
    SendData altSD;
    LCreal  altRate;        // rate which are going (up or down)
    SendData altROSD;
};

} // end of Mainz2 namespace
} // end of Eaagles namespace

#endif	/* __TestAlt_H__2D283360_1400_4d58_BD89_87FBE87BC155 */

