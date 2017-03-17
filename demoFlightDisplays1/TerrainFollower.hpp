
#ifndef __TerrainFollower_H__
#define __TerrainFollower_H__

#include "openeaagles/graphics/Graphic.hpp"

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
//      The list of points is sent in as an double array
//------------------------------------------------------------------------------
class TerrainFollower : public oe::graphics::Graphic
{
    DECLARE_SUBCLASS(TerrainFollower, oe::graphics::Graphic)

public:
    TerrainFollower();

    virtual void updateData(const double dt = 0.0) override;
    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

    virtual void drawFunc() override;

    // set functions
    virtual bool setPlaneAlt(const double newAlt);
    virtual bool setScanRange(const double newR);
    virtual bool setViewHeight(const double newH);
    virtual bool setViewWidth(const double newW);
    virtual bool setElevPts(const int num, const double newEPts[]);

    // Simply steps through the points we have
    void testElevPoints();

private:
    static const int MAX_POINTS = 1000; // maximum number of terrain elevation points

    // event functions
    bool onEventSetPlaneAltTerrainFollower(const oe::base::Number* const x);
    bool onEventSetScanRangeTerrainFollower(const oe::base::Number* const x);
    bool onEventSetViewHeightTerrainFollower(const oe::base::Number* const x);
    bool onEventSetViewWidthTerrainFollower(const oe::base::Number* const x);

    double range {10.0};            // our scan range ahead of us
    double maxAlt {1500.0};         // where do we want our max altitude (1)? (feet)
    double minAlt {100.0};          // where do we want our min altitude (0)? (feet)
    int numElevPts {89};            // number of elevation points we are using
    double elevPts[MAX_POINTS] {};  // our elevation points
    double height {1.8};            // height of the viewable area we are using (inches)
    double width {4.3};             // width of the viewable area we are using (inches)
    double rScale {};               // our range scale to use for drawing
    double aScale {};               // our altitude scale to use for drawing
    double planeAlt {800.0};        // what is our aircraft elevation?
    double aboveTerr {500.0};       // how far above the terrain do we want to be?  (default is 500)

    SendData maxAltSD;
    SendData midAltSD;
    SendData firstRSD;
    SendData secRSD;
    SendData tRSD;
    SendData fRSD;

    // test data
    double testPA {500.0};
    double timer {0.0};
    double timerRate {0.5};
};

#endif
