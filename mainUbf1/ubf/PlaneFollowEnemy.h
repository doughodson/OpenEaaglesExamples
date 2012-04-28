//
// Class: PlaneFollowEnemy
//
// Description: Behavior class that flies towards the closest track
//

#ifndef __Eaagles_MainUbf1_PlaneFollowEnemy_H__
#define __Eaagles_MainUbf1_PlaneFollowEnemy_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class State; }

namespace MainUbf1 {

class PlaneFollowEnemy : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneFollowEnemy, Ubf::Behavior)

public:

   PlaneFollowEnemy();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

};

}
}

#endif
