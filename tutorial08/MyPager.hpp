
#ifndef __MyPager_H__
#define __MyPager_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: MyPager
// Description: Example pager
//------------------------------------------------------------------------------
class MyPager : public oe::graphics::Page
{
   DECLARE_SUBCLASS(MyPager, oe::graphics::Page)

public:
   MyPager();

   virtual bool onEntry() override;
};

#endif
