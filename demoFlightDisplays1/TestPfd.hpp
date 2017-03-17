
#ifndef __TestPfd_H__
#define __TestPfd_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestPfd
//
// Description: Basic Pfd test page, stimulates the Pfd
//------------------------------------------------------------------------------
class TestPfd : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestPfd, oe::graphics::Page)

public:
   TestPfd();

   virtual void updateData(const double dt = 0.0) override;

private:
   // pitch and roll
   double pitch {};           // degs
   double pitchRate {10.0};   // degs/sec
   double roll {};            // degs
   double rollRate {-9.0};    // degs/sec

   // heading and nav stuff
   double trueHdg {};         // degs
   double tHdgRate {11.0};    // degs/sec

   double cmdCrs {};          // degs -- commanded course
   double cmdCrsRate {2.0};   // degs/sec

   double cmdHdg {};          // degs -- commanded heading (heading bug)
   double cmdHdgRate {3.0};   // degs/sec

   // cdi
   double cdiDots {};         // dots
   double cdiRate {0.15};     // dots/sec

   // to from
   double toFrom {-1.0};

   // airspeed
   double airSpd {};
   double airSpdRate {5.0};

   // altitude
   double alt {};
   double altRate {300.0};

   // side slip
   double slip {};            // degs
   double slipRate {10.0};    // degs/sec

   // glideslope (in dots)
   double gSlope {};
   double gSlopeRate {0.2};

   // Lateral dev
   double latDev {};
   double ldRate {0.3};

   // commanded speed
   double cmdSpd {150.0};

   // commanded alt
   double cmdAlt {5000.0};

   // master caution
   bool mstrCtn {};

   // vvi
   double vvi {};
   double vviRate {500.0};
   double maxVvi {3.0};      // max vvi value
   double minVvi {3.0};      // min vvi value

   // aoa
   double aoa {};
   double aoaRate {-1.0};

   // ground speed
   double gSpd {};
   double gSpdRate {1.5};

   // flight director (command bar, in inches)
   double fDirBank {};
   double fDirBankRate {10.0};
   double fDirPitch {};
   double fDirPitchRate {5.0};

   // barometric pressure
   double baro {};
   double baroRate {0.5};

   // radar altitude
   double rAlt {};
   double rAltRate {50.0};
   double rAltMin {500.0};

   // navaid bearings
   double nav1Brg {};           // degs
   double nav1BrgRate {4.0};    // degs/sec
   double nav2Brg {};           // degs
   double nav2BrgRate {10.0};   // degs/sec

   // Flight path marker
   double fpmX {};
   double fpmXRate {0.05};
   double fpmY {};
   double fpmYRate {0.05};

   // Send datas
   SendData sixtyVisSD;    // sixty degree bank marker visibility
   SendData ninetyVisSD;   // ninety  "        "       "       "
};

#endif
