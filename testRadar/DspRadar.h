
#ifndef __DspRadar_H__
#define __DspRadar_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
   namespace base      { class PairStream; }
   namespace simulation { class Radar; }
}

//------------------------------------------------------------------------------
// Class: DspRadar
// Description: Simple Realbeam B-Scan RADAR.  Displays the real-beam signal,
//              with color coded doppler shift, and overlayed with tracks.
// Factory name: DspRadar
//------------------------------------------------------------------------------
class DspRadar : public oe::graphics::Graphic
{
   DECLARE_SUBCLASS(DspRadar, oe::graphics::Graphic)

public:
   DspRadar();

   const oe::simulation::Radar* getRadar()         { return radar; }
   const oe::simulation::Radar* getRadar() const   { return radar; }
   bool setRadar(oe::simulation::Radar* const s)   { radar = s; return true; }

   virtual void drawFunc() override;

   virtual void updateData(const double dt = 0.0) override;

private:
    const oe::simulation::Radar* radar;     // The test RADAR sensor
    SendData azSD;
    SendData elSD;

    // Tracks
    enum { MAX_TRKS = 50 };
    unsigned int nTracks;              // Number of tracks
    int ntsTrk;                        // Index of the 'next-to-shoot' track
    double trkRng[MAX_TRKS];           // Track's range                    (meters)
    double trkAz[MAX_TRKS];            // Track's relative azimuth
    double trkVel[MAX_TRKS];           // Track's velocity                 (m/s)
    double trkRelGndTrk[MAX_TRKS];     // Track's relative ground track (to nearest 45 deg)
};

#endif
