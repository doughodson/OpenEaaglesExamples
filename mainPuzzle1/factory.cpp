
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "Blocks.hpp"
#include "Board.hpp"
#include "Puzzle.hpp"
#include "State.hpp"

#include "openeaagles/base/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"

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
