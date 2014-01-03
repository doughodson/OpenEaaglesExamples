// -------------------------------------------------------------------------------
// Class: MapPage
// -------------------------------------------------------------------------------
#include "MapPage.h"
#include "TestStation.h"
#include "MapDisplay.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/Autopilot.h"
#include "openeaagles/simulation/AirVehicle.h"

#include "openeaagles/simulation/Navigation.h"
#include "openeaagles/simulation/Route.h"
#include "openeaagles/simulation/Steerpoint.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/basicGL/SymbolLoader.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/vehicles/LaeroModel.h"
#include "openeaagles/basicGL/Display.h"
#include "openeaagles/basicGL/Shapes.h"

#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/units/Times.h"

#include <GL/glut.h>

namespace Eaagles {
   namespace BasicGL {
      class OcclusionArc;
   }

namespace Example {

IMPLEMENT_SUBCLASS(MapPage,"TestMapPage")
EMPTY_SLOTTABLE(MapPage)
EMPTY_SERIALIZER(MapPage)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MapPage::MapPage()
{
    STANDARD_CONSTRUCTOR()
    for (int i = 0; i < MAX_PLAYERS; i++) {
        player[i] = 0;
        playerIdx[i] = -1;
    }
    pStn = 0;
    loader = 0;

    for (int i = 0; i < MAX_READOUTS; i++) {
        latsSD[i].empty();
        lats[i] = 0;
        latReadoutXPosSD[i].empty();
        latReadoutXPos[i] = 0;
        latReadoutYPosSD[i].empty();
        latReadoutYPos[i] = 0;
        lonsSD[i].empty();
        lons[i] = 0;
        lonReadoutXPosSD[i].empty();
        lonReadoutXPos[i] = 0;
        lonReadoutYPosSD[i].empty();
        lonReadoutYPos[i] = 0;
    }

    routeLoaded = false;
}  

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void MapPage::copyData(const MapPage& org, const bool)
{
    // copy base class stuff first
    BaseClass::copyData(org);

    // regardless of copy, we will create all new symbols
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (player[i] != 0) {
            player[i]->unref();
            player[i] = 0;
        }
        if (org.player[i] != 0) {
            player[i] = org.player[i];
            player[i]->ref();
        }
        playerIdx[i] = org.playerIdx[i];
    }

    if (loader != 0) {
        loader->unref();
        loader = 0;
    }
    if (org.loader != 0) {
        loader = org.loader;
        loader->ref();
    }

    if (pStn != 0) {
        pStn->unref();
        pStn = 0;
    }
    if (org.pStn != 0) {
        pStn = org.pStn;
        pStn->ref();
    }

    for (int i = 0; i < MAX_READOUTS; i++) {
        latsSD[i].empty();
        lats[i] = org.lats[i];
        latReadoutXPosSD[i].empty();
        latReadoutXPos[i] = org.lonReadoutXPos[i];
        latReadoutYPosSD[i].empty();
        latReadoutYPos[i] = org.latReadoutYPos[i];
        lonsSD[i].empty();
        lons[i] = org.lons[i];
        lonReadoutXPosSD[i].empty();
        lonReadoutXPos[i] = org.lonReadoutXPos[i];
        lonReadoutYPosSD[i].empty();
        lonReadoutYPos[i] = org.lonReadoutYPos[i];
    }

    routeLoaded = org.routeLoaded;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void MapPage::deleteData()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (player[i] != 0) {
            player[i]->unref();
            player[i] = 0;
        }
    }
    if (pStn != 0) {
        pStn->unref();
        pStn = 0;
    }
    if (loader != 0) {
        loader->unref();
        loader = 0;
    }
}

void MapPage::drawLine(const double x, const double y)
{
      glBegin(GL_LINES);
         glVertex2d(0.0, 0.0);
         glVertex2d(x, y);
      glEnd();
} 

void MapPage::drawSemiCircle(const double startAngle, const double radius)
{
   const double eps = 0.015;
   double innerRadius = radius - eps;
   double outerRadius = radius + eps;
   GLUquadricObj* q1 = gluNewQuadric();
   gluQuadricDrawStyle(q1, GLU_FILL);
   gluPartialDisk(q1, innerRadius, outerRadius, 100, 1, startAngle, 180.0);
   gluDeleteQuadric(q1);
}

