
#ifndef __Uniform_H__
#define __Uniform_H__

#include "Random.hpp"

namespace oe {
namespace base   { class Number; }
}

//------------------------------------------------------------------------------
// Class: Uniform
// Description: Generates Random Numbers
//------------------------------------------------------------------------------
class Uniform : public Random
{
   DECLARE_SUBCLASS(Uniform, Random)

public:
   Uniform();

   // data access functions
   void setMax(const int);
   void setMin(const int);

   // slot table functions
   bool setSlotMax(const oe::base::Number* const);
   bool setSlotMin(const oe::base::Number* const);

   virtual int getNum() const override;

private:
   int min {};
   int max {1};
};

#endif
