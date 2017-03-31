
#ifndef __MapDisplay_H__
#define __MapDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

namespace oe {
namespace models { class Aircraft; }
namespace simulation { class Station; }
}

// -------------------------------------------------------------------------------
// Class: MapDisplay
//
// Description:
//      Derived MapDisplay that will simply make our map page move.
// -------------------------------------------------------------------------------
class MapDisplay : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(MapDisplay, oe::glut::GlutDisplay)

public:
   MapDisplay();

   virtual void mouseMotionEvent(const int x, const int y) override;
   virtual void mouseEvent(const int button, const int state, const int x, const int y) override;
   virtual void passiveMotionEvent(const int x, const int y) override;
   virtual void buttonEvent(const int b) override;

   virtual void updateData(const double dt = 0.0) override;

private:
   oe::models::Aircraft* getOwnship();
   oe::simulation::Station* getStation();

   // button hit enumerations
   enum class Btn {
      DEC_RANGE = 101,           // Increase / decrease the map range (NM)
      INC_RANGE,
      DEC_CMD_AS,                // Increase / decrease the commanded airspeed (Kts - only works with no autopilot mode engaged)
      INC_CMD_AS,
      DEC_CMD_ALT,               // Increase / decrease the commanded altitude (Ft - only works with no autopilot mode engaged)
      INC_CMD_ALT,
      DEC_CMD_HDG,               // Increase / decrease the commanded heading (Degs - only works with no autopilot mode engaged)
      INC_CMD_HDG,
      PASSIVE_ENABLE,
      PASSIVE_DISABLE,
      INC_CMD_AS_NPS,            // Increase / decrease our rate of acceleration
      DEC_CMD_AS_NPS,
      INC_CMD_ALT_MPS,           // Increase / decrease our rate of climb / dive
      DEC_CMD_ALT_MPS,
      INC_CMD_HDG_ROT,           // Increase / decrease our rate of change of the bank angle
      DEC_CMD_HDG_ROT,
      INC_CMD_HDG_BNK,           // Increase / decrease our maximum bank angle during turns
      DEC_CMD_HDG_BNK,
      CHANGE_AP_MODE             // Change the autopilot mode (Nav/Loiter/FollowTheLead or None)
   };

   oe::base::safe_ptr<oe::simulation::Station> myStation;

   int startX {};         // startX of our last mouse position
   int startY {};         // startY of our last mouse position
   bool dragging {};      // are we dragging the map?

   SendData cmdRangeSD;
   SendData cmdAirspeedSD;
   SendData cmdAltitudeSD;
   SendData cmdHeadingSD;

   // Button visibility for buttons that require no autopilot mode - commanded alt, heading, and airspeed
   SendData apReqButtonVisSD;
   // readout of the mode the autopilot is in
   SendData apModeSD;

   // pilot limits
   SendData maxAccelSD;
   SendData maxClimbSD;
   SendData maxBankSD;
   SendData maxTurnSD;

   bool passiveEnable {};
};

#endif