//void MapPage::drawHoldingPattern(const double aLat, const double aLon, const double ibCrs, const double tas)
//{
   //if (pStn != 0) {
   //   Simulation::Player* pPlr  = pStn->getOwnship();
   //   if (pPlr != 0) {
   //      Vehicle::LaeroModel* pRac = (Vehicle::LaeroModel*) pPlr->getDynamicsModel();
   //      if (pRac != 0) {

   //         pRac->setAnchorLat(aLat);
   //         pRac->setAnchorLon(aLon);
   //         pRac->setInboundCourse(ibCrs);
   //         pRac->setAcftSpeed(tas);

   //         this->drawHoldingPattern();
   //      }
   //   }
   //}
//}


void MapPage::drawHoldingPattern()
{
   if (pStn != 0) {
      Simulation::Player* pPlr  = pStn->getOwnship();
      if (pPlr != 0) {
         Simulation::Autopilot* pRac = (Simulation::Autopilot*) pPlr->getPilot();
         if (pRac != 0) {

         //---------------------------------------------------------------------------
         // Draw Holding Pattern
         //---------------------------------------------------------------------------
            double aLat = 0, aLon = 0, mLat = 0, mLon = 0;
            pRac->getLoiterPointAnchors(&aLat, &aLon, &mLat, &mLon);
            //std::cout << "MIRROR LAT/LON = " << mLat << ", " << mLon << std::endl;
            double ibCrs = pRac->getLoiterCourse();
            double osVel = pPlr->getTotalVelocityKts();

            //setReferenceLatDeg(0.0);
            //setReferenceLonDeg(0.0);

//            double refLat = getReferenceLatDeg();
//            double refLon = getReferenceLonDeg();

            double omegaDps = 3.0;                                      //dps
            double omegaRps = omegaDps * Basic::Angle::D2RCC;           //rps
            double rocNM = (osVel / Basic::Time::H2S) / omegaRps;       //nm
            //double obTimeMin = 2.0;                                     //min
            //double obTimeSec = obTimeMin * Basic::Time::M2S;            //sec
            
            //double obDistNM = (osVel / Basic::Time::H2S) * obTimeSec;   //nm

            double obDistNM = 0;
            if (pRac->isLoiterTimeBased()) {
               obDistNM = (osVel / Basic::Time::H2S) * pRac->getLoiterTime();   //nm
            }
            else {
               obDistNM = pRac->getLoiterPatternLengthNM();
            }

            double aLatSU = 0.0;
            double aLonSU = 0.0;
            latLon2Screen(aLat, aLon, &aLatSU, &aLonSU);

            double rocSU = rocNM * getScale();
            double obDistSU = obDistNM * getScale();

            //==============================================
            // begin drawing holding pattern

            glPushMatrix();

               // convert to NED coordinate system
               glRotated(90.0, 0, 0, 1);
               glRotated(180.0, 1, 0, 0);

               // set anchor waypoint and inbound course
               glTranslated(aLonSU, aLatSU, 0.0);
               glRotated(ibCrs, 0.0, 0.0, 1.0);

               // draw holding pattern
               //glColor3f(1, 1, 0);  // yellow
               drawLine(-obDistSU, 0.0);  // inbound path

               //glColor3f(1, 0, 0);  // red
               glTranslated(-obDistSU, rocSU, 0.0);
               drawSemiCircle(180.0, rocSU);  // inbound turn

               //glColor3f(1, 1, 0);  // yellow
               glTranslated(0.0, rocSU, 0.0);
               drawLine(obDistSU, 0.0);  // outbound path

               //glColor3f(0, 1, 0);  // green
               glTranslated(obDistSU, -rocSU, 0.0);
               drawSemiCircle(0.0, rocSU);  // outbound turn

            glPopMatrix();

            // end drawing holding pattern
            //==============================================
         }
      }
   }
}

