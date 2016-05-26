
#include "MyPager.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MyPager, "MyPager")
EMPTY_COPYDATA(MyPager)
EMPTY_DELETEDATA(MyPager)
EMPTY_SERIALIZER(MyPager)

MyPager::MyPager()
{
   STANDARD_CONSTRUCTOR()
}

bool MyPager::onEntry()
{
   oe::base::PairStream* components = getComponents();
   if (components != nullptr) {
      oe::base::List::Item* item = components->getFirstItem();
      while (item != nullptr) {
         oe::base::Pair* pair = static_cast<oe::base::Pair*>(item->getValue());
         oe::base::Component* cp = static_cast<oe::base::Component*>(pair->object());
         if (cp != nullptr)
            cp->event(RESET_EVENT);
         item = item->getNext();
      }
   }
   return true;
}
