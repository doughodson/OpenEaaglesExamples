//
// Class: PlaneLoop
//

#ifndef __Eaagles_MainUbf1_PlaneLoop_H__
#define __Eaagles_MainUbf1_PlaneLoop_H__

#include "openeaagles/ubf/Behavior.h"

namespace Eaagles {

namespace Ubf { class UbfState; class UbfAction; class PlaneAction; }

namespace MainUbf1 {

class PlaneLoop : public Ubf::Behavior
{
   DECLARE_SUBCLASS(PlaneLoop, Ubf::Behavior)

public:

   PlaneLoop();

   Ubf::Action* genAction(const Ubf::State* const state, const LCreal dt);

private:

	bool keepGoing;

};

}
}

#endif
