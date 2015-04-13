//------------------------------------------------------------------------------
// Class: TestObject
// Description: A very simple object class that will hold basic information, and
// will be passed from a parent to ObjectHandler via send commands, and the
// ObjectHandler will extract the data and send it to the output.  This tests
// the send command passing objects.
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TestObject_H__
#define __Eaagles_Test_TestObject_H__

#include "openeaagles/basic/Object.h"

// disable all deprecation warnings for now, until we fix
// they are quite annoying to see over and over again...
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Test {

class TestObject : public Basic::Object
{
   DECLARE_SUBCLASS(TestObject,Basic::Object)

public:
   TestObject();

    // set functions
    void setBoolean(const bool x)       { boolVal = x;   }
    void setInteger(const int x)        { intVal = x;    }
    void setFloat(const float x)        { floatVal = x;  }
    void setDouble(const double x)      { doubleVal = x; }
    void setReal(const LCreal x)        { realVal = x;   }
    void setChar(const char* x)         { lcStrcpy(charVal, sizeof(charVal), x); }

    // get functions
    bool getBoolean()                   { return boolVal;   }
    int getInteger()                    { return intVal;    }
    float getFloat()                    { return floatVal;  }
    double getDouble()                  { return doubleVal; }
    LCreal getReal()                    { return realVal;   }
    const char* getChar()               { return charVal;   }

private:
    bool boolVal;
    int intVal;
    float floatVal;
    double doubleVal;
    LCreal realVal;
    char charVal[10];
};

} // End Test namespace
} // End Eaagles namespace

#endif
