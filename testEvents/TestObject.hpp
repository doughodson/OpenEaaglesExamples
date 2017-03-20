
#ifndef __TestObject_H__
#define __TestObject_H__

#include "openeaagles/base/Object.hpp"
#include <string>

//------------------------------------------------------------------------------
// Class: TestObject
// Description: A very simple object class that will hold basic information, and
// will be passed from a parent to ObjectHandler via send commands, and the
// ObjectHandler will extract the data and send it to the output.  This tests
// the send command passing objects.
//------------------------------------------------------------------------------
class TestObject : public oe::base::Object
{
   DECLARE_SUBCLASS(TestObject, oe::base::Object)

public:
   TestObject();

   // set functions
   void setBoolean(const bool x)       { boolVal = x;      }
   void setInteger(const int x)        { intVal = x;       }
   void setFloat(const float x)        { floatVal = x;     }
   void setDouble(const double x)      { doubleVal = x;    }
   void setReal(const double x)        { realVal = x;      }
   void setChar(const std::string& x)  { charVal = x;      }

   // get functions
   bool getBoolean()                   { return boolVal;   }
   int getInteger()                    { return intVal;    }
   float getFloat()                    { return floatVal;  }
   double getDouble()                  { return doubleVal; }
   double getReal()                    { return realVal;   }
   const std::string& getChar()        { return charVal;   }

private:
   bool boolVal {};
   int intVal {};
   float floatVal {};
   double doubleVal {};
   double realVal {};
   std::string charVal = "ASCII";
};

#endif
