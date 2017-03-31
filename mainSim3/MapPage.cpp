
#include "MapPage.hpp"
#include "Station.hpp"
#include "Display.hpp"

#include "openeaagles/models/player/Player.hpp"
#include "openeaagles/models/WorldModel.hpp"

#include "openeaagles/graphics/SymbolLoader.hpp"
#include "openeaagles/graphics/Display.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/util/math_utils.hpp"

IMPLEMENT_SUBCLASS(MapPage, "MapTestMapPage")
EMPTY_SLOTTABLE(MapPage)
EMPTY_SERIALIZER(MapPage)

MapPage::MapPage()
{
    STANDARD_CONSTRUCTOR()
}

void MapPage::copyData(const MapPage& org, const bool)
{
    BaseClass::copyData(org);

    // regardless of copy, we will create all new symbols
    for (unsigned int i = 0; i < MAX_PLAYERS; i++) {
        if (player[i] != nullptr) {
            player[i]->unref();
            player[i] = nullptr;
        }
        if (org.player[i] != nullptr) {
            player[i] = org.player[i];
            player[i]->ref();
        }
        playerIdx[i] = org.playerIdx[i];
    }

    if (loader != nullptr) {
        loader->unref();
        loader = nullptr;
    }
    if (org.loader != nullptr) {
        loader = org.loader;
        loader->ref();
    }

    if (stn != nullptr) {
        stn->unref();
        stn = nullptr;
    }
    if (org.stn != nullptr) {
        stn = org.stn;
        stn->ref();
    }

    for (unsigned int i = 0; i < MAX_READOUTS; i++) {
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

void MapPage::deleteData()
{
    for (unsigned int i = 0; i < MAX_PLAYERS; i++) {
        if (player[i] != nullptr) {
            player[i]->unref();
            player[i] = nullptr;
        }
    }
    if (stn != nullptr) {
        stn->unref();
        stn = nullptr;
    }
    if (loader != nullptr) {
        loader->unref();
        loader = nullptr;
    }
}

void MapPage::drawFunc()
{
    // we are going to draw lat / lon lines
    // now let's draw our map lines
    const double refLat = getReferenceLatDeg();
    const double refLon = getReferenceLonDeg();
    // now get our range
    double latRange = getRange() / 60.0;
    const double southernLat = refLat - latRange;
    const double northernLat = refLat + latRange;
    // after calcs, double our lat range to encompass the whole screen
    latRange *= 2;

    // get our viewport
    const auto dis = static_cast<Display*>(getDisplay());
    if (dis != nullptr) {
        int start = oe::base::nint(static_cast<double>(southernLat) - 1);
        GLdouble l = 0, r = 0, t = 0, b = 0, n = 0, f = 0;
        dis->getOrtho(l, r, b, t, n, f);
        double inchPerDegNS = t*2 / latRange;
        glPushMatrix();
            glBegin(GL_LINES);
                int count = 0;
                while (start < oe::base::nint( static_cast<double>(northernLat) ) + 1) {
                    GLfloat disFromRef = static_cast<GLfloat>(refLat - start);
                    disFromRef *= static_cast<GLfloat>(inchPerDegNS);
                    if (count < MAX_READOUTS) {
                        lats[count] = start;
                        latReadoutYPos[count] = static_cast<float>(-disFromRef + 0.2);
                        latReadoutXPos[count++] = static_cast<float>(l + 0.5f);
                    }
                    glVertex2f(static_cast<GLfloat>(l), -disFromRef);
                    glVertex2f(static_cast<GLfloat>(r), -disFromRef);
                    start++;
                }
            glEnd();
            // now make the rest of ours go away
            for (int i = count; i < MAX_READOUTS; i++) latReadoutYPos[i] = -10000;
        glPopMatrix();

        // now for the longitude lines
        double lonRange = getRange() / (60 * getCosRefLat());
        const double easternLon = refLon - lonRange;
        const double westernLon = refLon + lonRange;

        lonRange *= 2;
        start = oe::base::nint( static_cast<double>(easternLon) - 1);
        const double inchPerDegEW = r*2 / lonRange;
        glPushMatrix();
            glBegin(GL_LINES);
                count = 0;
                while (start < oe::base::nint( static_cast<double>(westernLon) ) + 1) {
                    GLfloat disFromRef = static_cast<GLfloat>(refLon - start);
                    if (count < MAX_READOUTS) {
                        lons[count] = start;
                        disFromRef *= static_cast<GLfloat>(inchPerDegEW);
                        lonReadoutXPos[count] = static_cast<float>(-disFromRef + 0.2);
                        lonReadoutYPos[count++] = static_cast<float>(t - 0.5f);
                    }
                    glVertex2f(-disFromRef, static_cast<GLfloat>(b));
                    glVertex2f(-disFromRef, static_cast<GLfloat>(t));
                    start++;
                }
                for (int i = count; i < MAX_READOUTS; i++) lonReadoutYPos[i] = -10000;
            glEnd();
        glPopMatrix();
    }
}

void MapPage::updateData(const double dt)
{
    BaseClass::updateData(dt);

    // get our pointers
    if (loader == nullptr) {
        oe::base::Pair* pair = findByType(typeid(oe::graphics::SymbolLoader));
        if (pair != nullptr) {
            loader = dynamic_cast<oe::graphics::SymbolLoader*>(pair->object());
            if (loader != nullptr) loader->ref();
        }
    }
    if (stn == nullptr) {
        oe::graphics::Display* dis = getDisplay();
        if (dis != nullptr) {
            stn = static_cast<Station*>(dis->findContainerByType(typeid(Station)));
            if (stn != nullptr) {
                stn->ref();
                // set our reference lat / lon initially
                const auto sim = dynamic_cast<oe::models::WorldModel*>(stn->getSimulation());
                if (sim != nullptr) {
                    setReferenceLatDeg(sim->getRefLatitude());
                    setReferenceLonDeg(sim->getRefLongitude());
                }
            }
        }
    }

    // let's update our players
    if (loader != nullptr && stn != nullptr) {
        oe::base::PairStream* stream = stn->getPlayers();
        if (stream != nullptr) {
            // create our new player list
            oe::models::Player* newPlayers[MAX_PLAYERS];
            unsigned int numNewPlayers = 0;
            // go through all of our non-ownship players and populate our new list
            oe::base::List::Item* item = stream->getFirstItem();
            while (item != nullptr && numNewPlayers < MAX_PLAYERS) {
                const auto pair = static_cast<oe::base::Pair*>(item->getValue());
                if (pair != nullptr) {
                    const auto ply = dynamic_cast<oe::models::Player*>(pair->object());
                    if (ply != nullptr) {
                        newPlayers[numNewPlayers] = ply;
                        newPlayers[numNewPlayers++]->ref();
                    }
                }
                item = item->getNext();
            }

            // ok, go through our new list and match it with our old, and throw
            // away any old players that aren't in the new list, and add any new
            // players that aren't in the old list
            for (unsigned int i = 0; i < MAX_PLAYERS; i++) {
                if (player[i] != nullptr) {
                    bool match = false;
                    for (unsigned int j = 0; j < numNewPlayers && !match; j++) {
                        if (player[i] == newPlayers[j]) {
                            // if they do match, get rid of our new player, so we don't re-add it
                            // later accidentally
                            match = true;
                            newPlayers[j]->unref();
                            newPlayers[j] = nullptr;
                        }
                    }
                    // if our player doesn't match, we remove it from our list
                    if (!match) {
                        loader->removeSymbol(playerIdx[i]);
                        player[i]->unref();
                        player[i] = nullptr;
                        playerIdx[i] = -1;
                    }
                }
            }

            // ok, now we have removed our old players (and our matched ones), let's add our new ones!
            for (unsigned int i = 0; i < numNewPlayers; i++) {
                // make sure this player wasn't deleted earlier
                if (newPlayers[i] != nullptr) {
                    bool found = false;
                    for (unsigned int j = 0; j < MAX_PLAYERS && !found; j++) {
                        if (player[j] == nullptr) {
                            found = true;
                            // found an empty player, let's set him!
                            player[j] = newPlayers[i];
                            player[j]->ref();
                            int type = 1;
                            if (player[j]->isSide(oe::models::Player::RED)) type = 2;
                            playerIdx[j] = loader->addSymbol(type, "player");
                            if (player[j]->getName() != nullptr) {
                                loader->updateSymbolText(playerIdx[j], "name", player[j]->getName()->getString());
                            }
                            // now let's empty our new player list
                            newPlayers[i]->unref();
                            newPlayers[i] = nullptr;
                        }
                    }
                }
            }

            // ok, now update our symbols' positions
            for (unsigned int i = 0; i < MAX_PLAYERS; i++) {
                if (player[i] != nullptr) {
                    loader->updateSymbolPositionLL(playerIdx[i], player[i]->getLatitude(), player[i]->getLongitude());
                    loader->updateSymbolHeading(playerIdx[i], player[i]->getHeadingD());
                }
            }
        }
    }

    // now send our lat / lon text data
    send("line%d", UPDATE_VALUE2, latReadoutYPos.data(), latReadoutYPosSD, MAX_READOUTS);
    send("line%d", UPDATE_VALUE, latReadoutXPos.data(), latReadoutXPosSD, MAX_READOUTS);
    send("text%d", UPDATE_VALUE, lats.data(), latsSD, MAX_READOUTS);
    send("lonline%d", UPDATE_VALUE2, lonReadoutYPos.data(), lonReadoutYPosSD, MAX_READOUTS);
    send("lonline%d", UPDATE_VALUE, lonReadoutXPos.data(), lonReadoutXPosSD, MAX_READOUTS);
    send("lontext%d", UPDATE_VALUE, lons.data(), lonsSD, MAX_READOUTS);
}
