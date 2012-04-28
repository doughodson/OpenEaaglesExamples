//
// Class: PriorityArbiter
//
// Base class: Basic::Component -> Ubf::Behavior -> Ubf::Arbiter -> PriorityArbiter
//
// Description: Example fusion arbiter for a plane
//

#ifndef __Eaagles_MainUbf1_PriorityArbiter_H__
#define __Eaagles_MainUbf1_PriorityArbiter_H__

#include "openeaagles/ubf/Arbiter.h"

namespace Eaagles {

namespace Basic { class List; }

namespace Ubf { class Action; }

namespace MainUbf1 {

class PriorityArbiter : public Ubf::Arbiter
{
   DECLARE_SUBCLASS(PriorityArbiter, Ubf::Arbiter)

public:

   PriorityArbiter();

   // generates an action based upon the recommended actions in the actionSet
   virtual Ubf::Action* genComplexAction(const Basic::List* const actionSet);

private:

   // Trim change might not be valid if the plane is in the middle of a maneuver
   // and the change would go against the intended control stick action.  If so,
   // invalidate the trim change.
   // Returns nothing, but modifies what the action object points to
   void trimChangeValidation(Ubf::Action* const);

};

}
}

#endif

