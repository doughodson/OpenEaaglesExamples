
#include "MapPage.h"
#include "Station.h"
#include "Display.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/basicGL/SymbolLoader.h"
#include "openeaagles/basicGL/Display.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(MapPage,"MapTestMapPage")
EMPTY_SLOTTABLE(MapPage)
EMPTY_SERIALIZER(MapPage)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
MapPage::MapPage()
{
    STANDARD_CONSTRUCTOR()
    for (int i = 0; i < MAX_PLAYERS; i++) {
        player[i] = 0;
        playerIdx[i] = -1;
    }
    stn = 0;
    loader = 0;

    for (int i = 0; i < MAX_READOUTS; i++) {
        latsSD[i].empty();
        lats[i] = 0;
        latReadoutXPosSD[i].empty();
        latReadoutXPos[i] = 0;
        latReadoutYPosSD[i].empty();
        latReadoutYPos[i] = 0;
        lonsSD[i].empty();
        lons[i] = 0;
        lonReadoutXPosSD[i].empty();
        lonReadoutXPos[i] = 0;
        lonReadoutYPosSD[i].empty();
        lonReadoutYPos[i] = 0;
    }
}  

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void MapPage::copyData(const MapPage& org, const bool)
{
    // copy base class stuff first
    BaseClass::copyData(org);

    // regardless of copy, we will create all new symbols
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (player[i] != 0) {
            player[i]->unref();
            player[i] = 0;
        }
        if (org.player[i] != 0) {
            player[i] = org.player[i];
            player[i]->ref();
        }
        playerIdx[i] = org.playerIdx[i];
    }

    if (loader != 0) {
        loader->unref();
        loader = 0;
    }
    if (org.loader != 0) {
        loader = org.loader;
        loader->ref();
    }

    if (stn != 0) {
        stn->unref();
        stn = 0;
    }
    if (org.stn != 0) {
        stn = org.stn;
        stn->ref();
    }

    for (int i = 0; i < MAX_READOUTS; i++) {
        latsSD[i].empty();
        lats[i] = org.lats[i];
        latReadoutXPosSD[i].empty();
        latReadoutXPos[i] = org.lonReadoutXPos[i];
        latReadoutYPosSD[i].empty();
        latReadoutYPos[i] = org.latReadoutYPos[i];
        lonsSD[i].empty();
        lons[i] = org.lons[i];
        lonReadoutXPosSD[i].empty();
        lonReadoutXPos[i] = org.lonReadoutXPos[i];
        lonReadoutYPosSD[i].empty();
        lonReadoutYPos[i] = org.lonReadoutYPos[i];
    }
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void MapPage::deleteData()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (player[i] != 0) {
            player[i]->unref();
            player[i] = 0;
        }
    }
    if (stn != 0) {
        stn->unref();
        stn = 0;
    }
    if (loader != 0) {
        loader->unref();
        loader = 0;
    }
}


void MapPage::drawFunc()
{
    // we are going to draw lat / lon lines
    // now let's draw our map lines
    double refLat = getReferenceLatDeg();
    double refLon = getReferenceLonDeg();
    // now get our range
    double latRange = getRange() / 60;
    double southernLat = refLat - latRange;
    double northernLat = refLat + latRange;
    // after calcs, double our lat range to encompass the whole screen
    latRange *= 2;  

    // get our viewport
    Display* dis = (Display*)getDisplay();
    if (dis != 0) {
        int start = nint((LCreal)southernLat - 1);
        GLdouble l = 0, r = 0, t = 0, b = 0, n = 0, f = 0;
        dis->getOrtho(l, r, b, t, n, f);
        double inchPerDegNS = t*2 / latRange;
        glPushMatrix();
            glBegin(GL_LINES);
                int count = 0;
                while (start < nint((LCreal)northernLat) + 1) {
                    GLfloat disFromRef = GLfloat(refLat - start);
                    disFromRef *= (GLfloat)inchPerDegNS;
                    if (count < MAX_READOUTS) {
                        lats[count] = start;
                        latReadoutYPos[count] = float(-disFromRef + 0.2);
                        latReadoutXPos[count++] = float(l + 0.5f);
                    }
                    glVertex2f((GLfloat)l, -disFromRef);
                    glVertex2f((GLfloat)r, -disFromRef);
                    start++;
                }
            glEnd();
            // now make the rest of ours go away
            for (int i = count; i < MAX_READOUTS; i++) latReadoutYPos[i] = -10000;
        glPopMatrix();

        // now for the longitude lines
        double lonRange = getRange() / (60 * getCosRefLat());
        double easternLon = refLon - lonRange;
        double westernLon = refLon + lonRange;

        lonRange *= 2;
        start = nint((LCreal)easternLon - 1);
        double inchPerDegEW = r*2 / lonRange;
        glPushMatrix();
            glBegin(GL_LINES);
                count = 0;
                while (start < nint((LCreal)westernLon) + 1) {
                    GLfloat disFromRef = GLfloat(refLon - start);
                    if (count < MAX_READOUTS) {
                        lons[count] = start;
                        disFromRef *= (GLfloat)inchPerDegEW;
                        lonReadoutXPos[count] = float(-disFromRef + 0.2);
                        lonReadoutYPos[count++] = float(t - 0.5f);
                    }
                    glVertex2f(-disFromRef, (GLfloat)b);
                    glVertex2f(-disFromRef, (GLfloat)t);
                    start++;
                }
                for (int i = count; i < MAX_READOUTS; i++) lonReadoutYPos[i] = -10000;
            glEnd();
        glPopMatrix();

    }
}

