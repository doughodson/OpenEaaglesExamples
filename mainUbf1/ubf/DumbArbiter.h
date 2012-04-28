//
// Class: DumbArbiter
//
// Base class: Basic::Component -> Ubf::Behavior -> Ubf::Arbiter -> DumbArbiter
//
// Description: Really dumb, selects action specified in input file
//

#ifndef __Eaagles_MainUbf1_DumbArbiter_H__
#define __Eaagles_MainUbf1_DumbArbiter_H__

#include "openeaagles/ubf/Arbiter.h"

namespace Eaagles {

namespace Basic { class List; class Number; }
namespace Ubf { class Action; }

namespace MainUbf1 {

class DumbArbiter : public Ubf::Arbiter
{
   DECLARE_SUBCLASS(DumbArbiter, Ubf::Arbiter)

public:

   DumbArbiter();

   // generates an action
   virtual Ubf::Action* genComplexAction(const Basic::List* const actionSet);

   // slot functions
   virtual bool setSlotSelected(Basic::Number* const);

private:

   unsigned int select;

};

}
}

#endif

