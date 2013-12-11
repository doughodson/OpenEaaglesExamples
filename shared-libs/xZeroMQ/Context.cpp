//------------------------------------------------------------------------------
// Class: Context
//------------------------------------------------------------------------------
#include "Context.h"
#include "openeaagles/basic/List.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/String.h"

#include <zmq.h>


namespace Eaagles {
namespace xZeroMQ {

//==============================================================================
// Class: Context
//==============================================================================
IMPLEMENT_SUBCLASS(Context, "ZmqContext")

// Slot Table
BEGIN_SLOTTABLE(Context)
   "type",                 // 1) String containing the socket type
END_SLOTTABLE(Context)

// Map slot table to handles
BEGIN_SLOT_MAP(Context)
   ON_SLOT(1, setSlotType, Basic::String)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
Context::Context ()
{
   STANDARD_CONSTRUCTOR()
   initData ();
}


void Context::initData ()
{
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Context::copyData (const Context& org, const bool cc)
{
   BaseClass::copyData (org);

   if (cc) {
   }
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void Context::deleteData ()
{
   initData ();
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// type: String containing the socket type
bool Context::setSlotType (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* Context::getSlotByIndex (const int si)
{
   return BaseClass::getSlotByIndex (si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& Context::serialize (std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if (!slotsOnly) {
      indent (sout, i);
      sout << "( " << getFormName () << std::endl;
      j = 4;
   }

   BaseClass::serialize (sout, i+j, true);

   if (!slotsOnly) {
      indent (sout, i);
      sout << ")" << std::endl;
   }

   return sout;
}

}  // End xZeroMQ namespace
}  // End Eaagles namespace