//------------------------------------------------------------------------------
// updateData() -- update background data
//------------------------------------------------------------------------------
void MapPage::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);
    
    // get our pointers
    if (loader == 0) {
        Basic::Pair* pair = findByType(typeid(BasicGL::SymbolLoader));
        if (pair != 0) {
            loader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
            if (loader != 0) loader->ref();
        }
    }
    if (stn == 0) {
        BasicGL::Display* dis = getDisplay();
        if (dis != 0) {
            stn = (Station*)dis->findContainerByType(typeid(Station));
            if (stn != 0) {
                stn->ref();
                // set our reference lat / lon initially
                Simulation::Simulation* sim = stn->getSimulation();
                if (sim != 0) {
                    setReferenceLatDeg(sim->getRefLatitude());
                    setReferenceLonDeg(sim->getRefLongitude());
                }
            }
        }
    }

    // let's update our players
    if (loader != 0 && stn != 0) {
        Basic::PairStream* stream = stn->getPlayers();                      
        if (stream != 0) {
            // create our new player list
            Simulation::Player* newPlayers[MAX_PLAYERS];
            int numNewPlayers = 0;
            // go through all of our non-ownship players and populate our new list
            Basic::List::Item* item = stream->getFirstItem();
            while (item != 0 && numNewPlayers < MAX_PLAYERS) {
                Basic::Pair* pair = (Basic::Pair*)item->getValue();
                if (pair != 0) {
                    Simulation::Player* ply = dynamic_cast<Simulation::Player*>(pair->object());
                    if (ply != 0) {
                        newPlayers[numNewPlayers] = ply;
                        newPlayers[numNewPlayers++]->ref();
                    }
                }
                item = item->getNext();
            }

            // ok, go through our new list and match it with our old, and throw
            // away any old players that aren't in the new list, and add any new
            // players that aren't in the old list
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (player[i] != 0) {
                    bool match = false; 
                    for (int j = 0; j < numNewPlayers && !match; j++) {
                        if (player[i] == newPlayers[j]) {
                            // if they do match, get rid of our new player, so we don't re-add it 
                            // later accidentally
                            match = true;
                            newPlayers[j]->unref();
                            newPlayers[j] = 0;
                        }
                    }
                    // if our player doesn't match, we remove it from our list
                    if (!match) {
                        loader->removeSymbol(playerIdx[i]);
                        player[i]->unref();
                        player[i] = 0;
                        playerIdx[i] = -1;
                    }
                }
            }

            // ok, now we have removed our old players (and our matched ones), let's add our new ones!
            for (int i = 0; i < numNewPlayers; i++) {
                // make sure this player wasn't deleted earlier
                if (newPlayers[i] != 0) {
                    bool found = false;
                    for (int j = 0; j < MAX_PLAYERS && !found; j++) {
                        if (player[j] == 0) {
                            found = true;
                            // found an empty player, let's set him!
                            player[j] = newPlayers[i];
                            player[j]->ref();
                            int type = 1;
                            if (player[j]->isSide(Simulation::Player::RED)) type = 2;
                            playerIdx[j] = loader->addSymbol(type, "player");
                            if (player[j]->getName() != 0) {
                                loader->updateSymbolText(playerIdx[j], "name", player[j]->getName()->getString());
                            }
                            // now let's empty our new player list
                            newPlayers[i]->unref();
                            newPlayers[i] = 0;
                        }
                    }
                }
            }

            // ok, now update our symbols' positions
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (player[i] != 0) {
                    loader->updateSymbolPositionLL(playerIdx[i], player[i]->getLatitude(), player[i]->getLongitude());
                    loader->updateSymbolHeading(playerIdx[i], player[i]->getHeadingD());
                }
            }
        }
    }

    // now send our lat / lon text data
    send("line%d", UPDATE_VALUE2, latReadoutYPos, latReadoutYPosSD, MAX_READOUTS);
    send("line%d", UPDATE_VALUE, latReadoutXPos, latReadoutXPosSD, MAX_READOUTS);
    send("text%d", UPDATE_VALUE, lats, latsSD, MAX_READOUTS);
    send("lonline%d", UPDATE_VALUE2, lonReadoutYPos, lonReadoutYPosSD, MAX_READOUTS);
    send("lonline%d", UPDATE_VALUE, lonReadoutXPos, lonReadoutXPosSD, MAX_READOUTS);
    send("lontext%d", UPDATE_VALUE, lons, lonsSD, MAX_READOUTS);
}

}  // end of Example namespace
}  // end of Eaagles namespace

