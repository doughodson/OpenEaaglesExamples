
#include "Puzzle.hpp"
#include "State.hpp"

#include "openeaagles/base/List.hpp"
#include <iostream>

using namespace oe;

IMPLEMENT_SUBCLASS(Puzzle, "Puzzle")

BEGIN_SLOTTABLE(Puzzle)
    "initState",      //  1: Our initial state
    "goalState",      //  2: Our goal state
END_SLOTTABLE(Puzzle)

BEGIN_SLOT_MAP(Puzzle)
    ON_SLOT( 1, setInitState, State )
    ON_SLOT( 2, setGoalState, State )
END_SLOT_MAP()

Puzzle::Puzzle()
{
   STANDARD_CONSTRUCTOR()
}

void Puzzle::copyData(const Puzzle& org, const bool)
{
   BaseClass::copyData(org);

   setInitState(nullptr);
   if (org.initState != nullptr) {
      setInitState( org.initState->clone() );
   }

   setGoalState(nullptr);
   if (org.goalState != nullptr) {
      setGoalState( org.goalState->clone() );
   }

   // Clear the tables and lists -- we're not going to copy them
   clearHashTable();
   clearOpenList();
}

void Puzzle::deleteData()
{
   setInitState(nullptr);
   setGoalState(nullptr);
   clearOpenList();
   clearHashTable();
}

//------------------------------------------------------------------------------
// solve() -- try to solve the puzzle
//------------------------------------------------------------------------------
const State* Puzzle::solve()
{
   // ---
   // Until we found the goal or we're out of states to check,
   // expand, expand, expand, ...
   // ---
   const State* found = nullptr;
   State* current = getOpen();
   int i = 0;
   while ( (current != nullptr)  && (found == nullptr) ) {
      if (i == (i/100)*100) {
         std::cout << "i: " << i << ", states= " << getHashEntries();
         std::cout << ", current=" << current;
         std::cout << ", f() = " << current->f();
         std::cout << ", g() = " << current->g();
         std::cout << ", h() = " << current->h();
         std::cout << std::endl;
      }
      found = current->expand(goalState, this);
      //{
      //   unsigned int icount = 0;
      //   std::cout << "Open List ==============" << std::endl;
      //   const base::List::Item* item = openStates->getFirstItem();
      //   while (item != 0 && icount < 10) {
      //      const State* s = (const State*) item->getValue();
      //      //s->serialize(std::cout);
      //      std::cout << icount << " - f = " << s->f() << ", g = " << s->g() << ", h = " << s->h() << std::endl;
      //      item = item->getNext();
      //      icount++;
      //   }
      //}
      current = getOpen();
      i++;
   }
   std::cout << "Puzzle::solve() Number of states: " << getHashEntries() << std::endl;
   std::cout << "Puzzle::solve() Number expanded : " << i << std::endl;
   return found;
}

