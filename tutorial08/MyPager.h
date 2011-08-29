//------------------------------------------------------------------------------
// Class:	MyPager
// Base class:	Object -> Graphic -> Page -> MyPager
// Description:	Example pager
//------------------------------------------------------------------------------
#ifndef _MYPAGER_INCLUDE
#define _MYPAGER_INCLUDE

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Example08 {

class MyPager : public BasicGL::Page {

  DECLARE_SUBCLASS(MyPager,Page)

public:
  MyPager();

  // Page Interface
  virtual bool onEntry();
};

} // namespace Example08
} // namespace Eaagles

#endif
