//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "Blocks.h"
#include "Board.h"
#include "Puzzle.h"
#include "State.h"

#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

#include <cstring>

namespace Eaagles {
namespace Example {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

    // Main board
    if ( std::strcmp(name, Board::getFactoryName()) == 0 ) {
        obj = new Board;
    }

    // Puzzle controller
    else if ( std::strcmp(name, Puzzle::getFactoryName()) == 0 ) {
        obj = new Puzzle();
    }

    // Puzzle state
    else if ( std::strcmp(name, State::getFactoryName()) == 0 ) {
        obj = new State();
    }

    // Puzzle blocks
    else if ( std::strcmp(name, Block1x1::getFactoryName()) == 0 ) {
        obj = new Block1x1();
    }
    else if ( std::strcmp(name, Block1x2::getFactoryName()) == 0 ) {
        obj = new Block1x2();
    }
    else if ( std::strcmp(name, Block2x1::getFactoryName()) == 0 ) {
        obj = new Block2x1();
    }
    else if ( std::strcmp(name, Block2x2::getFactoryName()) == 0 ) {
        obj = new Block2x2();
    }

    else {
       if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
       if (obj == nullptr) obj = Glut::Factory::createObj(name);
       if (obj == nullptr) obj = Basic::Factory::createObj(name);
    }

    return obj;
}

}  // end namespace Example
}  // end namespace Eaagles
