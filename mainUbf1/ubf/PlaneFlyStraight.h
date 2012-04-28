//
// Class: PlaneFlyStraight
//
// Base class: Basic::Component -> Ubf::Behavior -> PlaneFlyStraight
//
// Description: Behavior class that tries to keep the plane level
//

#ifndef __Eaagles_MainUbf1_PlaneFlyStraight_H__
#define __Eaagles_MainUbf1_PlaneFlyStraight_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneFlyStraight : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneFlyStraight, Ubf::Behavior)

public:

   PlaneFlyStraight();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

private:

   double holdingAltitude;

};

}
}

#endif