void MapPage::drawFunc()
{

      //-------------------------------------------------------
      // get data pointers 
      //-------------------------------------------------------
   if (pStn != 0) {
      Simulation::Player* pPlr  = pStn->getOwnship();
      if (pPlr != 0) {

         // get the autopilot
         Simulation::Autopilot* ap = (Simulation::Autopilot*)pPlr->getPilot();
         if (ap != 0 && ap->isLoiterModeOn()) drawHoldingPattern();


         //---------------------------------------------------------------------------
         // get our viewport
         //---------------------------------------------------------------------------
         MapDisplay* pDsp = (MapDisplay*) getDisplay();
         //BasicGL::Display* pDsp = (BasicGL::Display*) getDisplay();

         if (pDsp != 0) {
            //-----------------------------------------------------------------
            // get reference lat/lon
            //-----------------------------------------------------------------
            double refLat = getReferenceLatDeg();
            double refLon = getReferenceLonDeg();

            //-----------------------------------------------------------------
            // get lat/lon drawing limits
            //-----------------------------------------------------------------
            GLdouble l = 0, r = 0, t = 0, b = 0, n = 0, f = 0;
            pDsp->getOrtho(l, r, b, t, n, f);

            double latRange = getRange() / 60.0;
            double inchPerDegNS = t / latRange;
            double northernLat = refLat + latRange;
            double southernLat = refLat - latRange;

            double lonRange = latRange / getCosRefLat();
            double inchPerDegEW = r / lonRange;
            double easternLon = refLon + lonRange;
            double westernLon = refLon - lonRange;

            glPushMatrix();
            glBegin(GL_LINES);
               int latIdx = 0;
               int startLat = nint((LCreal)southernLat - 1);
               int endLat   = nint((LCreal)northernLat + 1);
               while (startLat < endLat) {
                  GLfloat refLatDist = GLfloat(refLat - startLat);
                  if (latIdx < MAX_READOUTS) {
                     lats[latIdx] = startLat;
                     refLatDist *= (GLfloat)inchPerDegNS;
                     latReadoutYPos[latIdx] = float(-refLatDist + 0.2);
                     latReadoutXPos[latIdx++] = float(l + 0.5f);
                  }
                  glVertex2f((GLfloat)l, -refLatDist);
                  glVertex2f((GLfloat)r, -refLatDist);
                  startLat++;
               }
            glEnd();

            // now make the other lat lines go away
            for (int i = latIdx; i < MAX_READOUTS; i++) {
               latReadoutYPos[i] = -10000;
            }
            glPopMatrix();

            glPushMatrix();
            glBegin(GL_LINES);
               int lonIdx = 0;
               int startLon = nint((LCreal)westernLon - 1);
               int endLon   = nint((LCreal)easternLon + 1);
               while (startLon < endLon) {
                  GLfloat refLonDist = GLfloat(refLon - startLon);
                  if (lonIdx < MAX_READOUTS) {
                     lons[lonIdx] = startLon;
                     refLonDist *= (GLfloat)inchPerDegEW;
                     lonReadoutXPos[lonIdx] = float(-refLonDist + 0.2);
                     lonReadoutYPos[lonIdx++] = float(t - 0.5f);
                  }
                  glVertex2f(-refLonDist, (GLfloat)b);
                  glVertex2f(-refLonDist, (GLfloat)t);
                  startLon++;
               }
            glEnd();

            // now make the other lon lines go away
            for (int i = lonIdx; i < MAX_READOUTS; i++) {
               lonReadoutYPos[i] = -10000;
            }
            glPopMatrix();
         }
      }
   }
}

