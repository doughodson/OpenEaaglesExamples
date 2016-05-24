//------------------------------------------------------------------------------
// MyPager
//------------------------------------------------------------------------------
#include "MyPager.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"

namespace oe {
namespace tutorial {

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
   base::PairStream* components = getComponents();
   if (components != nullptr) {
      base::List::Item* item = components->getFirstItem();
      while (item != nullptr) {
         base::Pair* pair = static_cast<base::Pair*>(item->getValue());
         base::Component* cp = static_cast<base::Component*>(pair->object());
         if (cp != nullptr)
            cp->event(RESET_EVENT);
         item = item->getNext();
      }
   }
   return true;
}

}
}
