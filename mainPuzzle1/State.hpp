
#ifndef __State_H__
#define __State_H__

#include "openeaagles/base/Component.hpp"

#include <array>

namespace oe {
namespace base { class PairStream; }
}

class Block;
class Puzzle;

//------------------------------------------------------------------------------
// Class: State
//
// Description:  Puzzle state vector
//------------------------------------------------------------------------------
class State : public oe::base::Component
{
    DECLARE_SUBCLASS(State, oe::base::Component)

public:
   static const unsigned int MAX_BLOCKS = 30;         // Max number of blocks in each state

public:
   State();
   State(const State& org, const Block* const nb, const unsigned int idx);

   virtual int f() const              { return (g() + h()); }        // f() function
   virtual int g() const;                                            // g() function
   virtual int h() const;                                            // h() function
   virtual bool isExpanded() const    { return expanded; }           // Has this state been expanded?
   virtual int getGeneration() const  { return generation; }         // State's generation number

   virtual unsigned int getNumberOfBlocks() const { return nblocks; }   // Number of blocks
   virtual const Block* getBlock(const unsigned int n) const;           // Returns the n'th block (range: 1 .. getNumberOfBlocks())
   virtual const Block* getBlockByRefNum(const unsigned int refId) const;  // Returns the block with ref ID

   // Expand the state, s, and
   //  returns the state that matches the 'goal' state, if found, else zero
   virtual const State* expand(const State* const goal, Puzzle* const puz);

   // State's hash index; 'rh' is rehash count; 'max' is the maximum index
   virtual unsigned int hash(unsigned int rh, unsigned int max) const;

   friend bool operator==(const State& s1, const State& s2);
   friend bool operator!=(const State& s1, const State& s2);

   // Slot function(s)
   virtual bool setSlotBlocks(const oe::base::PairStream* const msg);

protected:
   //  create a new state (based on this one) and replace the block
   // at index, idx, with the new block, nb.
   const State* stateFactory(const Block* const nb, const unsigned int idx, const State* const goal, Puzzle* const puz);

   // Sets the state's array of blocks
   virtual unsigned int setBlocks(const Block* const newBlocks[], const unsigned int numNewBlocks);
   virtual void sortBlocks();
   virtual void clearBlocks();

private:
   std::array<const Block*, MAX_BLOCKS> blocks {};    // Our blocks
   unsigned int nblocks {};                           // Number of blocks
   bool expanded {};             // True if we've been expanded
   int  generation {};           // Generation index
};

#endif
