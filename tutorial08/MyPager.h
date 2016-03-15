//------------------------------------------------------------------------------
// Class: MyPager
// Description: Example pager
//------------------------------------------------------------------------------
#ifndef __oe_tutorial_MyPager_H__
#define __oe_tutorial_MyPager_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace tutorial {

class MyPager : public graphics::Page
{
   DECLARE_SUBCLASS(MyPager, graphics::Page)

public:

   MyPager();

   bool onEntry() override;
};

} // namespace tutorial
} // namespace oe

#endif
