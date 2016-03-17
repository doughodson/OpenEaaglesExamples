//------------------------------------------------------------------------------
// Class: TestObject
// Description: A very simple object class that will hold basic information, and
// will be passed from a parent to ObjectHandler via send commands, and the
// ObjectHandler will extract the data and send it to the output.  This tests
// the send command passing objects.
//------------------------------------------------------------------------------
#ifndef __oe_test_TestObject_H__
#define __oe_test_TestObject_H__

#include "openeaagles/base/Object.h"
#include "openeaagles/base/util/str_utils.h"

// disable all deprecation warnings for now, until we fix
// they are quite annoying to see over and over again...
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace oe {
namespace test {

class TestObject : public base::Object
{
   DECLARE_SUBCLASS(TestObject,base::Object)

public:
   TestObject();

    // set functions
    void setBoolean(const bool x)       { boolVal = x;   }
    void setInteger(const int x)        { intVal = x;    }
    void setFloat(const float x)        { floatVal = x;  }
    void setDouble(const double x)      { doubleVal = x; }
    void setReal(const double x)        { realVal = x;   }
    void setChar(const char* x)         { base::utStrcpy(charVal, sizeof(charVal), x); }

    // get functions
    bool getBoolean()                   { return boolVal;   }
    int getInteger()                    { return intVal;    }
    float getFloat()                    { return floatVal;  }
    double getDouble()                  { return doubleVal; }
    double getReal()                    { return realVal;   }
    const char* getChar()               { return charVal;   }

private:
    bool boolVal;
    int intVal;
    float floatVal;
    double doubleVal;
    double realVal;
    char charVal[10];
};

} // End test namespace
} // End oe namespace

#endif
