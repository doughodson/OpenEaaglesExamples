//
// Class: PlaneAgent
//
// Base class: Basic::Component -> Ubf::Agent -> PlaneAgent
//
// Description: This is a 'controller'
//

#ifndef __Eaagles_MainUbf1_PlaneAgent_H__
#define __Eaagles_MainUbf1_PlaneAgent_H__

#include "openeaagles/ubf/Agent.h"

namespace Eaagles {
namespace MainUbf1 {

namespace Simulation { class Player; }

class PlaneAgent : public Ubf::Agent
{
   DECLARE_SUBCLASS(PlaneAgent, Ubf::Agent)

public:

   PlaneAgent();

protected:

   // executes action
   virtual void executeAction(const Ubf::Action* const action);

private:

   bool setup;

};

}
}

#endif

