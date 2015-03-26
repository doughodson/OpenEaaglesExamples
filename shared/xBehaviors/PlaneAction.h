//------------------------------------------------------------------------------
// Class: PlaneAction
//------------------------------------------------------------------------------

#ifndef __Eaagles_xBehaviors_PlaneAction_H__
#define __Eaagles_xBehaviors_PlaneAction_H__

#include "openeaagles/basic/ubf/Action.h"

namespace Eaagles {

namespace Simulation { class Player; }

namespace xBehaviors {

//------------------------------------------------------------------------------
// Class: PlaneAction
//------------------------------------------------------------------------------
class PlaneAction : public Basic::Ubf::Action
{
   DECLARE_SUBCLASS(PlaneAction, Basic::Ubf::Action)

public:
   PlaneAction();

   bool execute(Basic::Component* actor) override;

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
   bool getFireMissile() const          { return fireMissile;       }
   bool isFireMissileChanged() const   { return fireMissileChanged; }

   void setPitchTrim(const double);
   double getPitchTrim() const         { return pitchTrim;          }
   bool isPitchTrimChanged() const     { return pitchTrimChanged;   }

private:

   double pitch;
   bool pitchChanged;

   double roll;
   bool rollChanged;

   double heading;
   bool headingChanged;

   double yaw;
   bool yawChanged;

   double throttle;
   bool throttleChanged;

   double speed;
   bool speedChanged;

   double pitchTrim;
   bool pitchTrimChanged;

   bool fireMissile;
   bool fireMissileChanged;

};

}
}

#endif

