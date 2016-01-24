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
   basic::PairStream* components = getComponents();
   if (components != nullptr) {
      basic::List::Item* item = components->getFirstItem();
      while (item != nullptr) {
         basic::Pair* pair = static_cast<basic::Pair*>(item->getValue());
         basic::Component* cp = static_cast<basic::Component*>(pair->object());
         if (cp != nullptr)
            cp->event(RESET_EVENT);
         item = item->getNext();
      }
   }
   return true;
}

} // namespace Tutorial
} // namespace oe
