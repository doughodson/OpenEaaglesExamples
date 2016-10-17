
#ifndef __Random_H__
#define __Random_H__

#include "openeaagles/base/Object.hpp"

namespace oe {
namespace base { class Number; }
}

//------------------------------------------------------------------------------
// Class: Random
// Description: Generates Random Numbers
//------------------------------------------------------------------------------
class Random : public oe::base::Object
{
   DECLARE_SUBCLASS(Random, oe::base::Object)

public:
   Random();

   // data access functions
   virtual int getNum() const = 0;
   bool setSeed(const unsigned int);

   // slot table functions
   bool setSlotSeed(const oe::base::Number* const);

};

#endif
