#include "formFunc.h"

#include "Blocks.h"
#include "Board.h"
#include "Puzzle.h"
#include "State.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"


namespace Eaagles {
namespace Puzzle2 {

Basic::Object* formFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // Main board
    if ( strcmp(formname, Board::getFormName()) == 0 ) {
        newform = new Board;
    }

    // Puzzle controller
    else if ( strcmp(formname, Puzzle::getFormName()) == 0 ) {
        newform = new Puzzle();
    }

    // Puzzle state
    else if ( strcmp(formname, State::getFormName()) == 0 ) {
        newform = new State();
    }

    // Puzzle blocks
    else if ( strcmp(formname, Block1::getFormName()) == 0 ) {
        newform = new Block1();
    }
    else if ( strcmp(formname, Block2::getFormName()) == 0 ) {
        newform = new Block2();
    }
    else if ( strcmp(formname, Block3::getFormName()) == 0 ) {
        newform = new Block3();
    }
    else if ( strcmp(formname, Block4::getFormName()) == 0 ) {
        newform = new Block4();
    }
    else if ( strcmp(formname, Block5::getFormName()) == 0 ) {
        newform = new Block5();
    }
    else if ( strcmp(formname, Block6::getFormName()) == 0 ) {
        newform = new Block6();
    }
    else if ( strcmp(formname, Block7::getFormName()) == 0 ) {
        newform = new Block7();
    }
    else if ( strcmp(formname, Block8::getFormName()) == 0 ) {
        newform = new Block8();
    }
    else if ( strcmp(formname, Block9::getFormName()) == 0 ) {
        newform = new Block9();
    }
    else if ( strcmp(formname, Block10::getFormName()) == 0 ) {
        newform = new Block10();
    }
    else if ( strcmp(formname, Block11::getFormName()) == 0 ) {
        newform = new Block11();
    }
    else if ( strcmp(formname, Block12::getFormName()) == 0 ) {
        newform = new Block12();
    }
    else if ( strcmp(formname, Block13::getFormName()) == 0 ) {
        newform = new Block13();
    }
    else if ( strcmp(formname, Block14::getFormName()) == 0 ) {
        newform = new Block14();
    }
    else if ( strcmp(formname, Block15::getFormName()) == 0 ) {
        newform = new Block15();
    }
    
    else {
       if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
       if (newform == 0) newform = Glut::glutFormFunc(formname);
       if (newform == 0) newform = Basic::basicFormFunc(formname);
    }
    return newform;
}

} // End Puzzle2 namespace
} // End Eaagles namespace
