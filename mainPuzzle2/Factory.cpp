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
    else if ( strcmp(name, Block1::getFactoryName()) == 0 ) {
        obj = new Block1();
    }
    else if ( strcmp(name, Block2::getFactoryName()) == 0 ) {
        obj = new Block2();
    }
    else if ( strcmp(name, Block3::getFactoryName()) == 0 ) {
        obj = new Block3();
    }
    else if ( strcmp(name, Block4::getFactoryName()) == 0 ) {
        obj = new Block4();
    }
    else if ( strcmp(name, Block5::getFactoryName()) == 0 ) {
        obj = new Block5();
    }
    else if ( strcmp(name, Block6::getFactoryName()) == 0 ) {
        obj = new Block6();
    }
    else if ( strcmp(name, Block7::getFactoryName()) == 0 ) {
        obj = new Block7();
    }
    else if ( strcmp(name, Block8::getFactoryName()) == 0 ) {
        obj = new Block8();
    }
    else if ( strcmp(name, Block9::getFactoryName()) == 0 ) {
        obj = new Block9();
    }
    else if ( strcmp(name, Block10::getFactoryName()) == 0 ) {
        obj = new Block10();
    }
    else if ( strcmp(name, Block11::getFactoryName()) == 0 ) {
        obj = new Block11();
    }
    else if ( strcmp(name, Block12::getFactoryName()) == 0 ) {
        obj = new Block12();
    }
    else if ( strcmp(name, Block13::getFactoryName()) == 0 ) {
        obj = new Block13();
    }
    else if ( strcmp(name, Block14::getFactoryName()) == 0 ) {
        obj = new Block14();
    }
    else if ( strcmp(name, Block15::getFactoryName()) == 0 ) {
        obj = new Block15();
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

