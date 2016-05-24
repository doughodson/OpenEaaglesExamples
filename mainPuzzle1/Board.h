//------------------------------------------------------------------------------
// Puzzle board
//------------------------------------------------------------------------------
#ifndef __oe_example_Board_H__
#define __oe_example_Board_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
   namespace base { class PairStream; }
   namespace graphics { class Graphic; }

namespace example {

class Puzzle;
class State;

class Board : public glut::GlutDisplay
{
   DECLARE_SUBCLASS(Board, glut::GlutDisplay)

public:
   Board();

   Puzzle* getPuzzle()                 { return puzzle; }      // Returns the puzzle controller
   const Puzzle* getPuzzle() const     { return puzzle; }      // Returns the puzzle controller (const version)

   const State* getFinalState() const  { return finalState; }  // Returns the final state

   virtual void drawFunc() override;

   virtual void updateData(const double dt = 0.0) override;

protected:
   virtual bool setSlotPuzzle(Puzzle* const s);                       // Sets the Puzzle controller
   virtual bool setSlotTemplates(const base::PairStream* const s);   // Sets a list of the graphical templates for the blocks
   virtual unsigned int setupBlockGraphics();                         // Setup the list of graphics::Graphic objects for the initial blocks
   virtual void clearGraphics();                                      // Clears the list of graphics::Graphic objects for the blocks
   virtual void updateSolutionPath(const double dt);                  // Updates the solution path graphics
   virtual void resetSolutionPath();                                  // Resets the solution path graphics
   virtual void updateBlockDeltaPositions();                          // Updates the blocks' delta positions

private:
   const base::PairStream* templates;  // Graphical templates for the blocks
   Puzzle*        puzzle;                 // the puzzle
   double         startupTimer;           // Movement timer

   static const unsigned int MAX_STATES = 1000; // Max states in solution path (i.e., moves)
   const State*   path[MAX_STATES];          // Solution path
   const State*   finalState;                // Final state (puzzle solved if not equal zero)
   unsigned int   nstates;                   // number of states in solution path

   unsigned int   curPathState;              // Current state in the solution path
   double         moveTimer;                 // Movement timer
   bool           movingFlg;                 // Block is moving

   static const unsigned int MAX_BLOCKS = 30;
   graphics::Graphic*  blocks[MAX_BLOCKS];    // Graphics for each block
   unsigned int       blockId[MAX_BLOCKS];   // Block reference IDs
   double             xp[MAX_BLOCKS];        // Block X positions
   double             yp[MAX_BLOCKS];        // Block Y positions
   double             xd[MAX_BLOCKS];        // Block delta X positions
   double             yd[MAX_BLOCKS];        // Block delta Y positions
   unsigned int       nblocks;               // number of blocks
};

}
}

#endif
