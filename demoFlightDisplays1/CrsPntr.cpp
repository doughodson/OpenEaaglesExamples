#include "CrsPntr.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_SUBCLASS(CrsPntr, "CrsPntr")
EMPTY_SERIALIZER(CrsPntr)

// Event handler
BEGIN_EVENT_HANDLER(CrsPntr)
    ON_EVENT_OBJ(UPDATE_VALUE7, onUpdateCdiDotsCrsPntr, Basic::Number)
    ON_EVENT_OBJ(UPDATE_VALUE8, onUpdateToFromCrsPntr, Basic::Number)
END_EVENT_HANDLER()

BEGIN_SLOTTABLE(CrsPntr)
    "numDots",      // number of dots to use
    "numInches",    // how many inches to use for the cdi scale
    "showCdi",      // do we display the cdi?
    "showCrsPntr",  // show to course pointer?
    "showToFrom",   // show our to from pointer?
END_SLOTTABLE(CrsPntr)

//------------------------------------------------------------------------------
//  Map slot table
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(CrsPntr)
    ON_SLOT(1, setSlotNumCdiDots, Basic::Number)
    ON_SLOT(2, setSlotNumInches, Basic::Number)
    ON_SLOT(3, setSlotShowCdi, Basic::Number)
    ON_SLOT(4, setSlotShowCrsPntr, Basic::Number)
    ON_SLOT(5, setSlotShowToFrom, Basic::Number)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
