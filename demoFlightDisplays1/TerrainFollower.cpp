//------------------------------------------------------------------------------
// Class: TerrainFollower
//------------------------------------------------------------------------------

#define TEST_ONE
//#define TEST_ALT

#include "TerrainFollower.h"
#include "openeaagles/basic/Number.h"
#include <GL/glu.h>

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TerrainFollower, "TerrainFollower")
EMPTY_SERIALIZER(TerrainFollower)

// Event handler
BEGIN_EVENT_HANDLER(TerrainFollower)
    ON_EVENT_OBJ(UPDATE_VALUE, onEventSetPlaneAltTerrainFollower, Basic::Number)
    ON_EVENT_OBJ(UPDATE_VALUE2, onEventSetScanRangeTerrainFollower, Basic::Number)
    ON_EVENT_OBJ(UPDATE_VALUE3, onEventSetViewHeightTerrainFollower, Basic::Number)
    ON_EVENT_OBJ(UPDATE_VALUE4, onEventSetViewWidthTerrainFollower, Basic::Number)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TerrainFollower::TerrainFollower()
{
    STANDARD_CONSTRUCTOR()
    
    numElevPts = 89;
    //LCreal elev = 500;
    // fill our elevation points with test data right now
    /*
    for (int i = 0; i < numElevPts; i++) {
        elevPts[i] = elev;
        if (i > numElevPts / 2) elev -= 0.1;
        else elev += 0.5;
    }
    */
    
    elevPts[0] = 750;
    elevPts[1] = 790;
    elevPts[2] = 800;
    elevPts[3] = 790;
    elevPts[4] = 790;
    elevPts[5] = 540;
    elevPts[6] = 550;
    elevPts[7] = 620;
    elevPts[8] = 625;
    elevPts[9] = 550;
    elevPts[10] = 553;
    elevPts[11] = 800;
    elevPts[12] = 820;
    elevPts[13] = 800;
    elevPts[14] = 800;
    elevPts[15] = 780;
    elevPts[16] = 760;
    elevPts[17] = 720;
    elevPts[18] = 690;
    elevPts[19] = 680;
    elevPts[20] = 650;
    elevPts[21] = 630;
    elevPts[22] = 600;
    elevPts[23] = 570;
    elevPts[24] = 590;
    elevPts[25] = 600;
    elevPts[26] = 600;
    elevPts[27] = 550;
    elevPts[28] = 545;
    elevPts[29] = 570;
    elevPts[30] = 590;
    elevPts[31] = 600;
    elevPts[32] = 620;
    elevPts[33] = 640;
    elevPts[34] = 665;
    elevPts[35] = 685;
    elevPts[36] = 690;
    elevPts[37] = 720;
    elevPts[38] = 725;
    elevPts[39] = 730;
    elevPts[40] = 750;
    elevPts[41] = 780;
    elevPts[42] = 790;
    elevPts[43] = 810;
    elevPts[44] = 820;
    elevPts[45] = 850;
    elevPts[46] = 880;
    elevPts[47] = 900;
    elevPts[48] = 900;
    elevPts[49] = 890;
    elevPts[50] = 870;
    elevPts[51] = 865;
    elevPts[52] = 855;
    elevPts[53] = 835;
    elevPts[54] = 820;
    elevPts[55] = 810;
    elevPts[56] = 800;
    elevPts[57] = 790;
    elevPts[58] = 785;
    elevPts[59] = 780;
    elevPts[60] = 780;
    elevPts[61] = 760;
    elevPts[62] = 745;
    elevPts[63] = 735;
    elevPts[64] = 725;
    elevPts[65] = 720;
    elevPts[66] = 705;
    elevPts[67] = 700;
    elevPts[68] = 685;
    elevPts[69] = 665;
    elevPts[70] = 650;
    elevPts[71] = 640;
    elevPts[72] = 632;
    elevPts[73] = 620;
    elevPts[74] = 600;
    elevPts[75] = 590;
    elevPts[76] = 580;
    elevPts[77] = 580;
    elevPts[78] = 590;
    elevPts[79] = 575;
    elevPts[80] = 570;
    elevPts[81] = 560;
    elevPts[82] = 555;
    elevPts[83] = 553;
    elevPts[84] = 570;
    elevPts[85] = 590;
    elevPts[86] = 630;
    elevPts[87] = 650;
    elevPts[88] = 690;
    
    range = 10;   
    maxAlt = 1500;       // feet
    minAlt = 100;       // feet
    height = 1.8f;       // inches
    width = 4.3f;        // inches
    rScale = 0;       
    aScale = 0;         
    planeAlt = 800;
    midAltSD.empty();
    maxAltSD.empty();
    firstRSD.empty();
    secRSD.empty();
    tRSD.empty();
    fRSD.empty();
    aboveTerr = 500;
    
    // test
    testPA = 500;
    timer = 0;
    timerRate = 0.5f;
}


