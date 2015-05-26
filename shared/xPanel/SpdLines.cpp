//------------------------------------------------------------------------------
// Class: SpdLines
//------------------------------------------------------------------------------
#include "SpdLines.h"
#include "openeaagles/basic/Number.h"

namespace Eaagles {
namespace xPanel {

IMPLEMENT_SUBCLASS(SpdLines, "SpdLines")
EMPTY_SERIALIZER(SpdLines)
EMPTY_DELETEDATA(SpdLines)

BEGIN_SLOTTABLE(SpdLines)
    "isAlt",              // draw for the altitude scale (instead of making a new class)
END_SLOTTABLE(SpdLines)

BEGIN_SLOT_MAP(SpdLines)
    ON_SLOT(1, setSlotIsAlt, Basic::Number)
END_SLOT_MAP()

// Event handler
BEGIN_EVENT_HANDLER(SpdLines)
    ON_EVENT_OBJ(UPDATE_VALUE, onEventSetIsAltSpdLines, Basic::Number)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
SpdLines::SpdLines()
{
    STANDARD_CONSTRUCTOR()
    isAlt = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void SpdLines::copyData(const SpdLines& org, const bool)
{
    // copy baseclass stuff first
    BaseClass::copyData(org);
    isAlt = org.isAlt;
}

//------------------------------------------------------------------------------
// drawFunc() - draw our objects
//------------------------------------------------------------------------------
void SpdLines::drawFunc()
{    
    GLfloat ocolor[4];
    GLfloat lw;
    glGetFloatv(GL_CURRENT_COLOR, ocolor);
    glGetFloatv(GL_LINE_WIDTH, &lw);
    
    BEGIN_DLIST

        if (!isAlt) {
            LCreal startPoint = 0;
            // now step through and draw all the lines (100 of them)
            // draw the big lines first
            glLineWidth(2);
            for (int i = 0; i < 51; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0.6f, startPoint);
                        lcVertex2(0.48f, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9f;
            }
            // now draw the small lines
            startPoint = 0.45f;
            for (int i = 0; i < 50; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0.6f, startPoint);
                        lcVertex2(0.52f, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9f;
            }

            glLineWidth(1);
            glColor3f(0.1f, 0.1f, 0.1f);

            // make the polygon last
            glPushMatrix();
                glBegin(GL_POLYGON);
                    glVertex2f(0, 1500);
                    glVertex2f(0, -1500);
                    glVertex2f(0.6f, -1500);
                    glVertex2f(0.6f, 1500);
                glEnd();
            glPopMatrix();
        }
        else {
            LCreal startPoint = 0;
            // now step through and draw all the lines (approx 280 of them, gets us to about 55,800 feet)
            // draw the big lines first
            glLineWidth(2);
            for (int i = 0; i < 281; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0, startPoint);
                        lcVertex2(0.12f, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9f;
            }
            // now draw the small lines
            startPoint = 0.45f;
            for (int i = 0; i < 280; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0, startPoint);
                        lcVertex2(0.08f, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9f;
            }

            glLineWidth(1);
            glColor3f(0.1f, 0.1f, 0.1f);

            // make the polygon last
            glPushMatrix();
                glBegin(GL_POLYGON);
                    glVertex2f(0, 1500);
                    glVertex2f(0, -1500);
                    glVertex2f(0.879f, -1500);
                    glVertex2f(0.879f, 1500);
                glEnd();
            glPopMatrix();
        }        
    END_DLIST  
      
    glColor4fv(ocolor);
    glLineWidth(lw);
}

// Event function
bool SpdLines::onEventSetIsAltSpdLines(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setIsAlt(x->getBoolean());
    return ok;
}

// SLOT FUNCTIONS
//------------------------------------------------------------------------------
// setSlotIsAlt() - sets our altitude flag
//------------------------------------------------------------------------------
bool SpdLines::setSlotIsAlt(const Basic::Number* const newAltFlag)
{
    bool ok = false;
    if (newAltFlag != nullptr) ok = setIsAlt(newAltFlag->getBoolean());
    return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex() 
//------------------------------------------------------------------------------
Basic::Object* SpdLines::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}; // end of xPanel namespace
}; // end of Eaagles namespace

