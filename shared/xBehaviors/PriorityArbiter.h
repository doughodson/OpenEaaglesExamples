//------------------------------------------------------------------------------
// Class: PriorityArbiter
//------------------------------------------------------------------------------
#ifndef __oe_xBehaviors_PriorityArbiter_H__
#define __oe_xBehaviors_PriorityArbiter_H__

#include "openeaagles/basic/ubf/Arbiter.h"

namespace oe {

namespace Basic { class List; class Action; }

namespace xBehaviors {

//------------------------------------------------------------------------------
// Class: PriorityArbiter
//
// Description: Example fusion arbiter for a plane
//------------------------------------------------------------------------------
class PriorityArbiter : public Basic::Ubf::Arbiter
{
   DECLARE_SUBCLASS(PriorityArbiter, Basic::Ubf::Arbiter)

public:
   PriorityArbiter();

   Basic::Ubf::Action* genComplexAction(Basic::List* const actionSet) override;

private:

   // Trim change might not be valid if the plane is in the middle of a maneuver
   // and the change would go against the intended control stick action.  If so,
   // invalidate the trim change.
   // Returns nothing, but modifies what the action object points to
   void trimChangeValidation(Basic::Ubf::Action* const);
};

}
}

#endif

