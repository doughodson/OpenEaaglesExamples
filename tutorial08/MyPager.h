//------------------------------------------------------------------------------
// Class: MyPager
// Description: Example pager
//------------------------------------------------------------------------------
#ifndef __Eaagles_Tutorial_MyPager_H__
#define __Eaagles_Tutorial_MyPager_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Tutorial {

class MyPager : public BasicGL::Page
{
   DECLARE_SUBCLASS(MyPager, BasicGL::Page)

public:

   MyPager();

   bool onEntry() override;
};

} // namespace Tutorial
} // namespace Eaagles

#endif
