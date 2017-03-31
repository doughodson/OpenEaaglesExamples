
#ifndef __MapPage_H__
#define __MapPage_H__

#include "openeaagles/graphics/MapPage.hpp"

#include <array>

namespace oe {
namespace models { class Player; }
namespace graphics { class SymbolLoader; }
}
class Station;

// -------------------------------------------------------------------------------
// Class: MapPage
//
// Description:
//      Derived MapPage that will show how to add, remove, and update symbols with the
//      SymbolLoader class.
// -------------------------------------------------------------------------------
class MapPage : public oe::graphics::MapPage
{
    DECLARE_SUBCLASS(MapPage, oe::graphics::MapPage)

public:
    MapPage();

    virtual void drawFunc() override;

    virtual void updateData(const double dt = 0.0) override;

private:
    // holds our players
    static const int MAX_PLAYERS = 200;
    static const int MAX_READOUTS = 20;
    std::array<oe::models::Player*, MAX_PLAYERS> player {};  // player pointer
    std::array<int, MAX_PLAYERS> playerIdx {};               // index of our symbol for the given player
    oe::graphics::SymbolLoader* loader {};          // holds our loader for quick reference
    Station* stn {};                                // holds our station (to get the player list quickly)
    // show where our lat/lons are
    SendData latsSD[MAX_READOUTS];
    std::array<int, MAX_READOUTS> lats {};
    SendData latReadoutXPosSD[MAX_READOUTS];
    std::array<float, MAX_READOUTS> latReadoutXPos {};
    SendData latReadoutYPosSD[MAX_READOUTS];
    std::array<float, MAX_READOUTS> latReadoutYPos {};
    // lons
    SendData lonsSD[MAX_READOUTS];
    std::array<int, MAX_READOUTS> lons {};
    SendData lonReadoutXPosSD[MAX_READOUTS];
    std::array<float, MAX_READOUTS> lonReadoutXPos {};
    SendData lonReadoutYPosSD[MAX_READOUTS];
    std::array<float, MAX_READOUTS> lonReadoutYPos {};
};

#endif
