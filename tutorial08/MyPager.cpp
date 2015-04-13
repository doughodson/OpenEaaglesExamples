//------------------------------------------------------------------------------
// MyPager
//------------------------------------------------------------------------------
#include "MyPager.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MyPager,"MyPager")
EMPTY_COPYDATA(MyPager)
EMPTY_DELETEDATA(MyPager)
EMPTY_SERIALIZER(MyPager)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MyPager::MyPager()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// onEntry() -- default ON_ENTRY handler
//------------------------------------------------------------------------------
bool MyPager::onEntry()
{
   Basic::PairStream* components = getComponents();
   if (components != 0) {
      Basic::List::Item* item = components->getFirstItem();
      while (item != 0) {
         Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
         Basic::Component* cp = static_cast<Basic::Component*>(pair->object());
         if (cp != 0)
            cp->event(RESET_EVENT);
         item = item->getNext();
      }
   }
   return true;
}

} // namespace Tutorial
} // namespace Eaagles
