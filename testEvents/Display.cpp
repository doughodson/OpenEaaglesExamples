//------------------------------------------------------------------------------
// Class: Display
//------------------------------------------------------------------------------
#include "Display.h"
#include "TestObject.h"

#include "openeaagles/basic/Color.h"
#include "openeaagles/basicGL/Material.h"
#include "openeaagles/basic/Rng.h"
#include "openeaagles/basic/Number.h"

// disable all deprecation warnings for now, until we fix
// they are quite annoying to see over and over again...
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Test {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Display, "SendDataDisplay")
EMPTY_SERIALIZER(Display)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Display::Display()
{
    STANDARD_CONSTRUCTOR()
    
    myBool = false;
    boolSD.empty();
    myInt = 0;
    intSD.empty();
    myFloat = 0.0f;
    floatSD.empty();
    myDouble = 0.0;
    doubleSD.empty();
    myLCreal = 0;
    lcrealSD.empty();
    obj = new TestObject();
    lcStrcpy(myChar, sizeof(myChar), "ASCII");
    charSD.empty();
    myColor = new Basic::Color();
    myColor->setRed(0.0f);
    myColor->setBlue(0.0f);
    myColor->setGreen(0.0f);

    // setup a random number generator to start our colors
    Basic::Rng* rng = new Basic::Rng();
    osg::Vec4 diffColor[MAX_MATERIALS];
    // this will get our computer time, and take the result, giving us
    // a random seed to start our generator
    double x = getComputerTime();
    x -= int(x);
    x *= 10;
    int seed = nint((LCreal)x);

    // go through x amount of numbers before we get our next random number
    // this will allow for some pseudo-randomness.
    for (int i = 0; i < seed; i++) rng->drawClosed();

    float startX = 0, startY = 0, startZ = 0;
    for (int i = 0; i < MAX_MATERIALS; i++) {
        materials[i] = new BasicGL::Material();
        materialSD[i].empty();
        diffColor[i].set((LCreal)rng->drawClosed(), (LCreal)rng->drawClosed(), (LCreal)rng->drawClosed(), 1);
        //std::cout << "DIFF COLOR = " << diffColor[i].x() << ", " << diffColor[i].y() << ", " << diffColor[i].z() << std::endl;
        materials[i]->setDiffuseColor(diffColor[i]);
        // set up initial different colors
        diffColorRate[i].set(1,1,1);
        rotations[i] = 0;
        rotationsSD[i].empty();
    }


    rng->unref();
    counter = 0;
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void Display::copyData(const Display& org, const bool cc)
{
    BaseClass::copyData(org);

    if (cc) {
        obj = 0;
        myColor = 0;
        for (int i = 0; i < MAX_MATERIALS; i++) materials[i] = 0;
    }

    myBool = org.myBool;
    boolSD.empty();
    myInt = org.myInt;
    intSD.empty();
    myFloat = org.myFloat;
    floatSD.empty();
    myDouble = org.myDouble;
    doubleSD.empty();
    myLCreal = org.myLCreal;
    lcrealSD.empty();
    if (obj != 0) obj->unref(); 
    if (org.obj != 0) {
        obj = org.obj->clone();
    }
    if (myColor != 0) myColor->unref();
    if (org.myColor != 0) {
        myColor = org.myColor->clone();
    }

    for (int i = 0; i < MAX_MATERIALS; i++) {
        if (materials[i] != 0) {
            materials[i]->unref();
            materials[i] = 0;
        }
        diffColorRate[i] = org.diffColorRate[i];
        if (org.materials[i] != 0) materials[i] = org.materials[i]->clone();
        materialSD[i].empty();
        rotations[i] = org.rotations[i];
        rotationsSD[i].empty();
    }

    lcStrcpy(myChar, sizeof(myChar), org.myChar);

    counter = org.counter;
}

//------------------------------------------------------------------------------
// deleteData()
//------------------------------------------------------------------------------
void Display::deleteData()
{
    if (obj != 0) {
        obj->unref();
        obj = 0;
    }
    if (myColor != 0) {
        myColor->unref();
        myColor = 0;
    }
    for (int i = 0; i < MAX_MATERIALS; i++) {
        if (materials[i] != 0) {
            materials[i]->unref();
            materials[i] = 0;
        }
    }
}

//------------------------------------------------------------------------------
// updateData(dt)
//------------------------------------------------------------------------------
void Display::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);

    counter++;
    if (counter > 1) {
        myBool = !myBool;
    
        myInt++;
        if (myInt > 999) myInt = 0;

        myFloat += 0.002f;
        if (myFloat > 100) myFloat = 0;

        myDouble += 0.00002f;
        if (myDouble > 2) myDouble = 0;    
      
        myLCreal += 0.15f;
        if (myLCreal > 15) myLCreal = 0;

        if (strcmp(myChar, "ASCII") == 0) lcStrcpy(myChar, sizeof(myChar), "TEXT");
        else lcStrcpy(myChar, sizeof(myChar), "ASCII");

        obj->setBoolean(!obj->getBoolean());
        obj->setInteger(obj->getInteger() + 1);
        obj->setFloat(obj->getFloat() + 0.01f);
        obj->setDouble(obj->getDouble() + 0.0003);
        obj->setReal(obj->getReal() + 0.1f);
        if (strcmp(obj->getChar(), "ASCII") == 0) obj->setChar("TEXT");
        else obj->setChar("ASCII");

        if (myColor->red() < 0.9f) myColor->setRed(myColor->red() + dt);
        else myColor->setRed(0.0f);
        if (myColor->blue() < 0.9f) myColor->setBlue(myColor->blue() + (2 * dt));
        else myColor->setBlue(0.0);
        if (myColor->green() < 0.9f) myColor->setGreen(myColor->green() + (3 * dt));
        else myColor->setGreen(0.0);

        // our materials
        osg::Vec4 diff;
        LCreal x = 0, y = 0, z = 0;
        for (int i = 0; i < MAX_MATERIALS; i++) {
            if (materials[i] != 0) {
                if (i == 0) {
                    diff = materials[i]->getDiffuseColor();
                    rotations[i] += 40 * dt;
                }
                else if (i == 1) {
                    diff = materials[i]->getAmbientColor();
                    rotations[i] -= 45 * dt;
                }
                else if (i == 2) {
                    diff = materials[i]->getEmissiveColor();
                    rotations[i] += 30 * dt;
                }
                x = diff.x();
                y = diff.y();
                z = diff.z();
                if (x > 1 || x < 0) diffColorRate[i].x() = -diffColorRate[i].x();
                x += diffColorRate[i].x() * 0.01f;
                if (y > 1 || y < 0) diffColorRate[i].y() = -diffColorRate[i].y();
                y += diffColorRate[i].y() * 0.02f;
                if (z > 1 || z < 0) diffColorRate[i].z() = -diffColorRate[i].z();
                z += diffColorRate[i].z() * 0.025f;
                diff.set(x,y,z,1);
                if (i == 0) materials[i]->setDiffuseColor(diff);
                else if (i == 1) materials[i]->setAmbientColor(diff);
            }
        }

        counter = 0;
    }


    send("boolean", UPDATE_VALUE, myBool, boolSD);
    send("integer", UPDATE_VALUE, myInt, intSD);
    send("float", UPDATE_VALUE, myFloat, floatSD);
    send("double", UPDATE_VALUE, myDouble, doubleSD);
    send("lcreal", UPDATE_VALUE, myLCreal, lcrealSD);
    send("ascii", UPDATE_VALUE, myChar, charSD);
    send("objtest", UPDATE_VALUE, obj, objSD);
    send("colors", SET_COLOR, myColor, colorSD);
    // convert materials to objects real quick, so we can send them down
    Basic::Object* tempMat[MAX_MATERIALS];
    for (int i = 0; i < MAX_MATERIALS; i++) {
        tempMat[i] = (Basic::Object*)materials[i];
    }
    send("matarray%d", SET_MATERIAL, tempMat, materialSD, MAX_MATERIALS);
    // send rotations to our objects as well
    send("rotators%d", UPDATE_VALUE2, rotations, rotationsSD, MAX_MATERIALS);
}


} // End Test namespace
} // End Eaagles namespace
