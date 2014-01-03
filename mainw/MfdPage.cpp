
#include "MfdPage.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basicGL/Rotators.h"
#include "openeaagles/basic/PairStream.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MfdPage,"MfdPage")
EMPTY_SERIALIZER(MfdPage)

EMPTY_COPYDATA(MfdPage)
EMPTY_DELETEDATA(MfdPage)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MfdPage::MfdPage()
{
   STANDARD_CONSTRUCTOR()
   rotate = 0;
   rotateRate = 5;
   rSD.empty();
}

//------------------------------------------------------------------------------
// Macro event handler for MfdPage
//------------------------------------------------------------------------------
BEGIN_EVENT_HANDLER(MfdPage)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// onEntry() -- default ON_ENTRY handler
//------------------------------------------------------------------------------
bool MfdPage::onEntry()
{
   Basic::PairStream* subcomponents = getComponents();
    if(subcomponents != 0) {
        Basic::List::Item* item = subcomponents->getFirstItem();
        while (item != 0) {
            Basic::Pair* pair = (Basic::Pair*) item->getValue();
            Basic::Component* cp = (Basic::Component*) pair->object();
            if (cp != 0) cp->event(RESET_EVENT);
            item = item->getNext();
        }
        subcomponents->unref();
        subcomponents = 0;
    }
    return true;
}

void MfdPage::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    rotate += (rotateRate * dt);
    if (rotate > 360) {
        rotate = 360;
        rotateRate = -rotateRate;
    }
    if (rotate < -360) {
        rotate = -360;
        rotateRate = -rotateRate;
    }
    
    send("rotator", UPDATE_VALUE2, rotate, rSD);    
}

} // End Example namespace
} // End Eaagles namespace
