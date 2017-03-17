
// Definition of NAV modes and types
#ifndef __Navdefs_H__
#define __Navdefs_H__

// enum utilities

//
// template converts enum class to underlying integer value representation
//
template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}


// readout modes
//const int ND_TTG  = 1;   // time to go
//const int ND_GSP  = 2;   // ground speed/drift angle
//const int ND_TAS  = 3;   // true air speed
//const int ND_ET   = 4;   // elapsed time
//const int ND_WIND = 5;   // wind dir/speed, drift angle

#endif
