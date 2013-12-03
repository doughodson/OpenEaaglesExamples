//------------------------------------------------------------------------------
// Class: TerrainFollower
//
// Description: Takes in a series of elevation points and a range, and draws
// a bar graph type representation of those elevation points in relation to the 
// aircraft.
// Inputs:
//      UPDATE_VALUE  -> plane altitude (ft)
//      UPDATE_VALUE2 -> scan range (nm)
//      UPDATE_VALUE3 -> viewable height on screen (inches)
//      UPDATE_VALUE4 -> viewable width on screen (inches
//      The list of points is sent in as an LCreal array 
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TerrainFollower_H__
#define __Eaagles_Demo_TerrainFollower_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Demo {

class TerrainFollower : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TerrainFollower,BasicGL::Graphic)

public:
    TerrainFollower();

    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
    virtual bool event(const int event, Basic::Object* const obj = 0);

    // BasicGL::Graphic interface
    virtual void drawFunc();

    // set functions
    virtual bool setPlaneAlt(const LCreal newAlt);
    virtual bool setScanRange(const LCreal newR);
    virtual bool setViewHeight(const LCreal newH);
    virtual bool setViewWidth(const LCreal newW);
    virtual bool setElevPts(const int num, const LCreal newEPts[]);

    // Simply steps through the points we have
    void testElevPoints();

private:
    // event functions
    bool onEventSetPlaneAltTerrainFollower(const Basic::Number* const x);
    bool onEventSetScanRangeTerrainFollower(const Basic::Number* const x);
    bool onEventSetViewHeightTerrainFollower(const Basic::Number* const x);
    bool onEventSetViewWidthTerrainFollower(const Basic::Number* const x);

    enum { MAX_POINTS = 1000 }; // maximum number of terrain elevation points
    LCreal range;               // our scan range ahead of us
    LCreal maxAlt;              // where do we want our max altitude (1)?
    LCreal minAlt;              // where do we want our min altitude (0)?
    int numElevPts;             // number of elevation points we are using
    LCreal elevPts[MAX_POINTS]; // our elevation points
    LCreal height;              // height of the viewable area we are using
    LCreal width;               // width of the viewable area we are using
    LCreal rScale;              // our range scale to use for drawing
    LCreal aScale;              // our altitude scale to use for drawing
    LCreal planeAlt;            // what is our aircraft elevation?
    LCreal aboveTerr;           // how far above the terrain do we want to be?  (default is 500)

    SendData maxAltSD;
    SendData midAltSD;
    SendData firstRSD;
    SendData secRSD;
    SendData tRSD;
    SendData fRSD;

    // test data
    LCreal testPA;
    LCreal timer;
    LCreal timerRate;
    
};

}; // end of Demo namespace
}; // end of Eaagles namespace

#endif

