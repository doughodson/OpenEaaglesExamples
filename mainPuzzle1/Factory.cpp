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

namespace Eaagles {
namespace Example {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    // Main board
    if ( strcmp(name, Board::getFactoryName()) == 0 ) {
        obj = new Board;
    }

    // Puzzle controller
    else if ( strcmp(name, Puzzle::getFactoryName()) == 0 ) {
        obj = new Puzzle();
    }

    // Puzzle state
    else if ( strcmp(name, State::getFactoryName()) == 0 ) {
        obj = new State();
    }

    // Puzzle blocks
    else if ( strcmp(name, Block1x1::getFactoryName()) == 0 ) {
        obj = new Block1x1();
    }
    else if ( strcmp(name, Block1x2::getFactoryName()) == 0 ) {
        obj = new Block1x2();
    }
    else if ( strcmp(name, Block2x1::getFactoryName()) == 0 ) {
        obj = new Block2x1();
    }
    else if ( strcmp(name, Block2x2::getFactoryName()) == 0 ) {
        obj = new Block2x2();
    }
    
    else {
       if (obj == 0) obj = BasicGL::Factory::createObj(name);
       if (obj == 0) obj = Glut::Factory::createObj(name);
       if (obj == 0) obj = Basic::Factory::createObj(name);
    }

    return obj;
}

}  // end namespace Example
}  // end namespace Eaagles
