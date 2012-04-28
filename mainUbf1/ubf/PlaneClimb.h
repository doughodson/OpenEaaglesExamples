//
// Class: PlaneClimb
//
// Base class: Basic::Component -> Ubf::Behavior -> PlaneClimb
//
// Description: Behavior class that climbs
//

#ifndef __Eaagles_MainUbf1_PlaneClimb_H__
#define __Eaagles_MainUbf1_PlaneClimb_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneClimb : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneClimb, Ubf::Behavior)

public:

   PlaneClimb();

   // Generates the PlaneClimb Behavior and returns an action
   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

};

}
}

#endif
