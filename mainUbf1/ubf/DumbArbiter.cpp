//
// DumbArbiter
//

#include "DumbArbiter.h"

#include "openeaagles/basic/List.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Number.h"

#include "openeaagles/ubf/State.h"
#include "openeaagles/ubf/Action.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(DumbArbiter, "DumbArbiter")
EMPTY_COPYDATA(DumbArbiter)
EMPTY_SERIALIZER(DumbArbiter)
EMPTY_DELETEDATA(DumbArbiter)

// slot table for this class type
BEGIN_SLOTTABLE(DumbArbiter)
   "select"                    // 1) selected behavior
END_SLOTTABLE(DumbArbiter)

// map of slots to handles
BEGIN_SLOT_MAP(DumbArbiter)
   ON_SLOT(1, setSlotSelected, Basic::Number)
END_SLOT_MAP()

DumbArbiter::DumbArbiter()
{
   STANDARD_CONSTRUCTOR()

   select = 1;
}

Ubf::Action* DumbArbiter::genComplexAction(const Basic::List* const actionSet)
{
   // make sure selected action is reasonable
   if ( (select<1) || (actionSet->entries()<select) )
      select = 1;

   Ubf::Action* complexAction = (Ubf::Action*)actionSet->getPosition(select);
   complexAction->ref();

   return complexAction;
}

//---------------------------------------
// set slot methods
//---------------------------------------

bool DumbArbiter::setSlotSelected(Basic::Number* const x)
{
   bool ok = false;

   if (x!=0) {
      select = x->getInt();
      ok = true;
   }

   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* DumbArbiter::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

}
}

