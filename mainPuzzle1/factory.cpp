
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "Blocks.h"
#include "Board.h"
#include "Puzzle.h"
#include "State.h"

#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"

#include <cstring>

namespace oe {
namespace example {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

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
       if (obj == nullptr) obj = graphics::factory(name);
       if (obj == nullptr) obj = glut::factory(name);
       if (obj == nullptr) obj = base::factory(name);
    }

    return obj;
}

}
}
