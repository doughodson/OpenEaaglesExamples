//------------------------------------------------------------------------------
// Class: MyObj
// Description: example class
//------------------------------------------------------------------------------

#ifndef __oe_tutorial_MyObj_H__
#define __oe_tutorial_MyObj_H__

#include "openeaagles/base/Object.h"

namespace oe {

namespace base { class PairStream; class List; class String;
                  class Number; class Identifier; }

namespace tutorial {

class MyObj : public base::Object
{
  DECLARE_SUBCLASS(MyObj, base::Object)

public:
  MyObj();

  // data access functions
  bool setColorTable(const base::PairStream* const);
  const base::PairStream* getColorTable(void) const;
  bool setTextColor(const base::Identifier* const);
  const base::Identifier* getTextColor(void) const;
  bool setBackColor(const base::Identifier* const);
  const base::Identifier* getBackColor(void) const;

  bool setVector(const base::List* const);
  const base::List* getVector(void) const;

  bool setVisible(bool);
  bool getVisible() const;

  bool setMessage(const base::String* const);
  const base::String* getMessage(void) const;

  // slot table functions
  bool setSlotColorTable(const base::PairStream* const);
  bool setSlotTextColor(const base::Identifier* const x);
  bool setSlotBackColor(const base::Identifier* const x);

  bool setSlotVector(const base::List* const);
  bool setSlotVisible(const base::Number* const);
  bool setSlotMessage(const base::String* const);

  virtual bool isValid() const override;

private:
  const base::PairStream* colorTable;
  const base::Identifier* textColor;
  const base::Identifier* backColor;
  const base::List* vector;
  const base::String* message;
  bool visible;
};

}
}

#endif
