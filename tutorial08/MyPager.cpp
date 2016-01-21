//------------------------------------------------------------------------------
// MyPager
//------------------------------------------------------------------------------
#include "MyPager.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"

namespace oe {
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
   if (components != nullptr) {
      Basic::List::Item* item = components->getFirstItem();
      while (item != nullptr) {
         Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
         Basic::Component* cp = static_cast<Basic::Component*>(pair->object());
         if (cp != nullptr)
            cp->event(RESET_EVENT);
         item = item->getNext();
      }
   }
   return true;
}

} // namespace Tutorial
} // namespace oe
