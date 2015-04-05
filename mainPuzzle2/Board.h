//------------------------------------------------------------------------------
// Puzzle board
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_Board_H__
#define __Eaagles_Example_Board_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Basic { class PairStream; }
   namespace BasicGL { class Graphic; }

namespace Example {

class Puzzle;
class State;

class Board : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(Board, Glut::GlutDisplay)

public:
   Board();

   Puzzle* getPuzzle()                 { return puzzle; }      // Returns the puzzle controller
   const Puzzle* getPuzzle() const     { return puzzle; }      // Returns the puzzle controller (const version)

   const State* getFinalState() const  { return finalState; }  // Returns the final state

   void drawFunc() override;

   void updateData(const LCreal dt = 0.0) override;

protected:
   virtual bool setSlotPuzzle(Puzzle* const s);                       // Sets the Puzzle controller
   virtual bool setSlotTemplates(const Basic::PairStream* const s);   // Sets a list of the graphical templates for the blocks
   virtual unsigned int setupBlockGraphics();                         // Setup the list of BasicGL::Graphic objects for the initial blocks
   virtual void clearGraphics();                                      // Clears the list of BasicGL::Graphic objects for the blocks
   virtual void updateSolutionPath(const LCreal dt);                  // Updates the solution path graphics
   virtual void resetSolutionPath();                                  // Resets the solution path graphics
   virtual void updateBlockDeltaPositions();                          // Updates the blocks' delta positions

private:
   const Basic::PairStream* templates;    // Graphical templates for the blocks
   Puzzle*        puzzle;                 // the puzzle
   LCreal         startupTimer;           // Movement timer

   static const unsigned int MAX_STATES = 1000; // Max states in solution path (i.e., moves)
   const State*   path[MAX_STATES];          // Solution path
   const State*   finalState;                // Final state (puzzle solved if not equal zero)
   unsigned int   nstates;                   // number of states in solution path

   unsigned int   curPathState;              // Current state in the solution path
   LCreal         moveTimer;                 // Movement timer
   bool           movingFlg;                 // Block is moving

   static const unsigned int MAX_BLOCKS = 30;
   BasicGL::Graphic*  blocks[MAX_BLOCKS];    // Graphics for each block
   unsigned int         blockId[MAX_BLOCKS]; // Block reference IDs
   LCreal               xp[MAX_BLOCKS];      // Block X positions
   LCreal               yp[MAX_BLOCKS];      // Block Y positions
   LCreal               xd[MAX_BLOCKS];      // Block delta X positions
   LCreal               yd[MAX_BLOCKS];      // Block delta Y positions
   unsigned int         nblocks;             // number of blocks
};

}  // End of Example namespace
}  // End of Eaagles namespace

#endif
