//------------------------------------------------------------------------------
// Class:  Puzzle
//------------------------------------------------------------------------------
#ifndef __Puzzle_H_05CE6F5B_A367_4b67_B678_9141D79810B2__
#define __Puzzle_H_05CE6F5B_A367_4b67_B678_9141D79810B2__

#include "openeaagles/basic/Component.h"

namespace Eaagles {
   namespace Basic {
      class List;
   }
namespace Puzzle {

class State;

//------------------------------------------------------------------------------
// Class:  Puzzle
// Base class:  Basic::Object-> Puzzle
//
// Description:  Puzzle engine
//
// GUID: {05CE6F5B-A367-4b67-B678-9141D79810B2}
//------------------------------------------------------------------------------
class Puzzle : public Basic::Component {
    DECLARE_SUBCLASS(Puzzle,Basic::Component)

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

   // Print the states from a terminal state, tstate, back to the inital state
   virtual void printPath(const State* tstate) const;

   // Adds a state to the hash table; returns true if successfull
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
   State*         initState;     // Initial (starting) state
   const State*   goalState;     // Goal (ending) state

   // Open list
   Basic::List*  openStates;   // List of 'open' states (still need to be expanded)
                                 // (list is ordered by the state's f() values)

   // HashTable
   const State* hashTable[MAX_STATES]; // Hash table (for quick lookup of states)
   unsigned int nhe;                   // Number of entries in hash table
};

}  // End of Puzzle namespace
}  // End of Eaagles namespace

#endif /* __Puzzle_H_05CE6F5B_A367_4b67_B678_9141D79810B2__ */