//------------------------------------------------------------------------------
// Print the states from a terminal state, tstate, back to the initial state
//------------------------------------------------------------------------------
void Puzzle::printPath(const State* tstate) const
{
   if ( tstate != nullptr ) {
      std::cout << std::endl;
      const State* s = tstate;
      while (s->getGeneration() > 0) {
         std::cout << std::endl;
         s->serialize(std::cout);
         s = static_cast<const State*>( s->container() );
      }
      std::cout << std::endl;
      s->serialize(std::cout);
   }
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

bool Puzzle::setInitState(State* const s)
{
   if (initState != nullptr) initState->unref();
   initState = s;
   if (initState != nullptr) {
      initState->ref();
      // Add to our lists (to be processed)
      putHash(initState);
      putOpen(initState);
   }
   return true;
}

bool Puzzle::setGoalState(State* const g)
{
   if (goalState != nullptr) goalState->unref();
   goalState = g;
   if (goalState != nullptr) {
      goalState->ref();
      goalState->defineBoard(this);
   }
   return true;
}

//------------------------------------------------------------------------------
// Open state list support functions
//------------------------------------------------------------------------------

// Returns the number of 'open' states
unsigned int Puzzle::getOpenEntries() const
{
   unsigned int n = 0;
   if (openStates != nullptr) {
      n = openStates->entries();
   }
   return n;
}

// Returns the next state from the 'open' list
State* Puzzle::getOpen()
{
   State* p = nullptr;
   if (openStates != nullptr) {
      p = static_cast<State*>( openStates->get() );
   }
   return p;
}

// Puts a state on to the 'open' list
void Puzzle::putOpen(State* const s)
{
   if (openStates == nullptr) {
      // create the list (as needed)
      openStates = new base::List();
   }

   if (s != nullptr) {
      // Create a new list item for this state and get the state's f() value
      const auto newItem = new base::List::Item();
      newItem->value = s;
      s->ref();
      int f = s->f();

      // Find where in the list to insert this new state (based on their f() values)
      base::List::Item* item = openStates->getFirstItem();
      base::List::Item* refItem = nullptr;
      while (item != nullptr && refItem == nullptr) {
         const auto p = static_cast<const State*>( item->getValue() );
         if (f < p->f()) {
            refItem = item;
         }
         item = item->getNext();
      }

      // Insert our new state
      openStates->insert(newItem, refItem);
   }
}

// Removes this state from the 'open' list
void Puzzle::removeOpen(const State* const s)
{
   if (s != nullptr && openStates != nullptr) {
      openStates->remove(s);
   }
}

// Clears the open states list
void Puzzle::clearOpenList()
{
   if (openStates != nullptr) {
      openStates->clear();
      openStates->unref();
      openStates = nullptr;
   }
}

//------------------------------------------------------------------------------
// Hash table support functions
//------------------------------------------------------------------------------

// Adds a state to the hash table; returns true if successful
bool Puzzle::putHash(const State* const s)
{
   bool added = false;

   if (s != nullptr) {

      // Get our new state's g() value
      int g = s->g();

      // ---
      // 1) get a hash value for the state and use it as an index into the table
      // 2) if the table index is already in use, check to see if it is the same state
      //    a) if it's the same state:  leave with a false
      //    b) if it's not the same state, rehash
      // ---
      bool rehash = true;
      for (unsigned int rh = 0; !added && rehash && rh < MAX_REHASH; rh++) {

         // Compute the state's hash value for use as the hash table index
         unsigned int idx = s->hash(rh,MAX_STATES);

         if (hashTable[idx] == nullptr) {
            // when we found an empty slot in the table
            rehash = false;
            s->ref();
            hashTable[idx] = s;
            nhe++;
            added = true;
         }
         else if ( *s  == *(hashTable[idx]) ) {

            // We've found that the state is already in the table
            rehash = false;

            // If the state in the table has not been expanded yet, then check
            // to see if our new state is closer to the start than the one
            // already in the table
            if ( !hashTable[idx]->isExpanded() && (g < hashTable[idx]->g()) ) {
               removeOpen(hashTable[idx]);
               hashTable[idx]->unref();
               s->ref();
               hashTable[idx] = s;
               added = true;
            }

         }
         else {
            //std::cout << "hash: rh = " << rh;
            //std::cout << ", idx = " << idx;
            //std::cout << "; table position in use -- rehash";
            //std::cout << std::endl;
         }

      }  // End of hash/rehash loop

   }  // End s != 0

   return added;
}

// Clears the hash table
void Puzzle::clearHashTable()
{
   for (unsigned int i = 0; i < MAX_STATES; i++) {
      if (hashTable[i] != nullptr) {
         hashTable[i]->unref();
         hashTable[i] = nullptr;
      }
   }
   nhe = 0;
}

std::ostream& Puzzle::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   // Initial state
   if (initState != nullptr) {
      indent(sout,i+j);
      sout << "initState: {" << std::endl;
      initState->serialize(sout,i+j+4,slotsOnly);
      indent(sout,i+j);
      sout << "}" << std::endl;
   }

   // Goal state
   if (goalState != nullptr) {
      indent(sout,i+j);
      sout << "goalState: {" << std::endl;
      goalState->serialize(sout,i+j+4,slotsOnly);
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
