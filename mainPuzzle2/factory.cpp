
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
    else if ( name == Block1::getFactoryName() ) {
        obj = new Block1();
    }
    else if ( name == Block2::getFactoryName() ) {
        obj = new Block2();
    }
    else if ( name == Block3::getFactoryName() ) {
        obj = new Block3();
    }
    else if ( name == Block4::getFactoryName() ) {
        obj = new Block4();
    }
    else if ( name == Block5::getFactoryName() ) {
        obj = new Block5();
    }
    else if ( name == Block6::getFactoryName() ) {
        obj = new Block6();
    }
    else if ( name == Block7::getFactoryName() ) {
        obj = new Block7();
    }
    else if ( name == Block8::getFactoryName() ) {
        obj = new Block8();
    }
    else if ( name == Block9::getFactoryName() ) {
        obj = new Block9();
    }
    else if ( name == Block10::getFactoryName() ) {
        obj = new Block10();
    }
    else if ( name == Block11::getFactoryName() ) {
        obj = new Block11();
    }
    else if ( name == Block12::getFactoryName() ) {
        obj = new Block12();
    }
    else if ( name == Block13::getFactoryName() ) {
        obj = new Block13();
    }
    else if ( name == Block14::getFactoryName() ) {
        obj = new Block14();
    }
    else if ( name == Block15::getFactoryName() ) {
        obj = new Block15();
    }

    else {
       if (obj == nullptr) obj = oe::graphics::factory(name);
       if (obj == nullptr) obj = oe::glut::factory(name);
       if (obj == nullptr) obj = oe::base::factory(name);
    }

    return obj;
}
