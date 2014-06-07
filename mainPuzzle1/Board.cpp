
#include "Board.h"
#include "Puzzle.h"
#include "State.h"
#include "Blocks.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(Board,"PuzzleBoard")

//------------------------------------------------------------------------------
// Slot table for this form type
//------------------------------------------------------------------------------
BEGIN_SLOTTABLE(Board)
    "puzzle",      //  1: Our puzzle controller
    "templates",   //  2: List of block templates (slot numbers MUST match block type IDs)
END_SLOTTABLE(Board)

//------------------------------------------------------------------------------
//  Map slot table to handles 
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(Board)
    ON_SLOT( 1, setSlotPuzzle,    Puzzle )        
    ON_SLOT( 2, setSlotTemplates, Basic::PairStream )        
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Board::Board()
{
   STANDARD_CONSTRUCTOR()

   // Clear our list of BasicGL::Graphic templates for each block type
   templates = 0;

   // clear the puzzle
   puzzle = 0;

   // Clear the solution path
   for (unsigned int i = 0; i < MAX_STATES; i++) {
      path[i] = 0;
   }
   finalState = 0;
   nstates = 0;

   // Clear our blocks
   for (unsigned int i = 0; i < MAX_BLOCKS; i++) {
      blocks[i] = 0;
      blockId[i] = 0;
      xp[i] = 0;
      yp[i] = 0;
      xd[i] = 0;
      yd[i] = 0;
   }
   nblocks = 0;

   curPathState = 0;
   moveTimer = 0;
   startupTimer = 0;
   movingFlg = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Board::copyData(const Board& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      templates = 0;
      puzzle = 0;
      finalState = 0;
   }

   setSlotPuzzle(0);
   if (org.puzzle != 0) {
      setSlotPuzzle( org.puzzle->clone() );
   }

   setSlotTemplates(0);
   if (org.templates != 0) {
      setSlotTemplates( org.templates->clone() );
   }

   // Clear the solution path
   for (unsigned int i = 0; i < MAX_STATES; i++) {
      path[i] = 0;
   }
   finalState = 0;
   nstates = 0;

   // Clear our blocks
   for (unsigned int i = 0; i < MAX_BLOCKS; i++) {
      blocks[i] = 0;
      blockId[i] = 0;
      xp[i] = 0;
      yp[i] = 0;
      xd[i] = 0;
      yd[i] = 0;
   }
   nblocks = 0;

   curPathState = 0;
   moveTimer = 0;
   startupTimer = 0;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Board::deleteData()
{
   setSlotPuzzle(0);
   setSlotTemplates(0);
   clearGraphics();
}

//------------------------------------------------------------------------------
// updateData() -- Update non-time critical (background) stuff here
//------------------------------------------------------------------------------
void Board::updateData(const LCreal dt)
{
   BaseClass::updateData(dt);

   startupTimer += dt;

   // ---
   // Find the graphic blocks to draw
   // ---
   if (nblocks == 0) {
      setupBlockGraphics();
   }

   // ---
   // Try to solve the puzzle
   // ---
   if (puzzle != 0 && finalState == 0 && startupTimer > 1.0f) {
      std::cout << "Starting to solve!" << std::endl;
      finalState = puzzle->solve();

      // ---
      // Get the path if we have a solution.
      // ---
      if (finalState != 0) {
         //puz->printPath(final);
         const State* s = finalState;
         while (s->getGeneration() > 0 && nstates < MAX_STATES) {
            path[nstates++] = s;
            s = static_cast<const State*>( s->container() );
         }
         resetSolutionPath();
         std::cout << "Board::updateData() Number moves : " << nstates << std::endl;
      }
      else {
         std::cout << "No solution as found!" << std::endl;
      }
   }

   // ---
   // Run the puzzle solution path
   // ---
   if (nblocks > 0 && finalState != 0) {
      updateSolutionPath(dt);
   }

}

//------------------------------------------------------------------------------
// Setup the list of BasicGL::Graphic objects for the initial blocks
// Returns the number of blocks
//------------------------------------------------------------------------------
unsigned int Board::setupBlockGraphics()
{
   clearGraphics();

   if (puzzle != 0 && templates != 0) {
      const State* s = puzzle->getInitState();
      if (s != 0) {
         bool finished = false;
         for (unsigned int i = 0; i < MAX_BLOCKS && !finished; i++) {
            const Block* b = s->getBlock(i+1);
            if (b != 0) {
               unsigned int typeId = b->getTypeId();
               const Basic::Pair* pair = templates->getPosition(typeId);
               if (pair != 0) {
                  const BasicGL::Graphic* g = dynamic_cast<const BasicGL::Graphic*>( pair->object() );
                  if (g != 0) {
                     // Ok, we've found a BasicGL::Graphic to draw this block!
                     blocks[nblocks] = g->clone();
                     blocks[nblocks]->container(this);
                     blockId[nblocks] = b->getReferenceID();
                     xp[nblocks] = static_cast<LCreal>(b->getX());
                     yp[nblocks] = static_cast<LCreal>(b->getY());
                     xd[nblocks] = 0;
                     yd[nblocks] = 0;
                     nblocks++;
                  }
               }
            }
            else finished = true;
         }
      }
   }
   return nblocks;
}

// Clears the list of BasicGL::Graphic objects for the blocks
void Board::clearGraphics()
{
   while (nblocks > 0) {
      nblocks--;
      blocks[nblocks]->unref();
      blocks[nblocks] = 0;
      blockId[nblocks] = 0;
      xp[nblocks] = 0;
      yp[nblocks] = 0;
      xd[nblocks] = 0;
      yd[nblocks] = 0;
   }
   movingFlg = false;
   moveTimer = 0;
}

//------------------------------------------------------------------------------
// Updates the solution path graphics
//------------------------------------------------------------------------------
void Board::updateSolutionPath(const LCreal dt)
{
   if (movingFlg) {
      // Wait while we move between states
      moveTimer += (dt*2.0f);
      if (moveTimer > 1.0f) {
         moveTimer = 1.0f;
         movingFlg = false;
      }
   }
   else if (curPathState > 0) {
      // Step to next state
      curPathState--;
      updateBlockDeltaPositions();
      movingFlg = true;
      moveTimer = 0;
   }
   //else if (curPathState == 0) {
   //   // Hold on last state
   //   for (unsigned int i = 0; i < nblocks; i++) {
   //      xd[i] = 0;
   //      yd[i] = 0;
   //   }
   //   movingFlg = false;
   //   moveTimer = 0;
   //}
}

// Updates the solution path graphics
void Board::resetSolutionPath()
{
   curPathState = (nstates-1);
   updateBlockDeltaPositions();
   movingFlg = true;
   moveTimer = 0;
}

//------------------------------------------------------------------------------
// Updates the blocks' delta positions
//------------------------------------------------------------------------------
void Board::updateBlockDeltaPositions()
{
   if (curPathState < nstates) {
      const State* s = path[curPathState];
      if (s != 0) {
         for (unsigned int i = 0; i < nblocks; i++) {

            // Update the block position with the last deltas
            //  (where we are now)
            xp[i] = xp[i] + xd[i];
            yp[i] = yp[i] + yd[i];

            // compute the block position deltas for the current state
            //  (where we're going)
            const Block* b = s->getBlockByRefNum(blockId[i]);
            if (b != 0) {
               xd[i] = b->getX() - xp[i];
               yd[i] = b->getY() - yp[i];
            }
         }
      }
   }
}

//------------------------------------------------------------------------------
// drawFunc()
//------------------------------------------------------------------------------
void Board::drawFunc()
{
   for (unsigned int i = 0; i < nblocks; i++) {
      if (blocks[i] != 0) {
         glPushMatrix();
            glTranslated( (xp[i] + xd[i]*moveTimer), (yp[i] + yd[i]*moveTimer), 0.0);
            blocks[i]->draw();
         glPopMatrix();
      }
   }
}

//------------------------------------------------------------------------------
// Sets the Puzzle controller
//------------------------------------------------------------------------------
bool Board::setSlotPuzzle(Puzzle* const p)
{
   if (puzzle != 0) puzzle->unref();
   puzzle = p;
   if (puzzle != 0) puzzle->ref();
   return true;
}

//------------------------------------------------------------------------------
// Sets a list of the graphical templates for the blocks
//------------------------------------------------------------------------------
bool Board::setSlotTemplates(const Basic::PairStream* const p)
{
   if (templates != 0) templates->unref();
   templates = p;
   if (templates != 0) templates->ref();
   return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex() 
//------------------------------------------------------------------------------
Basic::Object* Board::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& Board::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   // Puzzle controller
   if (puzzle != 0) {
      indent(sout,i+j);
      sout << "puzzle: {" << std::endl;
      puzzle->serialize(sout,i+j+4,slotsOnly);
      indent(sout,i+j);
      sout << "}" << std::endl;
   }

   // Puzzle controller
   if (puzzle != 0) {
      indent(sout,i+j);
      sout << "puzzle: {" << std::endl;
      puzzle->serialize(sout,i+j+4,slotsOnly);
      indent(sout,i+j);
      sout << "}" << std::endl;
   }

   BaseClass::serialize(sout,i+j,true);

   if ( !slotsOnly ) {
      indent(sout,i);
      sout << ")" << std::endl;
   }

   return sout;
}

}  // End of Example namespace
}  // End of Eaagles namespace
