//------------------------------------------------------------------------------
// Class: DspRadar
//------------------------------------------------------------------------------
#include "DspRadar.h"

#include "openeaagles/simulation/Antenna.h"
#include "openeaagles/simulation/Radar.h"
#include "openeaagles/simulation/Track.h"
#include "openeaagles/simulation/TrackManager.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/Hsv.h"

namespace Eaagles {
namespace xPanel {

IMPLEMENT_SUBCLASS(DspRadar,"DspRadar")
EMPTY_SLOTTABLE(DspRadar)
EMPTY_SERIALIZER(DspRadar)
EMPTY_DELETEDATA(DspRadar)

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// Constructor
DspRadar::DspRadar()
{
   STANDARD_CONSTRUCTOR()

   radar = nullptr;
   nTracks = 0;
   ntsTrk = -1;
   azSD.empty();
   elSD.empty();
}

// copy member data
void DspRadar::copyData(const DspRadar& org, const bool)
{
   BaseClass::copyData(org);

   radar = nullptr;
   nTracks = 0;
   ntsTrk = -1;
   azSD.empty();
   elSD.empty();
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void DspRadar::updateData(const LCreal dt)
{
   const Simulation::Antenna* antenna = nullptr;
   nTracks = 0;
   ntsTrk = -1;

   if (radar != nullptr) {

      // Get our antenna
      antenna = radar->getAntenna();

      // Get our track manager
      const Simulation::TrackManager* tm = radar->getTrackManager();

      // ---
      // Get the track list and convert them to display coordinates
      if (tm != nullptr) {
         Basic::safe_ptr<Simulation::Track> trackList[MAX_TRKS];
         unsigned int n = tm->getTrackList(trackList,MAX_TRKS);
         for (unsigned int i = 0; i < n; i++) {
            osg::Vec3 pos = trackList[i]->getPosition();
            trkRng[nTracks]       = pos.length();
            trkAz[nTracks]        = trackList[i]->getRelAzimuth();
            trkVel[nTracks]       = trackList[i]->getGroundSpeed();
            trkRelGndTrk[nTracks] = trackList[i]->getRelGroundTrack();
            if (trackList[i]->getShootListIndex() == 1) ntsTrk = i;
            nTracks++;
         }
      }
   }

   // Update antenna azimuth and elevation pointers
   if (antenna != nullptr) {
      send( "azPtr", UPDATE_VALUE, static_cast<float>(Basic::Angle::R2DCC * antenna->getAzimuth()),   azSD);
      send( "elPtr", UPDATE_VALUE, static_cast<float>(Basic::Angle::R2DCC * antenna->getElevation()), elSD);
   }

   // Update base classes stuff
   BaseClass::updateData(dt);
}

//------------------------------------------------------------------------------
// drawFunc() --
//------------------------------------------------------------------------------
void DspRadar::drawFunc()
{
   // Need a RADAR to draw; if not, just draw a big X
   if (radar == nullptr) {
      glBegin(GL_LINES);
         glVertex3d(-1.0,  0.0, 0.0);
         glVertex3d( 1.0,  2.0, 0.0);
         glVertex3d(-1.0,  2.0, 0.0);
         glVertex3d( 1.0,  0.0, 0.0);
      glEnd();
      return;
   }

   // Save the current color
   GLdouble  ocolor[4];
   glGetDoublev(GL_CURRENT_COLOR,ocolor);

   // ---
   // Draw the B-Scan
   // ---
   {
      osg::Vec4   rgb;
      osg::Vec4   hsv;

      unsigned int n = radar->getNumSweeps();
      unsigned int nv = radar->getPtrsPerSweep();

      LCreal sx = static_cast<LCreal>(n-1)/2.0f;
      LCreal sy = static_cast<LCreal>(nv-1);

      const LCreal* s0 = radar->getSweep(0);
      const LCreal* c0 = radar->getClosure(0);
      unsigned int i0 = 0;

      for (unsigned int i = 1; i < n; i++) {
         const LCreal* s1 = radar->getSweep(i);
         const LCreal* c1 = radar->getClosure(i);
         LCreal x0 = static_cast<LCreal>(i0)/sx - 1.0f;
         LCreal x1 = static_cast<LCreal>(i)/sx - 1.0f;

         glBegin(GL_QUAD_STRIP);
         for (unsigned int j = 0; j < nv; j++) {
            LCreal y = 2.0f * static_cast<LCreal>(j)/sy;

            LCreal vclos0 = alim(c0[j]/100.0f, 1.0f);
            hsv[0] = 120.0f - 120.0f * vclos0;
            hsv[1] = 1.0f;
            hsv[2] = s0[j];
            hsv[3] = 1.0f;
            Basic::Hsv::hsv2rgb(rgb, hsv);
            lcColor3v(rgb.ptr());
            glVertex3d(x0, y, 0.0);

            LCreal vclos1 = alim(c1[j]/100.0f, 1.0f);
            hsv[0] = 120.0f - 120.0f * vclos1;
            hsv[1] = 1.0f;
            hsv[2] = s1[j];
            hsv[3] = 1.0f;
            Basic::Hsv::hsv2rgb(rgb, hsv);
            lcColor3v(rgb.ptr());
            glVertex3d(x1, y, 0.0);
         }
         glEnd();

         s0 = s1;
         c0 = c1;
         i0 = i;
      }
   }

   // ---
   // Draw the tracks
   // ---
   {
      osg::Vec4   rgb;
      osg::Vec4   ntsRGB;
      osg::Vec4   hsv;

      // Vertices of the basic symbol
      //static LCreal maxRng = 40000.0;
      LCreal maxRng = radar->getRange() * Basic::Distance::NM2M;
      static double ss = 0.05;

      // The color
      hsv[0] = 300.0f;
      hsv[1] = 1.0f;
      hsv[2] = 1.0f;
      hsv[3] = 1.0f;
      Basic::Hsv::hsv2rgb(rgb, hsv);

      // The NTS color
      hsv[0] = 360.0f;
      Basic::Hsv::hsv2rgb(ntsRGB, hsv);

      for (unsigned int i = 0; i < nTracks; i++) {
         double xp = (Basic::Angle::R2DCC * trkAz[i])/30.0;
         double yp = 2.0*trkRng[i]/maxRng;
         if (static_cast<int>(i) == ntsTrk) lcColor3v(ntsRGB.ptr());
         else lcColor3v(rgb.ptr());
         glPushMatrix();
         glTranslated(xp, yp, 0.0);
         glScaled(ss, ss, ss);
         if (trkVel[i] > 50.0) {
            double gt = -(Basic::Angle::R2DCC * trkRelGndTrk[i]);
            glRotated(gt, 0.0, 0.0, 1.0);
            glBegin(GL_LINE_LOOP);
               glVertex3d( -1.0, -1.0, 0.2 );
               glVertex3d(  1.0, -1.0, 0.2 );
               glVertex3d(  1.0,  1.0, 0.2 );
               glVertex3d( -1.0,  1.0, 0.2 );
            glEnd();
            glBegin(GL_LINE_LOOP);
               glVertex3d( 0.0, 1.0, 0.2 );
               glVertex3d( 0.0, 3.0, 0.2 );
            glEnd();
         }
         else {
            glBegin(GL_POLYGON);
               glVertex3d( -0.5, -0.5, 0.2 );
               glVertex3d(  0.5, -0.5, 0.2 );
               glVertex3d(  0.5,  0.5, 0.2 );
               glVertex3d( -0.5,  0.5, 0.2 );
            glEnd();
         }
         glPopMatrix();
      }
   }

   // restore color
   glColor4dv(ocolor);
}

} // End xPanel namespace
} // End Eaagles namespace

