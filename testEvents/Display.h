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

   virtual void updateData(const double dt = 0.0) override;

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

    // double
    double myDouble;
    SendData doubleSD;

    // object
    TestObject* obj;
    SendData objSD;

    char myChar[10];
    SendData charSD;

    base::Color* myColor;
    SendData colorSD;

    static const int MAX_MATERIALS = 3;
    graphics::Material* materials[MAX_MATERIALS];
    SendData materialSD[MAX_MATERIALS];
    osg::Vec3 diffColorRate[MAX_MATERIALS];

    double rotations[MAX_MATERIALS];
    SendData rotationsSD[MAX_MATERIALS];

    int counter;    // to slowly increment our numbers
};

}
}

#endif
