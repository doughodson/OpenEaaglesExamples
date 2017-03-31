
#ifndef __Board_H__
#define __Board_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

#include <array>

namespace oe {
namespace base { class PairStream; }
namespace graphics { class Graphic; }
}
class Puzzle;
class State;

//------------------------------------------------------------------------------
// Class: Board
// Description: Puzzle board
//------------------------------------------------------------------------------
class Board : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(Board, oe::glut::GlutDisplay)

public:
   Board();

   Puzzle* getPuzzle()                 { return puzzle; }      // Returns the puzzle controller
   const Puzzle* getPuzzle() const     { return puzzle; }      // Returns the puzzle controller (const version)

   const State* getFinalState() const  { return finalState; }  // Returns the final state

   virtual void drawFunc() override;

   virtual void updateData(const double dt = 0.0) override;

protected:
   virtual bool setSlotPuzzle(Puzzle* const s);                          // Sets the Puzzle controller
   virtual bool setSlotTemplates(const oe::base::PairStream* const s);   // Sets a list of the graphical templates for the blocks
   virtual unsigned int setupBlockGraphics();                            // Setup the list of graphics::Graphic objects for the initial blocks
   virtual void clearGraphics();                                         // Clears the list of graphics::Graphic objects for the blocks
   virtual void updateSolutionPath(const double dt);                     // Updates the solution path graphics
   virtual void resetSolutionPath();                                     // Resets the solution path graphics
   virtual void updateBlockDeltaPositions();                             // Updates the blocks' delta positions

private:
   const oe::base::PairStream* templates {};      // Graphical templates for the blocks
   Puzzle* puzzle {};                             // the puzzle
   double  startupTimer {};                       // Movement timer

   static const unsigned int MAX_STATES = 1000;   // Max states in solution path (i.e., moves)
   std::array<const State*, MAX_STATES> path {};  // Solution path
   const State* finalState {};                    // Final state (puzzle solved if not equal zero)
   unsigned int nstates {};                       // number of states in solution path

   unsigned int curPathState {};                  // Current state in the solution path
   double       moveTimer {};                     // Movement timer
   bool         movingFlg {};                     // Block is moving

   static const unsigned int MAX_BLOCKS = 30;
   std::array<oe::graphics::Graphic*, MAX_BLOCKS> blocks {};  // Graphics for each block
   std::array<unsigned int, MAX_BLOCKS> blockId {};           // Block reference IDs
   std::array<double, MAX_BLOCKS> xp {};                      // Block X positions
   std::array<double, MAX_BLOCKS> yp {};                      // Block Y positions
   std::array<double, MAX_BLOCKS> xd {};                      // Block delta X positions
   std::array<double, MAX_BLOCKS> yd {};                      // Block delta Y positions
   unsigned int nblocks {};                                   // number of blocks
};

#endif
