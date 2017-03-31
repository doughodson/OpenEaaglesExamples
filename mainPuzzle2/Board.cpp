
#include "Board.hpp"
#include "Puzzle.hpp"
#include "State.hpp"
#include "Blocks.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"

using namespace oe;

IMPLEMENT_SUBCLASS(Board, "PuzzleBoard")

BEGIN_SLOTTABLE(Board)
    "puzzle",      //  1: Our puzzle controller
    "templates",   //  2: List of block templates (slot numbers MUST match block type IDs)
END_SLOTTABLE(Board)

BEGIN_SLOT_MAP(Board)
    ON_SLOT( 1, setSlotPuzzle,    Puzzle )
    ON_SLOT( 2, setSlotTemplates, base::PairStream )
END_SLOT_MAP()

Board::Board()
{
   STANDARD_CONSTRUCTOR()
}

void Board::copyData(const Board& org, const bool)
{
   BaseClass::copyData(org);

   setSlotPuzzle(nullptr);
   if (org.puzzle != nullptr) {
      setSlotPuzzle( org.puzzle->clone() );
   }

   setSlotTemplates(nullptr);
   if (org.templates != nullptr) {
      setSlotTemplates( org.templates->clone() );
   }

   // Clear the solution path
   for (unsigned int i = 0; i < MAX_STATES; i++) {
      path[i] = nullptr;
   }
   finalState = nullptr;
   nstates = 0;

   // Clear our blocks
   for (unsigned int i = 0; i < MAX_BLOCKS; i++) {
      blocks[i] = nullptr;
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

void Board::deleteData()
{
   setSlotPuzzle(nullptr);
   setSlotTemplates(nullptr);
   clearGraphics();
}

void Board::updateData(const double dt)
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
   if (puzzle != nullptr && finalState == nullptr && startupTimer > 1.0) {
      std::cout << "Starting to solve!" << std::endl;
      finalState = puzzle->solve();

      // ---
      // Get the path if we have a solution.
      // ---
      if (finalState != nullptr) {
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
   if (nblocks > 0 && finalState != nullptr) {
      updateSolutionPath(dt);
   }

}

//------------------------------------------------------------------------------
// Setup the list of graphics::Graphic objects for the initial blocks
// Returns the number of blocks
//------------------------------------------------------------------------------
unsigned int Board::setupBlockGraphics()
{
   clearGraphics();

   if (puzzle != nullptr && templates != nullptr) {
      const State* s = puzzle->getInitState();
      if (s != nullptr) {
         bool finished = false;
         for (unsigned int i = 0; i < MAX_BLOCKS && !finished; i++) {
            const Block* b = s->getBlock(i+1);
            if (b != nullptr) {
               unsigned int typeId = b->getTypeId();
               const base::Pair* pair = templates->getPosition(typeId);
               if (pair != nullptr) {
                  const auto g = dynamic_cast<const graphics::Graphic*>( pair->object() );
                  if (g != nullptr) {
                     // Ok, we've found a graphics::Graphic to draw this block!
                     blocks[nblocks] = g->clone();
                     blocks[nblocks]->container(this);
                     blockId[nblocks] = b->getReferenceID();
                     xp[nblocks] = static_cast<double>(b->getX());
                     yp[nblocks] = static_cast<double>(b->getY());
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

// Clears the list of graphics::Graphic objects for the blocks
void Board::clearGraphics()
{
   while (nblocks > 0) {
      nblocks--;
      blocks[nblocks]->unref();
      blocks[nblocks] = nullptr;
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
void Board::updateSolutionPath(const double dt)
{
   if (movingFlg) {
      // Wait while we move between states
      moveTimer += (dt*2.0);
      if (moveTimer > 1.0) {
         moveTimer = 1.0;
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
      if (s != nullptr) {
         for (unsigned int i = 0; i < nblocks; i++) {

            // Update the block position with the last deltas
            //  (where we are now)
            xp[i] = xp[i] + xd[i];
            yp[i] = yp[i] + yd[i];

            // compute the block position deltas for the current state
            //  (where we're going)
            const Block* b = s->getBlockByRefNum(blockId[i]);
            if (b != nullptr) {
               xd[i] = b->getX() - xp[i];
               yd[i] = b->getY() - yp[i];
            }
         }
      }
   }
}

void Board::drawFunc()
{
   for (unsigned int i = 0; i < nblocks; i++) {
      if (blocks[i] != nullptr) {
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
   if (puzzle != nullptr) puzzle->unref();
   puzzle = p;
   if (puzzle != nullptr) puzzle->ref();
   return true;
}

//------------------------------------------------------------------------------
// Sets a list of the graphical templates for the blocks
//------------------------------------------------------------------------------
bool Board::setSlotTemplates(const base::PairStream* const p)
{
   if (templates != nullptr) templates->unref();
   templates = p;
   if (templates != nullptr) templates->ref();
   return true;
}

std::ostream& Board::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   // Puzzle controller
   if (puzzle != nullptr) {
      indent(sout,i+j);
      sout << "puzzle: {" << std::endl;
      puzzle->serialize(sout,i+j+4,slotsOnly);
      indent(sout,i+j);
      sout << "}" << std::endl;
   }

   // Puzzle controller
   if (puzzle != nullptr) {
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
