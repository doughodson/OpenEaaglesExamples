#include "formFunc.h"

#include "Blocks.h"
#include "Board.h"
#include "Puzzle.h"
#include "State.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"


namespace Eaagles {
namespace Puzzle {

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
    else if ( strcmp(formname, Block1x1::getFormName()) == 0 ) {
        newform = new Block1x1();
    }
    else if ( strcmp(formname, Block1x2::getFormName()) == 0 ) {
        newform = new Block1x2();
    }
    else if ( strcmp(formname, Block2x1::getFormName()) == 0 ) {
        newform = new Block2x1();
    }
    else if ( strcmp(formname, Block2x2::getFormName()) == 0 ) {
        newform = new Block2x2();
    }
    
    else {
       if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
       if (newform == 0) newform = Glut::glutFormFunc(formname);
       if (newform == 0) newform = Basic::basicFormFunc(formname);
    }
    return newform;
}

} // End Puzzle namespace
} // End Eaagles namespace
