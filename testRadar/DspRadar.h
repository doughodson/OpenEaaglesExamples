//------------------------------------------------------------------------------
// Class: DspRadar
//------------------------------------------------------------------------------
#ifndef __oe_test_DspRadar_H__
#define __oe_test_DspRadar_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
   namespace base      { class PairStream; }
   namespace simulation { class Radar; }

namespace test {

//------------------------------------------------------------------------------
// Class: DspRadar
// Description: Simple Realbeam B-Scan RADAR.  Displays the real-beam signal,
//              with color coded doppler shift, and overlayed with tracks.
// Factory name: DspRadar
//------------------------------------------------------------------------------
class DspRadar : public graphics::Graphic
{
   DECLARE_SUBCLASS(DspRadar, graphics::Graphic)

public:
   DspRadar();

   const simulation::Radar* getRadar()         { return radar; }
   const simulation::Radar* getRadar() const   { return radar; }
   bool setRadar(simulation::Radar* const s)   { radar = s; return true; }

   void drawFunc() override;

   void updateData(const double dt = 0.0) override;

private:
    const simulation::Radar* radar;     // The test RADAR sensor
    SendData    azSD;
    SendData    elSD;

    // Tracks
    enum { MAX_TRKS = 50 };
    unsigned int nTracks;                   // Number of tracks
    int ntsTrk;                             // Index of the 'next-to-shoot' track
    double      trkRng[MAX_TRKS];           // Track's range                    (meters)
    double      trkAz[MAX_TRKS];            // Track's relative azimuth
    double      trkVel[MAX_TRKS];           // Track's velocity                 (m/s)
    double      trkRelGndTrk[MAX_TRKS];     // Track's relative ground track (to nearest 45 deg)
};

} // End test namespace
} // End oe namespace

#endif
