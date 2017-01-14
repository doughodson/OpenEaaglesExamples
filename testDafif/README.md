
DAFIF tests; lots of test routines (each one very simple).



// Test common stuff
test99		DsMagvar::magvar()


// Test DsAirportLoader
dump0		Dump the airport file (file0)

test00		Basic DsAirportLoader; just loads records and prints
test00I		DsAirportLoader.getNumIlsRecords()
test00R		DsAirportLoader.getNumRunwayRecords()

test01		DsAirportLoader.airport()
test01I		DsAirportLoader.queryIlsByNumber() and getIls()
test01R		DsAirportLoader.queryRunwayByNumber() and getRunway()

test02		DsAirportLoader.queryByIdent()
test02I		DsAirportLoader.queryIlsByIdent()
test02R		DsAirportLoader.queryRunwayByIdent()

test04		DsAirportLoader.queryByFreq()
test04I		DsAirportLoader.queryIlsByFreq()
test04R		DsAirportLoader.queryRunwayByFreq()

test05		DsAirportLoader.queryByRange()
test05I		DsAirportLoader.queryIlsByRange()
test05R		DsAirportLoader.queryRunwayByRange()

test06		DsAirportLoader.queryByKey()
test06I		DsAirportLoader.queryIlsBySubkey()
test06R		DsAirportLoader.queryRunwayBySubkey()

test07		DsAirportLoader.queryByLength()
test07R		DsAirportLoader.queryRunwayByLength()

test08		DsAirportLoader.queryByChannel()
test08I		DsAirportLoader.queryIlsByChannel()
test08R		DsAirportLoader.queryRunwayByChannel()

test09		DsAirportLoader.queryByType()
test09I		DsAirportLoader.queryIlsByType()

test0A		DsAirportLoader; ICAO sorted listing

test0B		DsAirportLoader.queryByIcao()


// Test DsNavaidLoader
dump2		Dump the NAVAID records (file2)

test20		Basic DsNavaidLoader; just loads records and prints

test21		DsNavaidLoader.navaid()

test22		DsNavaidLoader.queryByIdent()

test23		DsNavaidLoader; freq list sorting

test24		DsNavaidLoader.queryByFreq()

test25		DsNavaidLoader.queryByRange()

test26		DsNavaidLoader.queryByKey()

test27		DsNavaidLoader; channel list sorting

test28		DsNavaidLoader.queryByChannel()

test29		DsNavaidLoader.queryByType()

test2A		DsNavaidLoader; ICAO sorted listing

test2B		DsNavaidLoader.queryByIcao()


// Test DsWaypointLoader
dump3		Dump the waypoint records (file3)

test30		Basic DsWaypointLoader; just loads records and prints

test31		DsWaypointLoader.waypoint()

test32		DsWaypointLoader.queryByIdent()

test35		DsWaypointLoader.queryByRange()

test36		DsWaypointLoader.queryByKey()

test3A		DsWaypointLoader; ICAO sorted listing

test3B		DsWaypointLoader.queryByIcao()