CrsPntr::CrsPntr()
{
    STANDARD_CONSTRUCTOR()
    cdiDots = 0.0;
    toFrom = 0.0;     // assume going to for now
    numDots = 4;
    inchesPerDot = 0.0;
    inches = 1.76;  // default
    showCdi = true;
    showCrsPtr = true;
    showToFrom = true;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void CrsPntr::copyData(const CrsPntr& org, const bool)
{
    BaseClass::copyData(org);
    cdiDots = org.cdiDots;
    toFrom = org.toFrom;
    numDots = org.numDots;
    inchesPerDot = org.inchesPerDot;
    inches = org.inches;
    showCdi = org.showCdi;
    showCrsPtr = org.showCrsPtr;
    showToFrom = org.showToFrom;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void CrsPntr::deleteData()
{
}

//------------------------------------------------------------------------------
// set functions
//------------------------------------------------------------------------------
bool CrsPntr::setCdiDots(const LCreal newCDD)
{
    cdiDots = newCDD;
    return true;
}

bool CrsPntr::setNumCdiDots(const int newNCD)
{
    if (newNCD != 0) numDots = newNCD;
    return true;
}

bool CrsPntr::setNumInches(const LCreal newNI)
{
    inches = newNI;
    return true;
}

bool CrsPntr::setShowCdi(const bool newSCDI)
{
    showCdi = newSCDI;
    return true;
}

bool CrsPntr::setShowCrsPntr(const bool newSCP)
{
    showCrsPtr = newSCP;
    return true;
}

bool CrsPntr::setToFrom(const LCreal newTF)
{
    toFrom = newTF;
    return true;
}
bool CrsPntr::setShowToFrom(const bool newTF)
{
    showToFrom = newTF;
    return true;
}

// Event functions
bool CrsPntr::onUpdateCdiDotsCrsPntr(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setCdiDots(x->getReal());
    return ok;
}
bool CrsPntr::onUpdateToFromCrsPntr(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setToFrom(x->getReal());
    return ok;
}


//------------------------------------------------------------------------------
// drawFunc() - draw our objects
//------------------------------------------------------------------------------
void CrsPntr::drawFunc()
{
    GLfloat ocolor[4];
    GLfloat lw;
    glGetFloatv(GL_CURRENT_COLOR, ocolor);
    glGetFloatv(GL_LINE_WIDTH, &lw);

    glColor3f(1, 1, 1);
    glLineWidth(2);

    if (showCrsPtr) {
        // this is the course pointer
        glPushMatrix();
            glBegin(GL_LINE_STRIP);
                glVertex2f(0.044f, 0.49f);
                glVertex2f(0.044f, 0.865f);
                glVertex2f(0, 1.065f);
                glVertex2f(-0.044f, 0.865f);
                glVertex2f(-0.044f, 0.49f);
                glVertex2f(0.044f, 0.49f);
            glEnd();
            glBegin(GL_LINE_STRIP);
                glVertex2f(0, -0.6f);
                glVertex2f(-0.044f, -0.676f);
                glVertex2f(-0.044f, -1.1f);
                glVertex2f( 0.044f, -1.1f);
                glVertex2f( 0.044f, -0.676f);
                glVertex2f(0, -0.6f);
            glEnd();
        glPopMatrix();
    }

    if (showCdi) {
        // figure how far to translate
        LCreal scale = inchesPerDot * cdiDots;
        // limit ourself to the size of the scale
        if (scale > 0.88) scale = 0.88f;
        if (scale < -0.88) scale = -0.88f;

        // cdi
        glPushMatrix();
            glTranslatef(static_cast<GLfloat>(scale), 0, 0);
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.044f, -0.45f);
                glVertex2f(0.044f, -0.45f);
                glVertex2f(0.044f, 0.35f);
                glVertex2f(-0.044f, 0.35f);
                glVertex2f(-0.044f, -0.45f);
            glEnd();
        glPopMatrix();
    }

    // our to from arrow will not be display unless we get a 1 (to) or a 0 (from)
    if (showToFrom) {
        if (toFrom == 1) {
            glPushMatrix();
                glBegin(GL_POLYGON);
                    glVertex2f(0, -0.6f);
                    glVertex2f(-0.044f, -0.475f);
                    glVertex2f(0.044f, -0.475f);
                glEnd();
            glPopMatrix();
        }
        if (toFrom == 0) {
            glPushMatrix();
                glBegin(GL_POLYGON);
                    glVertex2f(0, 0.475f);
                    glVertex2f(-0.044f, 0.37f);
                    glVertex2f(0.044f, 0.37f);
                glEnd();
            glPopMatrix();

        }
    }

    glColor4fv(ocolor);
    glLineWidth(lw);
}


//------------------------------------------------------------------------------
// updateData() - update non time-critical threads here
//------------------------------------------------------------------------------
void CrsPntr::updateData(const LCreal dt)
{
    // update base class first
    BaseClass::updateData(dt);

    // figure our scaling per dot
    inchesPerDot = inches / numDots;

}

// SLOT FUNCTIONS
//------------------------------------------------------------------------------
// setSlotNumCdiDots() - set the number of cdi dots we are using
//------------------------------------------------------------------------------
bool CrsPntr::setSlotNumCdiDots(const Basic::Number* const newCDI)
{
    bool ok = false;
    if (newCDI != nullptr) ok = setNumCdiDots(newCDI->getInt());
    return ok;
}
//------------------------------------------------------------------------------
// setSlotNumInches() - set the number of inches we are scaling across the dots
//------------------------------------------------------------------------------
bool CrsPntr::setSlotNumInches(const Basic::Number* const newNI)
{
    bool ok = false;
    if (newNI != nullptr) ok = setNumInches(newNI->getReal());
    return ok;
}
//------------------------------------------------------------------------------
// setSlotShowCdi() - display the cdi?
//------------------------------------------------------------------------------
bool CrsPntr::setSlotShowCdi(const Basic::Number* const newSCDI)
{
    bool ok = false;
    if (newSCDI != nullptr) ok = setShowCdi(newSCDI->getBoolean());
    return ok;
}
//------------------------------------------------------------------------------
// setSlotShowCrsPntr() - display the course pointer?
//------------------------------------------------------------------------------
bool CrsPntr::setSlotShowCrsPntr(const Basic::Number* const newSCP)
{
    bool ok = false;
    if (newSCP != nullptr) ok = setShowCrsPntr(newSCP->getBoolean());
    return ok;
}
//------------------------------------------------------------------------------
// setSlotShowToFrom() - display the to from arrow?
//------------------------------------------------------------------------------
bool CrsPntr::setSlotShowToFrom(const Basic::Number* const newTF)
{
    bool ok = false;
    if (newTF != nullptr) ok = setShowToFrom(newTF->getBoolean());
    return ok;
}


//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* CrsPntr::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}; // end of Demo namespace
}; // end of Eaagles namespace

