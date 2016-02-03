// -------------------------------------------------------------------------------
// Class: MapPage
//
// Description:
//      Derived MapPage that will show how to add, remove, and update symbols with the
//      SymbolLoader class.
// -------------------------------------------------------------------------------
#ifndef __oe_example_MapPage_H__
#define __oe_example_MapPage_H__

#include "openeaagles/basicGL/MapPage.h"

namespace oe {
namespace simulation {
    class Player;
}
namespace BasicGL {
    class SymbolLoader;
}
namespace example {

class Station;

class MapPage : public BasicGL::MapPage
{
    DECLARE_SUBCLASS(MapPage, BasicGL::MapPage)

public:
    MapPage();

    void drawFunc() override;

    void updateData(const LCreal dt = 0.0) override;

private:
    // holds our players
    static const int MAX_PLAYERS = 200;
    static const int MAX_READOUTS = 20;
    simulation::Player* player[MAX_PLAYERS];    // player pointer
    int playerIdx[MAX_PLAYERS];                 // index of our symbol for the given player
    BasicGL::SymbolLoader* loader;              // holds our loader for quick reference
    Station* stn;                   // holds our station (to get the player list quickly)
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

}  // end of example namespace
}  // end of oe namespace

#endif

