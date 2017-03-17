
#include "SpdLines.hpp"
#include "openeaagles/base/Number.hpp"
#include <GL/glu.h>
#include <iostream>

using namespace oe;

IMPLEMENT_SUBCLASS(SpdLines, "SpdLines")
EMPTY_SERIALIZER(SpdLines)
EMPTY_DELETEDATA(SpdLines)

BEGIN_SLOTTABLE(SpdLines)
    "isAlt",              // draw for the altitude scale (instead of making a new class)
    "isBackground",       // do we draw the background?
END_SLOTTABLE(SpdLines)

BEGIN_SLOT_MAP(SpdLines)
    ON_SLOT(1, setSlotIsAlt, base::Number)
    ON_SLOT(2, setSlotDrawBack, base::Number)
END_SLOT_MAP()

SpdLines::SpdLines()
{
    STANDARD_CONSTRUCTOR()
}

void SpdLines::copyData(const SpdLines& org, const bool)
{
    // copy baseclass stuff first
    BaseClass::copyData(org);
    isAlt = org.isAlt;
    drawBack = org.drawBack;
}

bool SpdLines::setIsAlt(const bool newIsAlt)
{
    isAlt = newIsAlt;
    return true;
}

bool SpdLines::setDrawBack(const bool newDB)
{
    drawBack = newDB;
    return true;
}

void SpdLines::drawFunc()
{
    GLfloat ocolor[4];
    GLfloat lw;
    glGetFloatv(GL_CURRENT_COLOR, ocolor);
    glGetFloatv(GL_LINE_WIDTH, &lw);

    BEGIN_DLIST

        if (!isAlt) {
            double startPoint = 0;
            // now step through and draw all the lines (100 of them)
            // draw the big lines first
            glLineWidth(2);
            for (int i = 0; i < 51; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0.6, startPoint);
                        lcVertex2(0.48, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9;
            }
            // now draw the small lines
            startPoint = 0.45;
            for (int i = 0; i < 50; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0.6, startPoint);
                        lcVertex2(0.52, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9;
            }

            if (drawBack) {
                glLineWidth(1);
                glColor3f(0, 0, 0);
                // make the polygon last
                glPushMatrix();
                    glBegin(GL_POLYGON);
                        glVertex2f(0.0f,  15.0f);
                        glVertex2f(0.0f, -15.0f);
                        glVertex2f(0.6f, -15.0f);
                        glVertex2f(0.6f,  15.0f);
                    glEnd();
                glPopMatrix();
            }
        }
        else {
            // if we are drawing the altitude lines
            double startPoint = 0;
            // now step through and draw all the lines (approx 280 of them, gets us to about 55,800 feet)
            // draw the big lines first
            glLineWidth(2);
            for (int i = 0; i < 281; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0, startPoint);
                        lcVertex2(0.12, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9;
            }
            // now draw the small lines
            startPoint = 0.45;
            for (int i = 0; i < 280; i++) {
                glPushMatrix();
                    glBegin(GL_LINES);
                        lcVertex2(0, startPoint);
                        lcVertex2(0.08, startPoint);
                    glEnd();
                glPopMatrix();
                // move up to the next line
                startPoint += 0.9;
            }

            if (drawBack) {
                glLineWidth(1);
                glColor3f(0, 0, 0);

                // make the polygon last
                glPushMatrix();
                    glBegin(GL_POLYGON);
                        glVertex2f(0, 15);
                        glVertex2f(0, -15);
                        glVertex2f(0.879f, -15);
                        glVertex2f(0.879f, 15);
                    glEnd();
                glPopMatrix();
            }
        }
    END_DLIST

    glColor4fv(ocolor);
    glLineWidth(lw);
}

bool SpdLines::setSlotIsAlt(const base::Number* const newAltFlag)
{
    bool ok = false;
    if (newAltFlag != nullptr) ok = setIsAlt(newAltFlag->getBoolean());
    return ok;
}

//------------------------------------------------------------------------------
// sets our draw background flag
//------------------------------------------------------------------------------
bool SpdLines::setSlotDrawBack(const base::Number* const newDB)
{
    bool ok = false;
    if (newDB != nullptr) ok = setDrawBack(newDB->getBoolean());
    return ok;
}

