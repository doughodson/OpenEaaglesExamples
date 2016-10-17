
#include "MyComp.hpp"
#include "openeaagles/base/String.hpp"
#include <cstdlib>

IMPLEMENT_SUBCLASS(MyComp, "MyComp")
// setup slot table
BEGIN_SLOTTABLE(MyComp)
  "str"
END_SLOTTABLE(MyComp)
// map attributes to slots
BEGIN_SLOT_MAP(MyComp)
  ON_SLOT(1, setSlotStr, oe::base::String)
END_SLOT_MAP()
EMPTY_SERIALIZER(MyComp)

MyComp::MyComp()
{
   STANDARD_CONSTRUCTOR()
   initData();
   std::cout << "MyComp::MyComp() called\n";
}

void MyComp::initData()
{
   str = nullptr;
}

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

void MyComp::deleteData()
{
   setStr( nullptr );
   std::cout << "MyComp::deleteData() called\n";
}

bool MyComp::setStr(const oe::base::String* const x)
{
   if (str != nullptr) str->unref();
   str = x;
   if (str != nullptr) str->ref();
   return true;
}

const oe::base::String* MyComp::getStr() const
{
   return str;
}

oe::base::Object* MyComp::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

bool MyComp::setSlotStr(const oe::base::String* const x)
{
   bool ok = false;
   if(x != nullptr) {
      ok = setStr(x);
   }
   return ok;
}

void MyComp::reset()
{
   // as an example, I'm going to dump string
   setStr(nullptr);
   std::cout << "I've been reset!\n";

   BaseClass::reset();
}

void MyComp::updateTC(const double dt)
{
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   std::cout << "Time has moved forward by " << millis << " milliseconds\n";

   // Update base classes stuff
   BaseClass::updateTC(dt);
}

void MyComp::updateData(const double dt)
{
   // print out string info if a string has been defined
   if (str != nullptr)
      std::cout << "BG Str: " << str->getString() << "\n";
   else
      std::cout << "BG Str: Nothing to print\n";

   // Update base classes stuff
   BaseClass::updateData(dt);
}
