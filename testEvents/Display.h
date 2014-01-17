//------------------------------------------------------------------------------
// Class: Display
// Description: This class will send down data to it's components in different
// ways, showing how the SendData class works and testing our send commands.
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_Display_H__
#define __Eaagles_Test_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
namespace Test {

class TestObject;

class Display : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, Glut::GlutDisplay)

public:
   Display();

    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0.000000);


private:
    // here is our data and send datas

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

    Basic::Color* myColor;
    SendData colorSD;

    static const int MAX_MATERIALS = 3;
    BasicGL::Material* materials[MAX_MATERIALS];
    SendData materialSD[MAX_MATERIALS];
    osg::Vec3 diffColorRate[MAX_MATERIALS];

    LCreal rotations[MAX_MATERIALS];
    SendData rotationsSD[MAX_MATERIALS];

    int counter;    // to slowly increment our numbers
};

} // End Test namespace
} // End Eaagles namespace

#endif
