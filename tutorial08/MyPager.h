//------------------------------------------------------------------------------
// Class: MyPager
// Description: Example pager
//------------------------------------------------------------------------------
#ifndef __MyPager_H__
#define __MyPager_H__

#include "openeaagles/graphics/Page.h"

class MyPager : public oe::graphics::Page
{
   DECLARE_SUBCLASS(MyPager, oe::graphics::Page)

public:

   MyPager();

   virtual bool onEntry() override;
};

#endif
