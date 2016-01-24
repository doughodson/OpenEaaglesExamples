//------------------------------------------------------------------------------
// Class: Display
// Description: This class will send down data to it's components in different
// ways, showing how the SendData class works and testing our send commands.
//------------------------------------------------------------------------------
#ifndef __oe_test_Display_H__
#define __oe_test_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
namespace test {

class TestObject;

class Display : public glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, glut::GlutDisplay)

public:
   Display();

    void updateData(const LCreal dt = 0.0) override;

private:
    // boolean
    bool myBool;
    SendData boolSD;

    // Integer
    int myInt;
    SendData intSD;

    // float
    float myFloat;
    SendData floatSD;

    // LCreal
    LCreal myLCreal;
    SendData lcrealSD;

    // double
    double myDouble;
    SendData doubleSD;

    // object
    TestObject* obj;
    SendData objSD;

    char myChar[10];
    SendData charSD;

    basic::Color* myColor;
    SendData colorSD;

    static const int MAX_MATERIALS = 3;
    BasicGL::Material* materials[MAX_MATERIALS];
    SendData materialSD[MAX_MATERIALS];
    osg::Vec3 diffColorRate[MAX_MATERIALS];

    LCreal rotations[MAX_MATERIALS];
    SendData rotationsSD[MAX_MATERIALS];

    int counter;    // to slowly increment our numbers
};

} // End test namespace
} // End oe namespace

#endif
