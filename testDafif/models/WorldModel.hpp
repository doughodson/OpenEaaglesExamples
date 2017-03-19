
#ifndef __WorldModel_H__
#define __WOrldModel_H__

#include "openeaagles/models/WorldModel.hpp"

namespace oe {
namespace dafif { class AirportLoader; class NavaidLoader; class WaypointLoader; }
}

//------------------------------------------------------------------------------
// Class: WorldModel
//
// Description: Class to manage the reference position, and other common
//              simulation support components (ground truths, terrain elevation
//              database, etc)
//
// Slots --
//
//    airportLoader  <dafif::AirportLoader>   ! Airport database (default: nullptr)
//    navaidLoader   <dafif::NavaidLoader>    ! NAVAID database (default: nullptr)
//    waypointLoader <dafif::WaypointLoader>  ! Waypoint database (default: nullptr)
//
//
// Environments:
//
//    Current simulation environments include terrain elevation posts, getTerrain(),
//    atmosphere model, getAtmosphere(), and DAFIF navigational aids,
//    getNavaids(), getAirports() and getWaypoints().
//
// Shutdown:
//
//    At shutdown, the parent object must send a SHUTDOWN_EVENT event to
//    this object, environments and other components.
//
// Factory name: Simulation
//------------------------------------------------------------------------------
class WorldModel : public oe::models::WorldModel
{
    DECLARE_SUBCLASS(WorldModel, oe::models::WorldModel)

public:
    WorldModel();

    oe::dafif::AirportLoader* getAirports();           // Returns the airport loader
    oe::dafif::NavaidLoader* getNavaids();             // Returns the NAVAID loader
    oe::dafif::WaypointLoader* getWaypoints();         // Returns the waypoint loader

    virtual bool setAirports(oe::dafif::AirportLoader* const p);   // Sets the airport loader
    virtual bool setNavaids(oe::dafif::NavaidLoader* const p);     // Sets the NAVAID loader
    virtual bool setWaypoints(oe::dafif::WaypointLoader* const p); // Sets the waypoint loader

    virtual void updateData(const double dt = 0.0) override;

private:
   oe::dafif::AirportLoader*  airports {};   // Airport loader
   oe::dafif::NavaidLoader*   navaids {};    // NAVAID loader
   oe::dafif::WaypointLoader* waypoints {};  // Waypoint loader

};


#endif
