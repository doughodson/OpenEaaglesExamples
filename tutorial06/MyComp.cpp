//------------------------------------------------------------------------------
// MyComp
//------------------------------------------------------------------------------

#include "MyComp.h"
#include "openeaagles/basic/String.h"
#include <cstdlib>

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_SUBCLASS(MyComp,"MyComp")
// setup slot table
BEGIN_SLOTTABLE(MyComp)
  "str"
END_SLOTTABLE(MyComp)
// map attributes to slots
BEGIN_SLOT_MAP(MyComp)
  ON_SLOT(1, setSlotStr, Basic::String)
END_SLOT_MAP()
EMPTY_SERIALIZER(MyComp)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MyComp::MyComp(void)
{
   STANDARD_CONSTRUCTOR()
   initData();
   std::cout << "MyComp::MyComp() called\n";
}

//
//
//
void MyComp::initData()
{
   str = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void MyComp::copyData(const MyComp& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      initData();
   }

   if (str != 0) { str->unref(); str = 0; }
   if (org.str != 0) str = org.str->clone();

   std::cout << "MyComp::copyData() called\n";
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void MyComp::deleteData()
{
   setStr( 0 );
   std::cout << "MyComp::deleteData() called\n";
}

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------
bool MyComp::setStr(const Basic::String* const x)
{
   if (str != 0) str->unref();
   str = x;
   if (str != 0) str->ref();
   return true;
}

const Basic::String* MyComp::getStr(void) const
{
   return str;
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
Basic::Object* MyComp::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

bool MyComp::setSlotStr(const Basic::String* const x)
{
   bool ok = false;
   if(x != 0) {
      ok = setStr(x);
   }
   return ok;
}

//------------------------------------------------------------------------------
// Component class related methods
//------------------------------------------------------------------------------
void MyComp::reset()
{
   // as an example, I'm going to dump string
   setStr(0);
   std::cout << "I've been reset!\n";

   BaseClass::reset();
}

void MyComp::updateTC(const LCreal dt)
{
   unsigned int millis = (unsigned int)(dt * 1000);
   std::cout << "Time has moved forward by " << millis << " milliseconds\n";

   // Update base classes stuff
   BaseClass::updateTC(dt);
}

void MyComp::updateData(const LCreal dt)
{
   // print out string info if a string has been defined
   if (str != 0)
      std::cout << "BG Str: " << str->getString() << "\n";
   else
      std::cout << "BG Str: Nothing to print\n";

   // Update base classes stuff
   BaseClass::updateData(dt);
}

} // namespace Tutorial
} // namespace Eaagles

