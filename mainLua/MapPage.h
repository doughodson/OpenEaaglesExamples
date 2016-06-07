// -------------------------------------------------------------------------------
// Class: MapPage
// Description:
//      Derived MapPage that will show how to add, remove, and update symbols with the
//      SymbolLoader class.
// -------------------------------------------------------------------------------
#ifndef __MapPage_H__
#define __MapPage_H__

#include "openeaagles/graphics/MapPage.h"

namespace oe {
namespace simulation { class Player; }
namespace graphics { class SymbolLoader; }
}

class TestStation;

class MapPage : public oe::graphics::MapPage
{
   DECLARE_SUBCLASS(MapPage, oe::graphics::MapPage)
    
public:
   MapPage();  

   // BasicGL::Graphic interface
   virtual void drawFunc();
   //virtual void drawHoldingPattern(const double aLat, const double aLon, const double ibCrs, const double tgs);

   // Basic::Component interface
   virtual void updateData(const double dt = 0.0);

private:
   void drawLine(const double x, const double y);
   void drawSemiCircle(const double startAngle, const double radius);
   void drawHoldingPattern();
   // holds our players
   static const int MAX_PLAYERS = 200;
   static const int MAX_READOUTS = 20;

   oe::simulation::Player* player[MAX_PLAYERS];    // player pointer
   int playerIdx[MAX_PLAYERS];                     // index of our symbol for the given player
   // player symbol loader
   oe::graphics::SymbolLoader* loader;             // holds our loader for quick reference
   TestStation* pStn;                              // holds our station (to get the player list quickly)

   // is our route loaded?
   bool routeLoaded;              

   // show where our lat/lons are
   SendData latsSD[MAX_READOUTS];
   int lats[MAX_READOUTS];
          
   SendData latReadoutXPosSD[MAX_READOUTS];
   float latReadoutXPos[MAX_READOUTS];
          
   SendData latReadoutYPosSD[MAX_READOUTS];
   float latReadoutYPos[MAX_READOUTS];
          
   // lons
   SendData lonsSD[MAX_READOUTS];
   int lons[MAX_READOUTS];
          
   SendData lonReadoutXPosSD[MAX_READOUTS];
   float lonReadoutXPos[MAX_READOUTS];
          
   SendData lonReadoutYPosSD[MAX_READOUTS];
   float lonReadoutYPos[MAX_READOUTS];
};

#endif

