
#include "WorldModel.hpp"

#include "openeaagles/dafif/AirportLoader.hpp"
#include "openeaagles/dafif/NavaidLoader.hpp"
#include "openeaagles/dafif/WaypointLoader.hpp"

IMPLEMENT_SUBCLASS(WorldModel, "WorldModel")

BEGIN_SLOTTABLE(WorldModel)
   "airportLoader",  //  1) Airport database
   "navaidLoader",   //  2) NAVAID database
   "waypointLoader", //  3) Waypoint database
END_SLOTTABLE(WorldModel)

BEGIN_SLOT_MAP(WorldModel)
    ON_SLOT( 1, setAirports,    oe::dafif::AirportLoader)
    ON_SLOT( 2, setNavaids,     oe::dafif::NavaidLoader)
    ON_SLOT( 3, setWaypoints,   oe::dafif::WaypointLoader)
END_SLOT_MAP()

EMPTY_SERIALIZER(WorldModel)

WorldModel::WorldModel()
{
   STANDARD_CONSTRUCTOR()
}

void WorldModel::copyData(const WorldModel& org, const bool)
{
   BaseClass::copyData(org);

   const oe::dafif::AirportLoader* apLoader = org.airports;
   setAirports( const_cast<oe::dafif::AirportLoader*>(static_cast<const oe::dafif::AirportLoader*>(apLoader)) );

   const oe::dafif::NavaidLoader* naLoader = org.navaids;
   setNavaids( const_cast<oe::dafif::NavaidLoader*>(static_cast<const oe::dafif::NavaidLoader*>(naLoader)) );

   const oe::dafif::WaypointLoader* wpLoader = org.waypoints;
   setWaypoints( const_cast<oe::dafif::WaypointLoader*>(static_cast<const oe::dafif::WaypointLoader*>(wpLoader)) );
}

void WorldModel::deleteData()
{
   setAirports( nullptr );
   setNavaids( nullptr );
   setWaypoints( nullptr );
}

void WorldModel::updateData(const double dt)
{
   // ---
   // Load DAFIF files (one pre frame)
   // ---
   if (airports != nullptr && airports->numberOfRecords() == 0) {
      // Load Airports
      airports->load();
   }
   else if (navaids != nullptr && navaids->numberOfRecords() == 0) {
      // Load Navaids
      navaids->load();
   }
   else if (waypoints != nullptr && waypoints->numberOfRecords() == 0) {
      // Load Waypoints
      waypoints->load();
   }

   BaseClass::updateData(dt);
}

// Returns the airport loader
oe::dafif::AirportLoader* WorldModel::getAirports()
{
   return airports;
}

// Returns the NAVAID loader
oe::dafif::NavaidLoader* WorldModel::getNavaids()
{
   return navaids;
}

// Returns the waypoint loader
oe::dafif::WaypointLoader* WorldModel::getWaypoints()
{
   return waypoints;
}

//------------------------------------------------------------------------------
// Sets the airport loader
//------------------------------------------------------------------------------
bool WorldModel::setAirports(oe::dafif::AirportLoader* const p)
{
   if (airports != nullptr) {
      airports->unref();
   }
   airports = p;
   if (airports != nullptr) {
      airports->ref();
   }
   return true;
}

//------------------------------------------------------------------------------
// Sets the navaid loader
//------------------------------------------------------------------------------
bool WorldModel::setNavaids(oe::dafif::NavaidLoader* const p)
{
   if (navaids != nullptr) {
      navaids->unref();
   }
   navaids = p;
   if (navaids != nullptr) {
      navaids->ref();
   }
   return true;
}

//------------------------------------------------------------------------------
// Sets the waypoint loader
//------------------------------------------------------------------------------
bool WorldModel::setWaypoints(oe::dafif::WaypointLoader* const p)
{
   if (waypoints != nullptr) {
      waypoints->unref();
   }
   waypoints = p;
   if (waypoints != nullptr) {
      waypoints->ref();
   }
   return true;
}