//------------------------------------------------------------------------------
// updateData() -- update background data
//------------------------------------------------------------------------------
void MapPage::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    // get our pointers
    if (loader == 0) {
        Basic::Pair* pair = findByName("playerLoader");
        if (pair != 0) {
            loader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
            if (loader != 0) loader->ref();
        }
    }

    if (pStn == 0) {
        BasicGL::Display* pDsp = getDisplay();
        if (pDsp != 0) {
            pStn = (TestStation*)pDsp->findContainerByType(typeid(TestStation));
            if (pStn != 0) {
                pStn->ref();
                // set our reference lat / lon initially
                Simulation::Simulation* sim = pStn->getSimulation();
                if (sim != 0) {
                    setReferenceLatDeg(sim->getRefLatitude());
                    setReferenceLonDeg(sim->getRefLongitude());
                }
            }
        }
    }

   // go through one time and add our symbols for the route
   if (!routeLoaded && pStn != 0) {
      Basic::Pair* pair = findByName("routeLoader");
      if (pair != 0) {
         BasicGL::SymbolLoader* routeLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
         if (routeLoader != 0) {
            // get our player's route
            Simulation::Player* ply = pStn->getOwnship();
            if (ply != 0) {
               Simulation::Navigation* nav = ply->getNavigation();
               if (nav != 0) {
                  Simulation::Route* rte = nav->getPriRoute();
                  if (rte != 0) {
                     SPtr<Simulation::Steerpoint> stpts[10];
                     unsigned int numStpts = rte->getAllSteerpoints(stpts, 10);
                     for (unsigned int i = 0; i < numStpts; i++) {
                        if (stpts[i] != 0) {
                           int pos = routeLoader->addSymbol(1, "stpt");
                           // now update the position
                           routeLoader->updateSymbolPositionLL(pos, stpts[i]->getLatitude(), stpts[i]->getLongitude());
                           // unref when we are done
                           stpts[i] = 0;
                        }
                     }
                  }
               }
            }
         }
      }
      routeLoaded = true;
   }


    // let's update our players
    if (loader != 0 && pStn != 0) {
        Basic::PairStream* stream = pStn->getPlayers();                      
        if (stream != 0) {
            // create our new player list
            Simulation::Player* newPlayers[MAX_PLAYERS];
            int numNewPlayers = 0;
            // go through all of our non-ownship players and populate our new list
            Basic::List::Item* item = stream->getFirstItem();
            while (item != 0 && numNewPlayers < MAX_PLAYERS) {
                Basic::Pair* pair = (Basic::Pair*)item->getValue();
                if (pair != 0) {
                    Simulation::Player* pPlr = dynamic_cast<Simulation::Player*>(pair->object());
                    if (pPlr != 0) {
                        newPlayers[numNewPlayers] = pPlr;
                        newPlayers[numNewPlayers++]->ref();
                    }
                }
                item = item->getNext();
            }

            // ok, go through our new list and match it with our old, and throw
            // away any old players that aren't in the new list, and add any new
            // players that arent in the old list
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (player[i] != 0) {
                    bool match = false; 
                    for (int j = 0; j < numNewPlayers && !match; j++) {
                        if (player[i] == newPlayers[j]) {
                            // if they do match, get rid of our new player, so we don't re-add it 
                            // later accidentally
                            match = true;
                            newPlayers[j]->unref();
                            newPlayers[j] = 0;
                        }
                    }
                    // if our player doesn't match, we remove it from our list
                    if (!match) {
                        loader->removeSymbol(playerIdx[i]);
                        player[i]->unref();
                        player[i] = 0;
                        playerIdx[i] = -1;
                    }
                }
            }

            // ok, now we have removed our old players (and our matched ones), let's add our new ones!
            for (int i = 0; i < numNewPlayers; i++) {
                // make sure this player wasn't deleted earlier
                if (newPlayers[i] != 0) {
                    bool found = false;
                    for (int j = 0; j < MAX_PLAYERS && !found; j++) {
                        if (player[j] == 0) {
                            found = true;
                            // found an empty player, let's set him!
                            player[j] = newPlayers[i];
                            player[j]->ref();
                            int type = 1;
                            if (player[j]->isSide(Simulation::Player::RED)) type = 2;
                            playerIdx[j] = loader->addSymbol(type, "");  //<LDB - "player"
                            if (player[j]->getName() != 0) {
                                loader->updateSymbolText(playerIdx[j], "name", player[j]->getName()->getString());
                            }
                            // now let's empty our new player list
                            newPlayers[i]->unref();
                            newPlayers[i] = 0;
                        }
                    }
                }
            }

            // ok, now update our symbols' positions
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (player[i] != 0) {
                    loader->updateSymbolPositionLL(playerIdx[i], player[i]->getLatitude(), player[i]->getLongitude());
                    loader->updateSymbolHeading(playerIdx[i], player[i]->getHeadingD());
                }
            }
        }
    }
    

    // now send our lat / lon text data
    send("lattext%d", UPDATE_VALUE,  lats,           latsSD,           MAX_READOUTS);
    send("latline%d", UPDATE_VALUE,  latReadoutXPos, latReadoutXPosSD, MAX_READOUTS);
    send("latline%d", UPDATE_VALUE2, latReadoutYPos, latReadoutYPosSD, MAX_READOUTS);

    send("lontext%d", UPDATE_VALUE,  lons,           lonsSD,           MAX_READOUTS);
    send("lonline%d", UPDATE_VALUE,  lonReadoutXPos, lonReadoutXPosSD, MAX_READOUTS);
    send("lonline%d", UPDATE_VALUE2, lonReadoutYPos, lonReadoutYPosSD, MAX_READOUTS);
}

}
}

