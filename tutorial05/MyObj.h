//------------------------------------------------------------------------------
// Class: MyObj
// Description: example class
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_MyObj_H__
#define __oe_Tutorial_MyObj_H__

#include "openeaagles/basic/Object.h"

namespace oe {

namespace basic { class PairStream; class List; class String;
                  class Number; class Identifier; }

namespace Tutorial {

class MyObj : public basic::Object
{
  DECLARE_SUBCLASS(MyObj, basic::Object)

public:
  MyObj();

  // data access functions
  bool setColorTable(const basic::PairStream* const);
  const basic::PairStream* getColorTable(void) const;
  bool setTextColor(const basic::Identifier* const);
  const basic::Identifier* getTextColor(void) const;
  bool setBackColor(const basic::Identifier* const);
  const basic::Identifier* getBackColor(void) const;

  bool setVector(const basic::List* const);
  const basic::List* getVector(void) const;

  bool setVisible(bool);
  bool getVisible() const;

  bool setMessage(const basic::String* const);
  const basic::String* getMessage(void) const;

  // slot table functions
  bool setSlotColorTable(const basic::PairStream* const);
  bool setSlotTextColor(const basic::Identifier* const x);
  bool setSlotBackColor(const basic::Identifier* const x);

  bool setSlotVector(const basic::List* const);
  bool setSlotVisible(const basic::Number* const);
  bool setSlotMessage(const basic::String* const);

   bool isValid() const override;

private:
  const basic::PairStream* colorTable;
  const basic::Identifier* textColor;
  const basic::Identifier* backColor;
  const basic::List* vector;
  const basic::String* message;
  bool visible;
};

} // namespace Tutorial
} // namespace oe

#endif
