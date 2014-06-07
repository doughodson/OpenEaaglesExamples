//------------------------------------------------------------------------------
// Class:  Block1, Block2, ... Block15, Block
//------------------------------------------------------------------------------
#include "Blocks.h"
#include "Puzzle.h"

#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/List.h"

namespace Eaagles {
namespace Example {

//==============================================================================
// Class: Block
//==============================================================================

IMPLEMENT_ABSTRACT_SUBCLASS(Block,"PuzzleBlock")

//------------------------------------------------------------------------------
// Slot table for this form type
//------------------------------------------------------------------------------
BEGIN_SLOTTABLE(Block)
    "position",      //  1: initial position vector 
    "id",            //  2: Block's reference ID 
END_SLOTTABLE(Block)

//------------------------------------------------------------------------------
//  Map slot table to handles 
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(Block)
    ON_SLOT( 1, setSlotPosition, Basic::List)        
    ON_SLOT( 2, setSlotRefId, Basic::Integer)        
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block::Block()
{
   STANDARD_CONSTRUCTOR()

   x  = 0;
   y  = 0;
   refId = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Block::copyData(const Block& org, const bool)
{
   BaseClass::copyData(org);

   x  = org.x;
   y  = org.y;
   refId = org.refId;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Block::deleteData()
{
}

//------------------------------------------------------------------------------
// Comparison functions
//------------------------------------------------------------------------------

int compare(const Block& b1, const Block& b2)
{
   if ( b1.getTypeId() > b2.getTypeId() ) {
      // Block b1's type id is greater than b2's type id
      return 1;
   }
   else if ( b1.getTypeId() < b2.getTypeId() ) {
      // Block b1's type id is less than b2's type id
      return -1;
   }
   else {
      // When block type ids are the same, then it's position
      return comparePosition(b1, b2);
   }
}

int comparePosition(const Block& b1, const Block& b2)
{
   if ((b1.x == b2.x) && (b1.y == b2.y)) {
      return 0; // Equal 
   }
   else if (b1.y > b2.y) {
      // if b1 is at a higher row than b2, then it's "less than"
      // (e.g., higher rows first)
      return -1;
   }
   else if (b1.y < b2.y) {
      // if b1 is at a lower row than b2, then it's "greater than"
      // (e.g., higher rows first)
      return  1;
   }
   else {
      // y values are equal then x values must be different
      if (b1.x > b2.x) return 1;
      else return -1;
   }
}

//------------------------------------------------------------------------------
// Block movement support
//------------------------------------------------------------------------------

// Move block by dx and dy; returns true if successful
bool Block::move(const int dx, const int dy, const Puzzle* const puz)
{
   bool ok = testMove(dx,dy,puz);
   if ( ok ) {
      x += dx;
      y += dy;
   }
   return ok;
}

// Tests to see if we can move dx, dy; returns true if we can
bool Block::testMove(const int dx, const int dy, const Puzzle* const puz) const
{
   bool ok = false;
   if (puz != 0) {
      ok = (
            (x + dx) >= 1 &&
            (x + getSizeX() + dx - 1) <= puz->getBoardSizeX() &&
            (y + dy) >= 1 &&
            (y + getSizeY() + dy - 1) <= puz->getBoardSizeX()
         );
   }
   return ok;
}

//------------------------------------------------------------------------------
// collisionCheck() -- True if we collide with the test block
//------------------------------------------------------------------------------
bool Block::collisionCheck(const Block* const b2) const
{
  bool c = false;
  for (unsigned int i = 0; i < getSizeX() && !c; i++)
    for (unsigned int j = 0; j < getSizeY() && !c; j++) {
       unsigned int xx = x + i;
       unsigned int yy = y + j;
       if ( xx >= b2->x && xx <= (b2->x + b2->getSizeX() - 1) &&
            yy >= b2->y && yy <= (b2->y + b2->getSizeY() - 1) ) c = true;
    }
  return c;
}

//------------------------------------------------------------------------------
// computeHashValue() -- Compute a hash value for this block
//------------------------------------------------------------------------------
unsigned int Block::computeHashValue(const unsigned int, const unsigned int rehashCount) const
{
  unsigned int i;
  unsigned int a = 111;
  unsigned int b = 222;
  unsigned int c = 333;

  for (i = 0; i < rehashCount; i++) {
     //a *= blockIndex;
     a *= getTypeId();
     b *= x;
     c *= y;
  }

  b *= (x+1);
  b += x;

  c *= y;
  c *= (y+1);
  c += y;

  a += x;
  b += y;
  c += getTypeId();

  a += y;
  b += getTypeId();
  c += x;

  return a*b*c+a+b+c;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

// Initial position
bool Block::setInitPosition(const unsigned int ix, const unsigned int iy)
{
   x = ix;
   y = iy;
   return true;
}

// Sets the block's reference ID number
bool Block::setReferenceID(const unsigned int v)
{
   refId = v;
   return true;
}

//------------------------------------------------------------------------------
// Slot function(s)
//------------------------------------------------------------------------------
bool Block::setSlotPosition(const Basic::List* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int values[2];
      int n = msg->getNumberList(values, 2);
      if (n == 2) {
         ok = setInitPosition(values[0], values[1]);
      }
   }
   return ok;
}

bool Block::setSlotRefId(const Basic::Integer* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int i = msg->getInt();
      if (i >= 0) {
         unsigned int id = static_cast<unsigned int>(i);
         ok = setReferenceID(id);
      }
   }
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* Block::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& Block::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   indent(sout, i+j);
   sout << "position: [ " << x << " " << y << " ]" << std::endl;

   BaseClass::serialize(sout,i+j,true);

   if ( !slotsOnly ) {
      indent(sout,i);
      sout << ")" << std::endl;
   }

   return sout;
}


//==============================================================================
// Class: Block1
//==============================================================================

IMPLEMENT_SUBCLASS(Block1,"Block1")
EMPTY_SLOTTABLE(Block1)
EMPTY_SERIALIZER(Block1)

EMPTY_COPYDATA(Block1)
EMPTY_DELETEDATA(Block1)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block1::Block1()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block1::getTypeId() const   { return 1; }
unsigned int Block1::getSizeX() const      { return 1; }
unsigned int Block1::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block2
//==============================================================================

IMPLEMENT_SUBCLASS(Block2,"Block2")
EMPTY_SLOTTABLE(Block2)
EMPTY_SERIALIZER(Block2)

EMPTY_COPYDATA(Block2)
EMPTY_DELETEDATA(Block2)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block2::Block2()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block2::getTypeId() const   { return 2; }
unsigned int Block2::getSizeX() const      { return 1; }
unsigned int Block2::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block3
//==============================================================================

IMPLEMENT_SUBCLASS(Block3,"Block3")
EMPTY_SLOTTABLE(Block3)
EMPTY_SERIALIZER(Block3)

EMPTY_COPYDATA(Block3)
EMPTY_DELETEDATA(Block3)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block3::Block3()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block3::getTypeId() const   { return 3; }
unsigned int Block3::getSizeX() const      { return 1; }
unsigned int Block3::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block4
//==============================================================================

IMPLEMENT_SUBCLASS(Block4,"Block4")
EMPTY_SLOTTABLE(Block4)
EMPTY_SERIALIZER(Block4)

EMPTY_COPYDATA(Block4)
EMPTY_DELETEDATA(Block4)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block4::Block4()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block4::getTypeId() const   { return 4; }
unsigned int Block4::getSizeX() const      { return 1; }
unsigned int Block4::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block5
//==============================================================================

IMPLEMENT_SUBCLASS(Block5,"Block5")
EMPTY_SLOTTABLE(Block5)
EMPTY_SERIALIZER(Block5)

EMPTY_COPYDATA(Block5)
EMPTY_DELETEDATA(Block5)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block5::Block5()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block5::getTypeId() const   { return 5; }
unsigned int Block5::getSizeX() const      { return 1; }
unsigned int Block5::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block6
//==============================================================================

IMPLEMENT_SUBCLASS(Block6,"Block6")
EMPTY_SLOTTABLE(Block6)
EMPTY_SERIALIZER(Block6)

EMPTY_COPYDATA(Block6)
EMPTY_DELETEDATA(Block6)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block6::Block6()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block6::getTypeId() const   { return 6; }
unsigned int Block6::getSizeX() const      { return 1; }
unsigned int Block6::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block7
//==============================================================================

IMPLEMENT_SUBCLASS(Block7,"Block7")
EMPTY_SLOTTABLE(Block7)
EMPTY_SERIALIZER(Block7)

EMPTY_COPYDATA(Block7)
EMPTY_DELETEDATA(Block7)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block7::Block7()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block7::getTypeId() const   { return 7; }
unsigned int Block7::getSizeX() const      { return 1; }
unsigned int Block7::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block8
//==============================================================================

IMPLEMENT_SUBCLASS(Block8,"Block8")
EMPTY_SLOTTABLE(Block8)
EMPTY_SERIALIZER(Block8)

EMPTY_COPYDATA(Block8)
EMPTY_DELETEDATA(Block8)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block8::Block8()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block8::getTypeId() const   { return 8; }
unsigned int Block8::getSizeX() const      { return 1; }
unsigned int Block8::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block9
//==============================================================================

IMPLEMENT_SUBCLASS(Block9,"Block9")
EMPTY_SLOTTABLE(Block9)
EMPTY_SERIALIZER(Block9)

EMPTY_COPYDATA(Block9)
EMPTY_DELETEDATA(Block9)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block9::Block9()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block9::getTypeId() const   { return 9; }
unsigned int Block9::getSizeX() const      { return 1; }
unsigned int Block9::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block10
//==============================================================================

IMPLEMENT_SUBCLASS(Block10,"Block10")
EMPTY_SLOTTABLE(Block10)
EMPTY_SERIALIZER(Block10)

EMPTY_COPYDATA(Block10)
EMPTY_DELETEDATA(Block10)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block10::Block10()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block10::getTypeId() const     { return 10; }
unsigned int Block10::getSizeX() const      { return 1; }
unsigned int Block10::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block11
//==============================================================================

IMPLEMENT_SUBCLASS(Block11,"Block11")
EMPTY_SLOTTABLE(Block11)
EMPTY_SERIALIZER(Block11)

EMPTY_COPYDATA(Block11)
EMPTY_DELETEDATA(Block11)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block11::Block11()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block11::getTypeId() const     { return 11; }
unsigned int Block11::getSizeX() const      { return 1; }
unsigned int Block11::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block12
//==============================================================================

IMPLEMENT_SUBCLASS(Block12,"Block12")
EMPTY_SLOTTABLE(Block12)
EMPTY_SERIALIZER(Block12)

EMPTY_COPYDATA(Block12)
EMPTY_DELETEDATA(Block12)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block12::Block12()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block12::getTypeId() const     { return 12; }
unsigned int Block12::getSizeX() const      { return 1; }
unsigned int Block12::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block13
//==============================================================================

IMPLEMENT_SUBCLASS(Block13,"Block13")
EMPTY_SLOTTABLE(Block13)
EMPTY_SERIALIZER(Block13)

EMPTY_COPYDATA(Block13)
EMPTY_DELETEDATA(Block13)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block13::Block13()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block13::getTypeId() const     { return 13; }
unsigned int Block13::getSizeX() const      { return 1; }
unsigned int Block13::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block14
//==============================================================================

IMPLEMENT_SUBCLASS(Block14,"Block14")
EMPTY_SLOTTABLE(Block14)
EMPTY_SERIALIZER(Block14)

EMPTY_COPYDATA(Block14)
EMPTY_DELETEDATA(Block14)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block14::Block14()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block14::getTypeId() const     { return 14; }
unsigned int Block14::getSizeX() const      { return 1; }
unsigned int Block14::getSizeY() const      { return 1; }


//==============================================================================
// Class: Block15
//==============================================================================

IMPLEMENT_SUBCLASS(Block15,"Block15")
EMPTY_SLOTTABLE(Block15)
EMPTY_SERIALIZER(Block15)

EMPTY_COPYDATA(Block15)
EMPTY_DELETEDATA(Block15)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block15::Block15()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
unsigned int Block15::getTypeId() const     { return 15; }
unsigned int Block15::getSizeX() const      { return 1; }
unsigned int Block15::getSizeY() const      { return 1; }


}  // End of Example namespace
}  // End of Eaagles namespace
