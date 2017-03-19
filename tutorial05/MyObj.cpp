
#include "MyObj.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/List.hpp"
#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/String.hpp"
#include "openeaagles/base/Number.hpp"
#include "openeaagles/base/Identifier.hpp"
#include <cstdlib>

IMPLEMENT_SUBCLASS(MyObj, "MyObj")

BEGIN_SLOTTABLE(MyObj)
   "colorTable",         // 1: The Color table     <PairStream>
   "textColor",          // 2: Text color          <Identifier>
   "backColor",          // 3: Background color    <Identifier>
   "vector",             // 4: Vector              <List>
   "visible",            // 5: Visibility flag     <Number>
   "message",            // 6: The message         <String>
END_SLOTTABLE(MyObj)

BEGIN_SLOT_MAP(MyObj)
   ON_SLOT(1, setSlotColorTable, oe::base::PairStream)
   ON_SLOT(2, setSlotTextColor,  oe::base::Identifier)
   ON_SLOT(3, setSlotBackColor,  oe::base::Identifier)
   ON_SLOT(4, setSlotVector,     oe::base::List)
   ON_SLOT(5, setSlotVisible,    oe::base::Number)
   ON_SLOT(6, setSlotMessage,    oe::base::String)
END_SLOT_MAP()

EMPTY_SERIALIZER(MyObj)

MyObj::MyObj()
{
   STANDARD_CONSTRUCTOR()
}

void MyObj::copyData(const MyObj& org, const bool)
{
   BaseClass::copyData(org);

   if (colorTable != nullptr) { colorTable->unref(); colorTable = nullptr; }
   if (org.colorTable != nullptr) colorTable = org.colorTable->clone();

   if (textColor != nullptr) { textColor->unref(); textColor = nullptr; }
   if (org.textColor != nullptr) textColor = org.textColor->clone();

   if (backColor != nullptr) { backColor->unref(); backColor = nullptr; }
   if (org.backColor != nullptr) backColor = org.backColor->clone();

   if (vector != nullptr) { vector->unref(); vector = nullptr; }
   if (org.vector != nullptr) vector = org.vector->clone();

   if (message != nullptr) { message->unref(); message = nullptr; }
   if (org.message != nullptr) message = org.message->clone();

   visible = org.visible;
}

void MyObj::deleteData()
{
   setColorTable(nullptr);
   setTextColor(nullptr);
   setBackColor(nullptr);
   setVector(nullptr);
   setMessage(nullptr);
}

bool MyObj::setColorTable(const oe::base::PairStream* const x)
{
   if (colorTable != nullptr) colorTable->unref();
   colorTable = x;
   if (colorTable != nullptr) colorTable->ref();
   return true;
}

const oe::base::PairStream* MyObj::getColorTable() const
{
   return colorTable;
}

bool MyObj::setTextColor(const oe::base::Identifier* const x)
{
   if (textColor != nullptr) textColor->unref();
   textColor = x;
   if (textColor != nullptr) textColor->ref();
   return true;
}

const oe::base::Identifier* MyObj::getTextColor() const
{
   return textColor;
}

bool MyObj::setBackColor(const oe::base::Identifier* const x)
{
   if (backColor != nullptr) backColor->unref();
   backColor = x;
   if (backColor != nullptr) backColor->ref();
   return true;
}

const oe::base::Identifier* MyObj::getBackColor() const
{
   return backColor;
}

bool MyObj::setVector(const oe::base::List* const x)
{
   if (vector != nullptr) vector->unref();
   vector = x;
   if (vector != nullptr) vector->ref();
   return true;
}

const oe::base::List* MyObj::getVector() const
{
   return vector;
}

bool MyObj::setVisible(const bool x)
{
   visible = x;
   return true;
}

bool MyObj::getVisible() const
{
   return visible;
}

bool MyObj::setMessage(const oe::base::String* const x)
{
   if (message != nullptr) message->unref();
   message = x;
   if (message != nullptr) message->ref();
   return true;
}

const oe::base::String* MyObj::getMessage() const
{
   return message;
}

bool MyObj::setSlotColorTable(const oe::base::PairStream* const x)
{
   bool ok = false;
   if (x != nullptr) {
      ok = setColorTable(x);
   }
   return ok;
}

bool MyObj::setSlotTextColor(const oe::base::Identifier* const x)
{
   bool ok = false;
   if (x != nullptr) {
      ok = setTextColor(x);
   }
   return ok;
}

bool MyObj::setSlotBackColor(const oe::base::Identifier* const x)
{
   bool ok = false;
   if (x != nullptr) {
      ok = setBackColor(x);
   }
   return ok;
}

bool MyObj::setSlotVector(const oe::base::List* const x)
{
   bool ok = false;
   if (x != nullptr) {
      ok = setVector(x);
   }
   return ok;
}

bool MyObj::setSlotVisible(const oe::base::Number* const x)
{
   bool ok = false;
   if (x != nullptr) {
      ok = setVisible(x->getBoolean());
   }
   return ok;
}

bool MyObj::setSlotMessage(const oe::base::String* const x)
{
   bool ok = false;
   if (x != nullptr) {
      ok = setMessage(x);
   }
   return ok;
}

//------------------------------------------------------------------------------
// isValid() -- I'm not going to actually check anything - this method is here
//              to demonstrate that the capability to check data exists within
//              the framework
//------------------------------------------------------------------------------
bool MyObj::isValid() const
{
   return true;
}
