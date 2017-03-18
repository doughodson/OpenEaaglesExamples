
#include "DspRadar.hpp"

#include "openeaagles/models/system/Antenna.hpp"
#include "openeaagles/models/system/Radar.hpp"
#include "openeaagles/models/Track.hpp"
#include "openeaagles/models/system/TrackManager.hpp"

#include "openeaagles/base/Hsv.hpp"

#include "openeaagles/base/util/math_utils.hpp"

namespace oe {
namespace xpanel {

IMPLEMENT_SUBCLASS(DspRadar, "DspRadar")
EMPTY_SLOTTABLE(DspRadar)
EMPTY_SERIALIZER(DspRadar)
EMPTY_DELETEDATA(DspRadar)

DspRadar::DspRadar()
{
   STANDARD_CONSTRUCTOR()
}

void DspRadar::copyData(const DspRadar& org, const bool)
{
   BaseClass::copyData(org);

   radar = nullptr;
   nTracks = 0;
   ntsTrk = -1;
   azSD.empty();
   elSD.empty();
}

void DspRadar::updateData(const double dt)
{
   const models::Antenna* antenna = nullptr;
   nTracks = 0;
   ntsTrk = -1;

   if (radar != nullptr) {

      // Get our antenna
      antenna = radar->getAntenna();

      // Get our track manager
      const models::TrackManager* tm = radar->getTrackManager();

      // ---
      // Get the track list and convert them to display coordinates
      if (tm != nullptr) {
         base::safe_ptr<models::Track> trackList[MAX_TRKS];
         unsigned int n = tm->getTrackList(trackList,MAX_TRKS);
         for (unsigned int i = 0; i < n; i++) {
            base::Vec3d pos       = trackList[i]->getPosition();
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
      send( "azPtr", UPDATE_VALUE, static_cast<float>(base::angle::R2DCC * antenna->getAzimuth()),   azSD);
      send( "elPtr", UPDATE_VALUE, static_cast<float>(base::angle::R2DCC * antenna->getElevation()), elSD);
   }

   // Update base classes stuff
   BaseClass::updateData(dt);
}

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
      base::Vec4d rgb;
      base::Vec4d hsv;

      unsigned int n = radar->getNumSweeps();
      unsigned int nv = radar->getPtrsPerSweep();

      double sx = static_cast<double>(n-1)/2.0f;
      double sy = static_cast<double>(nv-1);

      const double* s0 = radar->getSweep(0);
      const double* c0 = radar->getClosure(0);
      unsigned int i0 = 0;

      for (unsigned int i = 1; i < n; i++) {
         const double* s1 = radar->getSweep(i);
         const double* c1 = radar->getClosure(i);
         double x0 = static_cast<double>(i0)/sx - 1.0f;
         double x1 = static_cast<double>(i)/sx - 1.0f;

         glBegin(GL_QUAD_STRIP);
         for (unsigned int j = 0; j < nv; j++) {
            double y = 2.0f * static_cast<double>(j)/sy;

            double vclos0 = base::alim(c0[j]/100.0f, 1.0f);
            hsv[0] = 120.0f - 120.0f * vclos0;
            hsv[1] = 1.0f;
            hsv[2] = s0[j];
            hsv[3] = 1.0f;
            base::Hsv::hsv2rgb(rgb, hsv);
            lcColor3v(rgb.ptr());
            glVertex3d(x0, y, 0.0);

            double vclos1 = base::alim(c1[j]/100.0f, 1.0f);
            hsv[0] = 120.0f - 120.0f * vclos1;
            hsv[1] = 1.0f;
            hsv[2] = s1[j];
            hsv[3] = 1.0f;
            base::Hsv::hsv2rgb(rgb, hsv);
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
      base::Vec4d rgb;
      base::Vec4d ntsRGB;
      base::Vec4d hsv;

      // Vertices of the basic symbol
      //static double maxRng = 40000.0;
      double maxRng = radar->getRange() * base::distance::NM2M;
      static double ss = 0.05;

      // The color
      hsv[0] = 300.0f;
      hsv[1] = 1.0f;
      hsv[2] = 1.0f;
      hsv[3] = 1.0f;
      base::Hsv::hsv2rgb(rgb, hsv);

      // The NTS color
      hsv[0] = 360.0f;
      base::Hsv::hsv2rgb(ntsRGB, hsv);

      for (unsigned int i = 0; i < nTracks; i++) {
         double xp = (base::angle::R2DCC * trkAz[i])/30.0;
         double yp = 2.0*trkRng[i]/maxRng;
         if (static_cast<int>(i) == ntsTrk) lcColor3v(ntsRGB.ptr());
         else lcColor3v(rgb.ptr());
         glPushMatrix();
         glTranslated(xp, yp, 0.0);
         glScaled(ss, ss, ss);
         if (trkVel[i] > 50.0) {
            double gt = -(base::angle::R2DCC * trkRelGndTrk[i]);
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

}
}
