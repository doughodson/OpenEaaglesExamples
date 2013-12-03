// Definition of NAV modes and types
#ifndef __Eaagles_Demo_Navdefs_H__
#define __Eaagles_Demo_Navdefs_H__

namespace Eaagles {
namespace Demo {

    // nav types 
    const int VORTAC  = 0;  // variable omni-range tacan
    const int TACAN   = 1;  // tacan    
    const int INAV    = 2;  // ins system
    const int VORDME  = 3;  // vor using DME
    const int VOR     = 4;  // vor

    // nav modes
    const int DECLUTTER    = 0;
    const int MAP_MODE     = 1;
    const int NORMAL       = 2;
    const int HSI_MODE     = 3;
    const int ARC_MODE     = 4;
    const int ARC_MAP_MODE = 5;

    // nav sources
    const int PRIMARY   = 0;
    const int SECONDARY = 1;

    // pilot/copilot
    const int PILOT   = 0;
    const int COPILOT = 1;

    // readout modes
    const int ND_TTG  = 1;   // time to go
    const int ND_GSP  = 2;   // ground speed/drift angle
    const int ND_TAS  = 3;   // true air speed
    const int ND_ET   = 4;   // elapsed time
    const int ND_WIND = 5;   // wind dir/speed, drift angle

}; // end Demo namespace 
}; // end Eaagles namespace

#endif
