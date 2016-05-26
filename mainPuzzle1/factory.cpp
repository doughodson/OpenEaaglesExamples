
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "Blocks.h"
#include "Board.h"
#include "Puzzle.h"
#include "State.h"

#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    // Main board
    if ( name == Board::getFactoryName() ) {
        obj = new Board;
    }

    // Puzzle controller
    else if ( name == Puzzle::getFactoryName() ) {
        obj = new Puzzle();
    }

    // Puzzle state
    else if ( name == State::getFactoryName() ) {
        obj = new State();
    }

    // Puzzle blocks
    else if ( name == Block1x1::getFactoryName() ) {
        obj = new Block1x1();
    }
    else if ( name == Block1x2::getFactoryName() ) {
        obj = new Block1x2();
    }
    else if ( name == Block2x1::getFactoryName() ) {
        obj = new Block2x1();
    }
    else if ( name == Block2x2::getFactoryName() ) {
        obj = new Block2x2();
    }

    else {
       if (obj == nullptr) obj = oe::graphics::factory(name);
       if (obj == nullptr) obj = oe::glut::factory(name);
       if (obj == nullptr) obj = oe::base::factory(name);
    }

    return obj;
}