//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void TerrainFollower::copyData(const TerrainFollower& org, const bool)
{
    // always copy baseclass stuff FIRST
    BaseClass::copyData(org);
    numElevPts = org.numElevPts;
    
    for (int i = 0; i < numElevPts; i++) elevPts[i] = org.elevPts[i];
    range = org.range;   
    maxAlt = org.maxAlt;
    minAlt = org.minAlt;
    height = org.height;
    width = org.width;
    rScale = org.rScale;
    aScale = org.aScale;
    planeAlt = org.planeAlt;
    midAltSD.empty();
    maxAltSD.empty();
    firstRSD.empty();
    secRSD.empty();
    tRSD.empty();
    fRSD.empty();
    aboveTerr = org.aboveTerr;
    
    // test
    testPA = org.testPA;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void TerrainFollower::deleteData()
{
}

//------------------------------------------------------------------------------
// testElevPoints() - shifts all the points to the left
//------------------------------------------------------------------------------
void TerrainFollower::testElevPoints()
{
    //LCreal last = 0;
    LCreal first = 0;
    // get first and last values
    first = elevPts[0];

    for (int i = 0; i < numElevPts; i++) {
        if (i == numElevPts - 1) elevPts[i] = first;
        else elevPts[i] = elevPts[i+1];
    }
    
}

// set functions
bool TerrainFollower::setPlaneAlt(const LCreal newAlt) 
{ 
    planeAlt = newAlt; 
    return true; 
}
bool TerrainFollower::setScanRange(const LCreal newR)  
{   
    range = newR; 
    return true; 
}
bool TerrainFollower::setViewHeight(const LCreal newH) 
{ 
    height = newH; 
    return true; 
}
bool TerrainFollower::setViewWidth(const LCreal newW)  
{ 
    width = newW; 
    return true; 
}    
bool TerrainFollower::setElevPts(const int num, const LCreal newEPts[])
{
    bool ok = false;
    if (num <= MAX_POINTS) {
        for (int i = 0; i < num; i++) {
            elevPts[i] = newEPts[i];
        }
        numElevPts = num;
    }
    return ok;
}

// Event functions
bool TerrainFollower::onEventSetPlaneAltTerrainFollower(const Basic::Number* const x)
{
    bool ok = false;
    if (x != 0) ok = setPlaneAlt(x->getReal());
    return ok;
}
bool TerrainFollower::onEventSetScanRangeTerrainFollower(const Basic::Number* const x)
{
    bool ok = false;
    if (x != 0) ok = setScanRange(x->getReal());
    return ok;
}
bool TerrainFollower::onEventSetViewHeightTerrainFollower(const Basic::Number* const x)
{
    bool ok = false;
    if (x != 0) ok = setViewHeight(x->getReal());
    return ok;
}
bool TerrainFollower::onEventSetViewWidthTerrainFollower(const Basic::Number* const x)
{
    bool ok = false;
    if (x != 0) ok = setViewWidth(x->getReal());
    return ok;
}

//------------------------------------------------------------------------------
// drawFunc() -- draws the object(s)
//------------------------------------------------------------------------------
void TerrainFollower::drawFunc()
{       
    GLfloat ocolor[4];
    GLfloat lw;
    glGetFloatv(GL_CURRENT_COLOR, ocolor);
    glGetFloatv(GL_LINE_WIDTH, &lw);
    
    // initialize local variables
    LCreal temp = 1.4f;
    LCreal moveY = 0;
    LCreal moveYNext = 0;
    //LCreal lastMoveY = 0;
    LCreal start = 0.2f;
    
    
    glColor3f(1, 1, 0);
    moveY = (planeAlt - minAlt) * aScale;
    // draw the plane outline
    glPushMatrix();
        // translate to the proper position
        glTranslatef( GLfloat(temp), GLfloat(moveY + start), 0);
        glLineWidth(4);   
        glBegin(GL_LINES);
            glVertex2f(0, 0);
            glVertex2f(0.4f, 0);
        glEnd();
        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
            glVertex2f(0, 0);
            glVertex2f(0, 0.1f);
            glVertex2f(0.1f, 0);
        glEnd();
    glPopMatrix();

    
    temp = 0;
    glColor3f(0.596f, 0.4f, 0.208f);
    glLineWidth(2);
    
    // make a series of polygons that will allow the terrain to be displayed
    glPushMatrix();
        glTranslatef(1.6f, GLfloat(start), 0);
        for (int i = 0; i < numElevPts; i++) {
            glBegin(GL_POLYGON);
                moveY = (elevPts[i] - minAlt) * aScale;
                if (moveY > height) moveY = height;
                if (i != numElevPts - 1) moveYNext = (elevPts[i +1] - minAlt) * aScale;
                else moveYNext = 0;
                if (moveYNext > height) moveYNext = height;
                lcVertex2(temp, 0);
                lcVertex2(temp, moveY);
                lcVertex2(temp + rScale, moveYNext);
                lcVertex2(temp + rScale, 0);
                temp += rScale;
            glEnd();
        }
    glPopMatrix();
        
    temp = 0;
    // now we draw the flight path line, using an average factor for determining the slope of the line
    glColor3f(0, 1, 1);
    glPushMatrix();
        glTranslatef(1.6f, GLfloat(start), 0);
        LCreal myAvg = 0;
        LCreal mySum = 0;
        // make a line strip that follows the terrain
        glBegin(GL_LINE_STRIP);
            // this draws every point
            for (int i = 0; i < numElevPts; i++) {    
            
                // average our six values
                int myPlace = (numElevPts - (i +1));
                if (myPlace >= 6) {
                    mySum = (elevPts[i] + elevPts[i+1] + elevPts[i+2] + elevPts[i+3] + elevPts[i+4] + elevPts[i+5] + elevPts[i+6]);
                    myAvg = mySum / 7;
                }
                else if ( myPlace >= 5) {
                    mySum = (elevPts[i] + elevPts[i+1] + elevPts[i+2] + elevPts[i+3] + elevPts[i+4] + elevPts[i+5]);
                    myAvg = mySum / 6;
                }
                else if ( myPlace >= 4) {
                    mySum = (elevPts[i] + elevPts[i+1] + elevPts[i+2] + elevPts[i+3] + elevPts[i+4]);
                    myAvg = mySum / 5;
                }               
                else if ( myPlace >= 3) {
                    mySum = (elevPts[i] + elevPts[i+1] + elevPts[i+2] + elevPts[i+3]);
                    myAvg = mySum / 4;
                }       
                else if (myPlace >= 2) {
                    mySum = (elevPts[i] + elevPts[i+1] + elevPts[i+2]);
                    myAvg = mySum / 3;
                }       
                else if (myPlace >= 1) {
                    mySum = (elevPts[i] + elevPts[i+1]);
                    myAvg = mySum / 2;
                }
                else myAvg = elevPts[i];
                         
                // make sure our moveY is above our terrain average
                myAvg = ((myAvg + aboveTerr) - minAlt) * aScale;
                lcVertex2(temp, myAvg);
                temp += rScale;
            }           
        glEnd();
    glPopMatrix();
        
    glLineWidth(lw);
    glColor4fv(ocolor);
}

//------------------------------------------------------------------------------
// updateData() -- update non time-critical threads here
//------------------------------------------------------------------------------
void TerrainFollower::updateData(const LCreal dt)
{
    // update our Baseclass first
    BaseClass::updateData(dt);

#ifdef TEST_ALT


    planeAlt += testPA * dt;
    if (planeAlt > 50000) {
        planeAlt = 50000;
        testPA = -testPA;
    }
    if (planeAlt < 0) {
        planeAlt = 0;
        testPA = -testPA;
    }
#endif

#ifdef TEST_ONE 
    // run this test right now
    timer += timerRate * dt;
    if (timer > 0.1) {
        testElevPoints();
        timer = 0;
    }
#endif
 
    // determine our min and max ranges from the plane altitude (add and subtract 2000)
    // always start from 0 feet 
    minAlt = 0;
    if (planeAlt > 20000) maxAlt = 50000;
    else if (planeAlt > 18000) maxAlt = 20000;
    else if (planeAlt > 16000) maxAlt = 18000;
    else if (planeAlt > 14000) maxAlt = 16000;
    else if (planeAlt > 12000) maxAlt = 14000;
    else if (planeAlt > 10000) maxAlt = 12000;
    else if (planeAlt > 8000) maxAlt = 10000;
    else if (planeAlt > 6000) maxAlt = 8000;
    else if (planeAlt > 4000) maxAlt = 6000;
    else if (planeAlt > 2000) maxAlt = 4000;
    else if (planeAlt > 0) maxAlt = 2000;
    
    // figure our altitude scale
    // get our range of altitude in feet
    LCreal temp = maxAlt - minAlt;
    if (temp != 0 && temp > 0) { 
        // divide by the number of inches to give us a inches/feet
        aScale = height / temp;
    }
    if (numElevPts > 0) {
        // figure our range scale 
        rScale = width / numElevPts;
    }
    
   
    LCreal tempR = 0.75f * range;
    send("thirdr", UPDATE_VALUE, tempR, tRSD);
    tempR = range/4;
    send("firstr", UPDATE_VALUE, tempR, firstRSD);
    tempR = range/2;
    send("secondr", UPDATE_VALUE, tempR, secRSD);
    
    // send our alt values out
    send("middlealt", UPDATE_VALUE, maxAlt/2, midAltSD);
    send("maxalt", UPDATE_VALUE, maxAlt, maxAltSD);
    // send our range values out
    send("fourthr", UPDATE_VALUE, range, fRSD);
}

}; // end of Demo namespace
}; // end of Eaagles namespace

