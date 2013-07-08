//*****************************************************************************
// Example routine for the basicGL and basic framework
//*****************************************************************************

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/basicGL/SymbolLoader.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basicGL/Readouts.h"
#include "openeaagles/basic/basicFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

#include <fstream>

#include "openeaagles/maps/vpfMap/VPFTable.h"
#include "openeaagles/maps/vpfMap/VPFRecord.h"
#include "openeaagles/maps/vpfMap/VPFDirectory.h"
#include "openeaagles/maps/vpfMap/VMAP0MainDirectory.h"
#include "openeaagles/maps/mapsFF.h"

namespace Eaagles {    
namespace Maps {
namespace MainVmap {

// Description (input) File -- After being processed by the C preprocessor
const char* testFileName = "test.edl";

// Frame Rate
const int frameRate = 20;

// System descriptions
static class TestDisplay* sys = 0;	

//=============================================================================
// TestDisplay
//=============================================================================
class TestDisplay : public Glut::GlutDisplay
{
    DECLARE_SUBCLASS(TestDisplay, Glut::GlutDisplay)

public:
    TestDisplay();
    
    virtual void drawIt();
    virtual void mouseEvent(const int button, const int state, const int x, const int y);
    virtual void updateData(const LCreal dt = 0.00000);
    void updatePlaceNames();
    void updatePoints();

protected:
    bool setSlotVMAPDir(Vpf::VMAP0MainDirectory* vDir);

private:
    // Select/Pick test
    BasicGL::Graphic* selected;
    //packet test for vector product format level 0
    Vpf::VPFTable tables[2];
    //VPFPacket packet;
    bool start;
    int numVerts;
    int numRecords;
    int numPlaces;
    osg::Vec3 verts[5000];
    Vpf::VMAP0MainDirectory* vpf;
    char placenames[500][100];
};

IMPLEMENT_SUBCLASS(TestDisplay,"TestDisplay")
EMPTY_SERIALIZER(TestDisplay)


BEGIN_SLOTTABLE(TestDisplay)
    "vpfdirectory",          // 1) set our VMAP0MainDirectory object
END_SLOTTABLE(TestDisplay)

// Map slot table to handles 
BEGIN_SLOT_MAP(TestDisplay)
    ON_SLOT(1,setSlotVMAPDir,Vpf::VMAP0MainDirectory)
END_SLOT_MAP()

TestDisplay::TestDisplay()
{
    STANDARD_CONSTRUCTOR()
    selected = 0;
    start = true;
    for (int i = 0; i < 500; i++) {
        verts[i].set(0,0,0);
        *placenames[i] = 0;
    }
    vpf = 0;
    numVerts = 0;
    numRecords = 4;
    numPlaces = 0;
}

bool TestDisplay::setSlotVMAPDir(Vpf::VMAP0MainDirectory* vDir)
{
    if (vpf != 0) vpf->unref();
    vpf = 0;
    if (vDir != 0) {
        vpf = vDir;
        vpf->ref();
    }
    return true;
}

EMPTY_COPYDATA(TestDisplay)
EMPTY_DELETEDATA(TestDisplay)


// drawIt() -- function to display the test
void TestDisplay::drawIt()
{
    BaseClass::drawIt();
    //clear();
    //draw();
    //swapBuffers();
}

void TestDisplay::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);

#if 0
    if (start) {
        if (vpf != 0) {
            // get our reference directory
            Vpf::VMAP0ReferenceDirectory* ref = vpf->getReferenceDir();
            if (ref != 0) {
//                bool ok = true;
                numVerts = 0;
#if 1
                Vpf::VMAP0RefCoverageDirectory* rDir = ref->getCoverage(Vpf::VMAP0ReferenceDirectory::CVG_PLACENAM);
                if (rDir != 0) {
                    //numVerts = rDir->getPlacenameCoordsByRange(20, 20, 39.9276f, -75.2182f, verts, 500);  
                    //updatePoints();

                    //ok = true;
                    //numVerts = 0;
                    //numRecords = 0;
                    //// now get our placenames
                    //for (int i = 0; i < 
                    //    rDir->getPlacenameByRecord(numRecords+1, placenames[numPlaces]);
                    //    //std::cout << "PLACENAME #" <<  numPlaces +1 << " = " << placenames[numPlaces] << std::endl;
                    //    numPlaces++;
                    //    numRecords++;
                    //}
                    //// if we never reached a bad record, back up one
                    //updatePlaceNames();


                    //ok = true;
                    //numVerts = 0;
                    //numRecords = 0;
                    ////// now get our placenames
                    //while (numRecords < 250 && numVerts < 500){
                    //    // let's just get our coordinates first (by record)
                    //    int count = rDir->getPlacenameCoordsByRecord(numRecords+1, verts, numVerts, 500);
                    //    //std::cout << "PLACENAME #" << numVerts+1 << " = " << placenames[numVerts] << std::endl;
                    //    numVerts += count;
                    //    numRecords++;
                    //}
                    //// if we never reached a bad record, back up one
                    //updatePoints();
    #else
                    // we are going to query our components by a lat long and range
                    VMAP0RefCoverageDirectory* rDir = ref->getCoverage(VMAP0ReferenceDirectory::CVG_POLBND);
                    // ok, our placenam coverage directory contains points and their associated names, so let's query them by record first
                    while (numVerts < 500) {
                        float maxLat = 90, maxLon = 180;
                        float minLat = -90, minLon = -180;
                        int x = rDir->getPolBndCoordsByLatLon(maxLat, maxLon, minLat, minLon, numVerts, verts);
                        numVerts += x;
                    }
                    //while (ok && numVerts < 500) {
                        // let's just get our coordinates first (by record)
                        //int x = rDir->getPolBndCoordsByRecord(numRecords+1, verts, numVerts);  
                        
                        // add the number of vertices we recorded
                        //numVerts += x;
                        //numRecords++;
                    //}
                    updatePoints();
    #if 0
                    ok = true;
                    numVerts = 0;
                    // now get our placenames
                    while (ok && numVerts < 300) {
                        // let's just get our coordinates first (by record)
                        ok = rDir->getPlacenameByRecord(numVerts+1, placenames[numVerts]);
                        //std::cout << "PLACENAME #" << numVerts+1 << " = " << placenames[numVerts] << std::endl;
                        //if (numVerts > 0) std::cout << "PLACENAME - 1 #" << numVerts << " = " << placenames[numVerts-1] << std::endl;
                        numVerts++;
                    }
                    // if we never reached a bad record, back up one
                    if (!ok) numVerts--;
                    updatePlaceNames();
    #endif
    #endif
                }
            }
        }
        start = false;
    }
#endif
}

void TestDisplay::updatePlaceNames() 
{
    Basic::Pair* pair = subpage()->findByName("places");
    if (pair != 0) {
        pair->ref();
        BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
        if (myLoader != 0) {
            myLoader->clearLoader();
            for (int i = 0; i < numPlaces; i++) {
                int idx = myLoader->addSymbol(1, placenames[i]);
                myLoader->updateSymbolPositionLL(idx, verts[i].x(), verts[i].y());
                myLoader->updateSymbolText(idx, "name", placenames[i]);
                std::cout << "PUT PLACENAME " << placenames[i] << " into position " << verts[i].x() << ", " << verts[i].y() << std::endl;
            }
        }
        pair->unref();
    }        
}

void TestDisplay::updatePoints() 
{
    Basic::Pair* pair = subpage()->findByName("points");
    if (pair != 0) {
        pair->ref();
        BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
        if (myLoader != 0) {
            myLoader->clearLoader();
            for (int i = 0; i < numVerts; i++) {
                if (verts[i].y() != 0 && verts[i].x() != 0 && verts[i].z() != 0) {
                    int idx = myLoader->addSymbol(1, placenames[i]);
                    myLoader->updateSymbolPositionLL(idx, verts[i].x(), verts[i].y());
                    std::cout << "COORDINATE = " << verts[i].x() << ", " << verts[i].y() << std::endl;
                }
            }
        }
        pair->unref();
    }        
}


//SLS - last update 3/18/08 
//Now I can query the reference directory for the placenam coverage, and get placenames and coordinates based on a ref lat lon and range
//The next step would be to start querying political boundaries (polbnd) using the indexes they have setup.

// mouseEvent() -- Handle mouse inputs
void TestDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
    setMouse(x,y);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // we just did a pick, let's do a spatial query on it, based on our lat and lon
        BasicGL::MapPage* page = (BasicGL::MapPage*)subpage();
        if (page != 0) {
            double refLat = page->getReferenceLatDeg();
            double refLon = page->getReferenceLonDeg();
            double mapRange = page->getRange();
            // now get our directory and query our index
            if (vpf != 0) {
                // get our reference directory
                Vpf::VMAP0ReferenceDirectory* ref = vpf->getReferenceDir();
                if (ref != 0) {
//                    bool ok = true;
                    numVerts = 0;
                    Vpf::VMAP0RefCoverageDirectory* rDir = ref->getCoverage(Vpf::VMAP0ReferenceDirectory::CVG_PLACENAM);
                    if (rDir != 0) {
                        // query our place name by reference latitutde
                        numVerts = rDir->getPlacenameCoordsByRange((float)mapRange, (float)mapRange, (float)refLat, (float)refLon, verts, 0, 500);
                        // update points
                        updatePoints();
                        // now get our placenames
                        numPlaces = 0;
                        for (int i = 0; i < numVerts; i++) {
                            int primId = rDir->getSpatialQueryPlacenamePrimID(i+1);
                            rDir->getPlacenameByRecord(primId, placenames[numPlaces++]);
                        }
                        updatePlaceNames();
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// getSlotByIndex() for TestDisplay
//------------------------------------------------------------------------------
Basic::Object* TestDisplay::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}


//=============================================================================
// Main test functions
//=============================================================================

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0/double(frameRate);

    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers((LCreal)dt);
    BasicGL::Graphic::flashTimer((LCreal)dt);
    sys->tcFrame((LCreal)dt);
}

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // This test ...
    if ( strcmp(formname, TestDisplay::getFormName()) == 0 ) {
        newform = new TestDisplay;
    }

    if (newform == 0) newform = Maps::mapsFormFunc(formname);
    if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
    if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
    if (newform == 0) newform = Glut::glutFormFunc(formname);
    if (newform == 0) newform = Basic::basicFormFunc(formname);
    
    return newform;
}

// readTest() -- function to the read description files
static void readTest()
{
    // Read the description file
    int errors = 0;
    Basic::Object* q1 = Basic::lcParser(testFileName, testFormFunc, &errors);
    if (errors > 0) {
        std::cerr << "Errors in reading file: " << errors << std::endl;
        exit(1);
    }

    // Set 'sys' to our basic description object.
    sys = 0;
    if (q1 != 0) {

        // When we were given a Pair, get the pointer to its object.
        Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
        if (pp != 0) {
           std::cout << "Form: " << *pp->slot() << std::endl;
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'TestDisplay'.
        sys = dynamic_cast<TestDisplay*>(q1);

    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //sys->serialize(std::cout);
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{

    glutInit(&argc, argv);

// ---
// Read in the description files
// ---
    readTest();

// ---
// Create a display window
// ---
    sys->createWindow();

// ---
// Set timer
// ---
    double dt = 1.0/double(frameRate);
    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

// ---
// Main loop
// ---
    glutMainLoop();

    return 0;
}
    
};  // end MainVmap namespace
};  // end Maps namespace
};  // end Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    return Eaagles::Maps::MainVmap::main(argc,argv);
}
