//------------------------------------------------------------------------------
// Class: MyObj
// Description: example class
//------------------------------------------------------------------------------

#ifndef __Eaagles_Tutorial_MyObj_H__
#define __Eaagles_Tutorial_MyObj_H__

#include "openeaagles/basic/Object.h"

namespace Eaagles {

namespace Basic { class PairStream; class List; class String;
                  class Number; class Identifier; }

namespace Tutorial {

class MyObj : public Basic::Object
{
  DECLARE_SUBCLASS(MyObj, Basic::Object)

public:
  MyObj();

  // data access functions
  bool setColorTable(const Basic::PairStream* const);
  const Basic::PairStream* getColorTable(void) const;
  bool setTextColor(const Basic::Identifier* const);
  const Basic::Identifier* getTextColor(void) const;
  bool setBackColor(const Basic::Identifier* const);
  const Basic::Identifier* getBackColor(void) const;

  bool setVector(const Basic::List* const);
  const Basic::List* getVector(void) const;

  bool setVisible(bool);
  bool getVisible() const;

  bool setMessage(const Basic::String* const);
  const Basic::String* getMessage(void) const;

  // slot table functions
  bool setSlotColorTable(const Basic::PairStream* const);
  bool setSlotTextColor(const Basic::Identifier* const x);
  bool setSlotBackColor(const Basic::Identifier* const x);

  bool setSlotVector(const Basic::List* const);
  bool setSlotVisible(const Basic::Number* const);
  bool setSlotMessage(const Basic::String* const);

   bool isValid() const override;

private:
  const Basic::PairStream* colorTable;
  const Basic::Identifier* textColor;
  const Basic::Identifier* backColor;
  const Basic::List* vector;
  const Basic::String* message;
  bool visible;
};

} // namespace Tutorial
} // namespace Eaagles

#endif
