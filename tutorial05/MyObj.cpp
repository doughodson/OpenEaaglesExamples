//------------------------------------------------------------------------------
// MyObj
//------------------------------------------------------------------------------

#include "MyObj.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/List.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/String.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/Identifier.h"
#include <cstdlib>

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_SUBCLASS(MyObj,"MyObj")
// setup slot table
BEGIN_SLOTTABLE(MyObj)
  "colorTable",         // 1: The Color table     <PairStream>
  "textColor",          // 2: Text color          <Identifier>
  "backColor",          // 3: Background color    <Identifier>
  "vector",             // 4: Vector              <List>
  "visible",            // 5: Visibility flag     <Number>
  "message",            // 6: The message         <String>
END_SLOTTABLE(MyObj)
// map attributes to slots
BEGIN_SLOT_MAP(MyObj)
  ON_SLOT(1, setSlotColorTable, Basic::PairStream)
  ON_SLOT(2, setSlotTextColor, Basic::Identifier)
  ON_SLOT(3, setSlotBackColor, Basic::Identifier)
  ON_SLOT(4, setSlotVector, Basic::List)
  ON_SLOT(5, setSlotVisible, Basic::Number)
  ON_SLOT(6, setSlotMessage, Basic::String)
END_SLOT_MAP()
// nothing to serialize
EMPTY_SERIALIZER(MyObj)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MyObj::MyObj(void)
{
  STANDARD_CONSTRUCTOR()
  colorTable = nullptr;
  textColor = nullptr;
  backColor = nullptr;
  vector = nullptr;
  message = nullptr;
  visible = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void MyObj::copyData(const MyObj& org, const bool cc)
{
  BaseClass::copyData(org);
  if (cc) {
    colorTable = nullptr;
    textColor = nullptr;
    backColor = nullptr;
    vector = nullptr;
    message = nullptr;
  }

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

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void MyObj::deleteData()
{
  setColorTable(nullptr);
  setTextColor(nullptr);
  setBackColor(nullptr);
  setVector(nullptr);
  setMessage(nullptr);
}

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------
bool MyObj::setColorTable(const Basic::PairStream* const x)
{
  if (colorTable != nullptr) colorTable->unref();
  colorTable = x;
  if (colorTable != nullptr) colorTable->ref();
  return true;
}

const Basic::PairStream* MyObj::getColorTable(void) const
{
  return colorTable;
}

bool MyObj::setTextColor(const Basic::Identifier* const x)
{
  if (textColor != nullptr) textColor->unref();
  textColor = x;
  if (textColor != nullptr) textColor->ref();
  return true;
}

const Basic::Identifier* MyObj::getTextColor(void) const
{
  return textColor;
}

bool MyObj::setBackColor(const Basic::Identifier* const x)
{
  if (backColor != nullptr) backColor->unref();
  backColor = x;
  if (backColor != nullptr) backColor->ref();
  return true;
}

const Basic::Identifier* MyObj::getBackColor(void) const
{
  return backColor;
}

bool MyObj::setVector(const Basic::List* const x)
{
  if (vector != nullptr) vector->unref();
  vector = x;
  if (vector != nullptr) vector->ref();
  return true;
}

const Basic::List* MyObj::getVector(void) const
{
  return vector;
}

bool MyObj::setVisible(const bool x)
{
  visible = x;
  return true;
}

bool MyObj::getVisible(void) const
{
  return visible;
}

bool MyObj::setMessage(const Basic::String* const x)
{
  if (message != nullptr) message->unref();
  message = x;
  if (message != nullptr) message->ref();
  return true;
}

const Basic::String* MyObj::getMessage(void) const
{
  return message;
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
Basic::Object* MyObj::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

bool MyObj::setSlotColorTable(const Basic::PairStream* const x)
{
  bool ok = false;
  if(x != nullptr) {
    ok = setColorTable(x);
  }
  return ok;
}

bool MyObj::setSlotTextColor(const Basic::Identifier* const x)
{
  bool ok = false;
  if(x != nullptr) {
    ok = setTextColor(x);
  }
  return ok;
}

bool MyObj::setSlotBackColor(const Basic::Identifier* const x)
{
  bool ok = false;
  if(x != nullptr) {
    ok = setBackColor(x);
  }
  return ok;
}

bool MyObj::setSlotVector(const Basic::List* const x)
{
  bool ok = false;
  if(x != nullptr) {
    ok = setVector(x);
  }
  return ok;
}

bool MyObj::setSlotVisible(const Basic::Number* const x)
{
  bool ok = false;
  if(x != nullptr) {
    ok = setVisible(x->getBoolean());
  }
  return ok;
}

bool MyObj::setSlotMessage(const Basic::String* const x)
{
  bool ok = false;
  if(x != nullptr) {
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

} // namespace Tutorial
} // namespace Eaagles
