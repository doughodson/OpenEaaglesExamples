
#ifndef __Display_H__
#define __Display_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

namespace oe {
   namespace base { class Color; }
   namespace graphics { class Material; }
}

class TestObject;

//------------------------------------------------------------------------------
// Class: Display
// Description: This class will send down data to it's components in different
// ways, showing how the SendData class works and testing our send commands.
//------------------------------------------------------------------------------
class Display : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, oe::glut::GlutDisplay)

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

    oe::base::Color* myColor;
    SendData colorSD;

    static const int MAX_MATERIALS = 3;
    oe::graphics::Material* materials[MAX_MATERIALS];
    SendData materialSD[MAX_MATERIALS];
    oe::osg::Vec3 diffColorRate[MAX_MATERIALS];

    double rotations[MAX_MATERIALS];
    SendData rotationsSD[MAX_MATERIALS];

    int counter;    // to slowly increment our numbers
};

#endif
