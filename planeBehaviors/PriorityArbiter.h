//------------------------------------------------------------------------------
// Class: PriorityArbiter
//------------------------------------------------------------------------------

#ifndef __Eaagles_PlaneBehaviors_PriorityArbiter_H__
#define __Eaagles_PlaneBehaviors_PriorityArbiter_H__

#include "openeaagles/basic/ubf/Arbiter.h"

namespace Eaagles {

namespace Basic { class List; class Action; }

namespace PlaneBehaviors {

//
// Class: PriorityArbiter
//
// Description: Example fusion arbiter for a plane
//
class PriorityArbiter : public Basic::Arbiter
{
   DECLARE_SUBCLASS(PriorityArbiter, Basic::Arbiter)

public:
   PriorityArbiter();

   // generates an action based upon the recommended actions in the actionSet
   virtual Basic::Action* genComplexAction(const Basic::List* const actionSet);

private:

   // Trim change might not be valid if the plane is in the middle of a maneuver
   // and the change would go against the intended control stick action.  If so,
   // invalidate the trim change.
   // Returns nothing, but modifies what the action object points to
   void trimChangeValidation(Basic::Action* const);
};

}
}

#endif
