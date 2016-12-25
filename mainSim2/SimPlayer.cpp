
#include "SimPlayer.hpp"
#include "openeaagles/base/List.hpp"
#include "openeaagles/base/units/Angles.hpp"

IMPLEMENT_SUBCLASS(SimPlayer, "SimPlayer")
EMPTY_DELETEDATA(SimPlayer)
EMPTY_COPYDATA(SimPlayer)
EMPTY_SLOTTABLE(SimPlayer)

SimPlayer::SimPlayer()
{
    STANDARD_CONSTRUCTOR()

    static oe::base::String generic("Sim");
    setType(&generic);
}

void SimPlayer::reset()
{
    BaseClass::reset();
}

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
