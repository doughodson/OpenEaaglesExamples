
#ifndef __Puzzle_H__
#define __Puzzle_H__

#include "openeaagles/base/Component.hpp"

#include <array>

namespace oe {
namespace base { class List; }
}
class State;

//------------------------------------------------------------------------------
// Class:  Puzzle
//
// Description:  Puzzle engine
//------------------------------------------------------------------------------
class Puzzle : public oe::base::Component
{
    DECLARE_SUBCLASS(Puzzle, oe::base::Component)

public:
   static const unsigned int MAX_STATES = 1000000;    // Max number of states
   static const unsigned int MAX_REHASH = 20;         // Max number of rehash tries

public:
   Puzzle();

   unsigned int getHashEntries() const    { return nhe; }         // Returns the number of entries in the hash table
   unsigned int getOpenEntries() const;                           // Returns the number of 'open' states

   const State* getInitState() const      { return initState; }   // Returns our 'initial' or starting state
   const State* getGoalState() const      { return goalState; }   // Returns the 'goal' state

   // Solve (or try) the puzzle
   virtual const State* solve();

   // Print the states from a terminal state, tstate, back to the initial state
   virtual void printPath(const State* tstate) const;

   // Adds a state to the hash table; returns true if successful
   virtual bool putHash(const State* const s);

   // Adds a state to the 'open' list
   virtual void putOpen(State* const s);

protected:
   virtual State* getOpen();                          // Returns the next state from the 'open' list
   virtual void removeOpen(const State* const s);     // Removes this state from the 'open' list
   virtual void clearOpenList();                      // Clears the open states list

   virtual bool setInitState(State* const s);         // Sets the initial (starting) state
   virtual bool setGoalState(const State* const g);   // Sets the goal (ending) state

   virtual void clearHashTable();                     // Clears the hash table

private:
   State*       initState {};       // Initial (starting) state
   const State* goalState {};       // Goal (ending) state

   // Open list
   oe::base::List* openStates {};   // List of 'open' states (still need to be expanded)
                                    // (list is ordered by the state's f() values)

   // HashTable
   std::array<const State*, MAX_STATES> hashTable {};  // Hash table (for quick lookup of states)
   unsigned int nhe {};                                // Number of entries in hash table
};

#endif
