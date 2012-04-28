//
// Class: PlaneBarrelRoll
//
// Base class: Basic::Component -> Ubf::Behavior -> PlaneBarrelRoll
//

#ifndef __Eaagles_MainUbf1_PlaneBarrelRoll_H__
#define __Eaagles_MainUbf1_PlaneBarrelRoll_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneBarrelRoll : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneBarrelRoll, Ubf::Behavior)

public:

   PlaneBarrelRoll();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

};

}
}

#endif

