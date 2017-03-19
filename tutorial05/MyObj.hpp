
#ifndef __MyObj_H__
#define __MyObj_H__

#include "openeaagles/base/Object.hpp"

namespace oe {
namespace base { class PairStream; class List; class String; class Number; class Identifier; }
}

//------------------------------------------------------------------------------
// Class: MyObj
// Description: example class
//------------------------------------------------------------------------------
class MyObj : public oe::base::Object
{
  DECLARE_SUBCLASS(MyObj, oe::base::Object)

public:
  MyObj();

  // data access functions
  bool setColorTable(const oe::base::PairStream* const);
  const oe::base::PairStream* getColorTable() const;
  bool setTextColor(const oe::base::Identifier* const);
  const oe::base::Identifier* getTextColor() const;
  bool setBackColor(const oe::base::Identifier* const);
  const oe::base::Identifier* getBackColor() const;

  bool setVector(const oe::base::List* const);
  const oe::base::List* getVector() const;

  bool setVisible(bool);
  bool getVisible() const;

  bool setMessage(const oe::base::String* const);
  const oe::base::String* getMessage() const;

  // slot table functions
  bool setSlotColorTable(const oe::base::PairStream* const);
  bool setSlotTextColor(const oe::base::Identifier* const x);
  bool setSlotBackColor(const oe::base::Identifier* const x);

  bool setSlotVector(const oe::base::List* const);
  bool setSlotVisible(const oe::base::Number* const);
  bool setSlotMessage(const oe::base::String* const);

  virtual bool isValid() const override;

private:
  const oe::base::PairStream* colorTable {};
  const oe::base::Identifier* textColor {};
  const oe::base::Identifier* backColor {};
  const oe::base::List* vector {};
  const oe::base::String* message {};
  bool visible {};
};

#endif
