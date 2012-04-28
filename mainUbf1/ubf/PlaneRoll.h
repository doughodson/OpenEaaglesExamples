//
// Class: PlaneRoll
//
// Description: Behavior class that rolls clockwise
//

#ifndef __Eaagles_MainUbf1_PlaneRoll_H__
#define __Eaagles_MainUbf1_PlaneRoll_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class Action; class State; }

namespace MainUbf1 {

class PlaneRoll : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneRoll, Ubf::Behavior)

public:

   PlaneRoll();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

};

}
}

#endif
