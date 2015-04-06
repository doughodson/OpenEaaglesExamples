//------------------------------------------------------------------------------
// Class: DspRadar
//------------------------------------------------------------------------------
#ifndef __Eaagles_XPanel_DspRadar_H__
#define __Eaagles_XPanel_DspRadar_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
   namespace Basic      { class PairStream; }
   namespace Simulation { class Radar; }

namespace xPanel {

//------------------------------------------------------------------------------
// Class: DspRadar
// Description: Simple Realbeam B-Scan RADAR.  Displays the real-beam signal,
//              with color coded doppler shift, and overlaid with tracks.
// Factory name: DspRadar
//------------------------------------------------------------------------------
class DspRadar : public BasicGL::Graphic
{
   DECLARE_SUBCLASS(DspRadar,BasicGL::Graphic)

public:
   DspRadar();

   const Simulation::Radar* getRadar()         { return radar; }
   const Simulation::Radar* getRadar() const   { return radar; }
   bool setRadar(Simulation::Radar* const s)   { radar = s; return true; }

   void drawFunc() override;

   void updateData(const LCreal dt = 0.0) override;

private:
    const Simulation::Radar* radar;     // The test RADAR sensor
    SendData    azSD;
    SendData    elSD;

    // Tracks
    enum { MAX_TRKS = 50 };
    unsigned int nTracks;                   // Number of tracks
    int ntsTrk;                             // Index of the 'next-to-shoot' track
    LCreal      trkRng[MAX_TRKS];           // Track's range                    (meters)
    LCreal      trkAz[MAX_TRKS];            // Track's relative azimuth
    LCreal      trkVel[MAX_TRKS];           // Track's velocity                 (m/s)
    LCreal      trkRelGndTrk[MAX_TRKS];     // Track's relative ground track (to nearest 45 deg)
};

} // End xPanel namespace
} // End Eaagles namespace

#endif

