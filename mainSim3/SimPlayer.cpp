
#include "SimPlayer.h"
#include "openeaagles/base/List.h"
#include "openeaagles/base/osg/Matrix"
#include "openeaagles/base/units/Angles.h"

namespace oe {
namespace example {

IMPLEMENT_SUBCLASS(SimPlayer, "SimPlayer")
EMPTY_DELETEDATA(SimPlayer)
EMPTY_COPYDATA(SimPlayer)

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
    //ON_SLOT(1, setSlotMasterMode, base::String)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SimPlayer::SimPlayer()
{
    STANDARD_CONSTRUCTOR()

    static base::String generic("Sim");
    setType(&generic);
}

//------------------------------------------------------------------------------
// reset() --
//------------------------------------------------------------------------------
void SimPlayer::reset()
{
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// getSlotByIndex() for graphics::Graphic
//------------------------------------------------------------------------------
base::Object* SimPlayer::getSlotByIndex(const int si)
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

    BaseClass::serialize(sout,i+j,true);

    if ( !slotsOnly ) {
        indent(sout,i);
        sout << ")" << endl;
    }

    return sout;
}

} // End example namespace
} // End oe namespace
