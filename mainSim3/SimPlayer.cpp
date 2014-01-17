
#include "SimPlayer.h"
#include "openeaagles/simulation/RfSensor.h"
#include "openeaagles/simulation/StoresMgr.h"
#include "openeaagles/simulation/DynamicsModels.h"
#include "openeaagles/sensors/Tws.h"
#include "openeaagles/sensors/Gmti.h"
#include "openeaagles/basic/List.h"
#include "openeaagles/basic/osg/Matrix"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(SimPlayer,"SimPlayer")

//------------------------------------------------------------------------------
// Slot table for this form type
//------------------------------------------------------------------------------
BEGIN_SLOTTABLE(SimPlayer)
    "xxx",             // dummy
END_SLOTTABLE(SimPlayer)

//------------------------------------------------------------------------------
//  Map slot table to handlers
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(SimPlayer)
    //ON_SLOT(1, setSlotMasterMode, Basic::String)
END_SLOT_MAP()


//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SimPlayer::SimPlayer()
{
    STANDARD_CONSTRUCTOR()
    
    static Basic::String generic("Sim");
    setType(&generic);
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void SimPlayer::copyData(const SimPlayer& org, const bool)
{
    BaseClass::copyData(org);
}

void SimPlayer::deleteData()
{
}

//------------------------------------------------------------------------------
// reset() -- 
//------------------------------------------------------------------------------
void SimPlayer::reset()
{
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// getSlotByIndex() for BasicGL::Graphic
//------------------------------------------------------------------------------
Basic::Object* SimPlayer::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& SimPlayer::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
    using namespace std;

    int j = 0;
    if ( !slotsOnly ) {
        //indent(sout,i);
        sout << "( " << getFactoryName() << endl;
        j = 4;
    }

    //indent(sout,i+j);
    //sout << "masterMode: " << findMasterModeName(getMasterMode()) << endl;


    BaseClass::serialize(sout,i+j,true);

    if ( !slotsOnly ) {
        indent(sout,i);
        sout << ")" << endl;
    }

    return sout;
}

} // End Example namespace
} // End Eaagles namespace
