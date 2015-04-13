
#include "MfdDisplay.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MfdDisplay,"MfdDisplay")
EMPTY_SERIALIZER(MfdDisplay)

EMPTY_COPYDATA(MfdDisplay)
EMPTY_DELETEDATA(MfdDisplay)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MfdDisplay::MfdDisplay()
{
   STANDARD_CONSTRUCTOR()
}

} // End Example namespace
} // End Eaagles namespace
