
#ifndef __oe_xbehaviors_PlaneAction_H__
#define __oe_xbehaviors_PlaneAction_H__

#include "openeaagles/base/ubf/AbstractAction.hpp"

namespace oe {
namespace simulation { class Player; }
namespace xbehaviors {

//------------------------------------------------------------------------------
// Class: PlaneAction
//------------------------------------------------------------------------------
class PlaneAction : public base::ubf::AbstractAction
{
   DECLARE_SUBCLASS(PlaneAction, base::ubf::AbstractAction)

public:
   PlaneAction();

   virtual bool execute(base::Component* actor) override;

   // get/set methods
   void setPitch(const double);
   double getPitch() const             { return pitch;              }
   bool isPitchChanged() const         { return pitchChanged;       }

   void setRoll(const double);
   double getRoll() const              { return roll;               }
   bool isRollChanged() const          { return rollChanged;        }

   void setHeading(const double);
   double getHeading() const           { return heading;            }
   bool isHeadingChanged() const       { return headingChanged;     }

   void setYaw(const double);
   double getYaw() const               { return yaw;                }
   bool isYawChanged() const           { return yawChanged;         }

   void setThrottle(const double);
   double getThrottle() const          { return throttle;           }
   bool isThrottleChanged() const      { return throttleChanged;    }

   void setSpeed(const double);
   double getSpeed() const             { return speed;              }
   bool isSpeedChanged() const         { return speedChanged;       }

   void setFireMissile(const bool);
   bool getFireMissile() const         { return fireMissile;        }
   bool isFireMissileChanged() const   { return fireMissileChanged; }

   void setPitchTrim(const double);
   double getPitchTrim() const         { return pitchTrim;          }
   bool isPitchTrimChanged() const     { return pitchTrimChanged;   }

private:

   double pitch {};
   bool pitchChanged {};

   double roll {};
   bool rollChanged {};

   double heading {};
   bool headingChanged {};

   double yaw {};
   bool yawChanged {};

   double throttle {};
   bool throttleChanged {};

   double speed {};
   bool speedChanged {};

   double pitchTrim {};
   bool pitchTrimChanged {};

   bool fireMissile {};
   bool fireMissileChanged {};
};

}
}

#endif
