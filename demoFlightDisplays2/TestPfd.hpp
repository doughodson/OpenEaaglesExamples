
#ifndef __TestPfd_H__
#define __TestPfd_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestPfd
//
// Description: Tests another pfd page
//------------------------------------------------------------------------------
class TestPfd : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestPfd, oe::graphics::Page )

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
   double cmdHdg {};          // commanded heading (heading bug) (degs)
   double cmdHdgRate {3.0};   // degs/sec

   // airspeed
   double airSpd {};
   double airSpdRate {5.0};

   // altitude
   double alt {10000.0};
   double altRate {80.0};

   // side slip
   double slip {};            // degs
   double slipRate {10.0};    // degs/sec

   // glide slope (in dots)
   double gSlope {};
   double gSlopeRate {0.2};

   // Lateral dev
   double latDev {};
   double ldRate {0.3};

   // commanded speed
   double cmdSpd {200.0};

   // commanded alt
   double cmdAlt {6000.0};

   // vvi
   double vvi {};
   double vviRate {500.0};

   // flight director stuff (in inches)
   double fDirBank {};
   double fDirBankRate {4.0};
   double fDirPitch {};
   double fDirPitchRate {7.0};

   // barometric pressure
   double baro {};
   double baroRate {10.0};
};

#endif
