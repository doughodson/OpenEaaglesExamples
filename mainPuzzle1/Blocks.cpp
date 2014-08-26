
#include "Blocks.h"

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

bool operator>(const Block& b1, const Block& b2)
{
   bool gt = false;
   if (b1.getTypeId() > b2.getTypeId()) {
      gt = true;
   }
   else if (b1.getTypeId() == b2.getTypeId()) {
      if (b1.x > b2.x) {
         gt = true;
      }
      else if (b1.x == b2.x) {
         if (b1.y > b2.y)
            gt = true;
      }
   }
   return gt;
}


// Are two blocks equal
bool operator==(const Block& b1, const Block& b2)
{
   return ( (b1.getTypeId() == b2.getTypeId()) && (b1.x == b2.x) && (b1.y == b2.y) );
}


// Are two blocks not equal
bool operator!=(const Block& b1, const Block& b2)
{
   return ( (b1.getTypeId() != b2.getTypeId()) || (b1.x != b2.x) || (b1.y != b2.y) );
}

//------------------------------------------------------------------------------
// Block movement support
//------------------------------------------------------------------------------

// Move block by dx and dy; returns true if successful
bool Block::move(const int dx, const int dy)
{
   bool ok = testMove(dx,dy);
   if ( ok ) {
      x += dx;
      y += dy;
   }
   return ok;
}

// Tests to see if we can move dx, dy; returns true if we can
bool Block::testMove(const int dx, const int dy) const
{
   return (
         (x + dx) >= 1 &&
         (x + getSizeX() + dx - 1) <= BOARD_X_SIZE &&
         (y + dy) >= 1 &&
         (y + getSizeY() + dy - 1) <= BOARD_Y_SIZE
      );
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
unsigned int Block::computeHashValue(const unsigned int blockIndex, const unsigned int rehashCount) const
{
  unsigned int i;
  unsigned int a = 1;
  unsigned int b = 1;
  unsigned int c = 1;

  for (i = 0; i < rehashCount; i++) {
     a *= blockIndex;
     b *= x;
     c *= y;
  }

  b *= x;

  c *= y;
  c *= y;

  return a*b*c;
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
// Class: Block1x1
//==============================================================================

IMPLEMENT_SUBCLASS(Block1x1,"Block1x1")
EMPTY_SLOTTABLE(Block1x1)
EMPTY_SERIALIZER(Block1x1)

EMPTY_COPYDATA(Block1x1)
EMPTY_DELETEDATA(Block1x1)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block1x1::Block1x1()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
Block::BlockId Block1x1::getTypeId() const   { return Block::BLOCK_1X1; }
unsigned int Block1x1::getSizeX() const      { return 1; }
unsigned int Block1x1::getSizeY() const      { return 1; }



//==============================================================================
// Class: Block1x2
//==============================================================================

IMPLEMENT_SUBCLASS(Block1x2,"Block1x2")
EMPTY_SLOTTABLE(Block1x2)
EMPTY_SERIALIZER(Block1x2)

EMPTY_COPYDATA(Block1x2)
EMPTY_DELETEDATA(Block1x2)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block1x2::Block1x2()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
Block::BlockId Block1x2::getTypeId() const   { return Block::BLOCK_1X2; }
unsigned int Block1x2::getSizeX() const      { return 1; }
unsigned int Block1x2::getSizeY() const      { return 2; }



//==============================================================================
// Class: Block2x1
//==============================================================================

IMPLEMENT_SUBCLASS(Block2x1,"Block2x1")
EMPTY_SLOTTABLE(Block2x1)
EMPTY_SERIALIZER(Block2x1)

EMPTY_COPYDATA(Block2x1)
EMPTY_DELETEDATA(Block2x1)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block2x1::Block2x1()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
Block::BlockId Block2x1::getTypeId() const   { return Block::BLOCK_2X1; }
unsigned int Block2x1::getSizeX() const      { return 2; }
unsigned int Block2x1::getSizeY() const      { return 1; }



//==============================================================================
// Class: Block2x2
//==============================================================================

IMPLEMENT_SUBCLASS(Block2x2,"Block2x2")
EMPTY_SLOTTABLE(Block2x2)
EMPTY_SERIALIZER(Block2x2)

EMPTY_COPYDATA(Block2x2)
EMPTY_DELETEDATA(Block2x2)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Block2x2::Block2x2()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Access functions
//------------------------------------------------------------------------------
Block::BlockId Block2x2::getTypeId() const   { return Block::BLOCK_2X2; }
unsigned int Block2x2::getSizeX() const      { return 2; }
unsigned int Block2x2::getSizeY() const      { return 2; }


}  // End of Example namespace
}  // End of Eaagles namespace
