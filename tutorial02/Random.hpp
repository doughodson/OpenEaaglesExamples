
#ifndef __Random_H__
#define __Random_H__

#include "openeaagles/base/Object.hpp"

//------------------------------------------------------------------------------
// Class: Random
// Description: Generates random numbers
//------------------------------------------------------------------------------
class Random : public oe::base::Object
{
   DECLARE_SUBCLASS(Random, oe::base::Object)

public:
   Random();

   int getNum() const;
   void setSeed(const unsigned int);
};

#endif
