//
// Class: PlaneTrim
//
// Base class: Basic::Component -> Ubf::Behavior -> PlaneTrim
//
// Description: Behavior class that tries to keep the plane level
//              while reaching max speed without afterburner
//

#ifndef __Eaagles_MainUbf1_PlaneTrim_H__
#define __Eaagles_MainUbf1_PlaneTrim_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneTrim : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneTrim, Ubf::Behavior)

public:

   PlaneTrim();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

private:

   double holdingAltitude;
   int count;
};

}
}

#endif

