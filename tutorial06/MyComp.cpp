//------------------------------------------------------------------------------
// MyComp
//------------------------------------------------------------------------------

#include "MyComp.h"
#include "openeaagles/base/String.h"
#include <cstdlib>

namespace oe {
namespace Tutorial {

IMPLEMENT_SUBCLASS(MyComp,"MyComp")
// setup slot table
BEGIN_SLOTTABLE(MyComp)
  "str"
END_SLOTTABLE(MyComp)
// map attributes to slots
BEGIN_SLOT_MAP(MyComp)
  ON_SLOT(1, setSlotStr, base::String)
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

void MyComp::initData()
{
   str = nullptr;
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

   if (str != nullptr) { str->unref(); str = nullptr; }
   if (org.str != nullptr) str = org.str->clone();

   std::cout << "MyComp::copyData() called\n";
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void MyComp::deleteData()
{
   setStr( nullptr );
   std::cout << "MyComp::deleteData() called\n";
}

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------
bool MyComp::setStr(const base::String* const x)
{
   if (str != nullptr) str->unref();
   str = x;
   if (str != nullptr) str->ref();
   return true;
}

const base::String* MyComp::getStr(void) const
{
   return str;
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
base::Object* MyComp::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

bool MyComp::setSlotStr(const base::String* const x)
{
   bool ok = false;
   if(x != nullptr) {
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
   setStr(nullptr);
   std::cout << "I've been reset!\n";

   BaseClass::reset();
}

void MyComp::updateTC(const LCreal dt)
{
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   std::cout << "Time has moved forward by " << millis << " milliseconds\n";

   // Update base classes stuff
   BaseClass::updateTC(dt);
}

void MyComp::updateData(const LCreal dt)
{
   // print out string info if a string has been defined
   if (str != nullptr)
      std::cout << "BG Str: " << str->getString() << "\n";
   else
      std::cout << "BG Str: Nothing to print\n";

   // Update base classes stuff
   BaseClass::updateData(dt);
}

} // namespace Tutorial
} // namespace oe

