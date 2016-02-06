//------------------------------------------------------------------------------
// Class: PriorityArbiter
//------------------------------------------------------------------------------
#ifndef __oe_xBehaviors_PriorityArbiter_H__
#define __oe_xBehaviors_PriorityArbiter_H__

#include "openeaagles/basic/ubf/Arbiter.h"

namespace oe {

namespace basic { class List; class Action; }

namespace xBehaviors {

//------------------------------------------------------------------------------
// Class: PriorityArbiter
//
// Description: Example fusion arbiter for a plane
//------------------------------------------------------------------------------
class PriorityArbiter : public basic::ubf::Arbiter
{
   DECLARE_SUBCLASS(PriorityArbiter, basic::ubf::Arbiter)

public:
   PriorityArbiter();

   basic::ubf::Action* genComplexAction(basic::List* const actionSet) override;

private:

   // Trim change might not be valid if the plane is in the middle of a maneuver
   // and the change would go against the intended control stick action.  If so,
   // invalidate the trim change.
   // Returns nothing, but modifies what the action object points to
   void trimChangeValidation(basic::ubf::Action* const);
};

}
}

#endif

