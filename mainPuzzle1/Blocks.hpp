
#ifndef __Block_H__
#define __Block_H__

#include "openeaagles/base/Object.hpp"

namespace oe
{
namespace base
{
class List;
class Integer;
}
}

//------------------------------------------------------------------------------
// Class:  Block
// Description: Abstract puzzle block
//
// Block locations (x, y): lower left is (1,1)
// Block type IDs are unique to blocks of the same type (e.g., size and shape)
//------------------------------------------------------------------------------
class Block : public oe::base::Object
{
   DECLARE_SUBCLASS(Block, oe::base::Object)

 public:
   static const unsigned int BOARD_X_SIZE = 4;
   static const unsigned int BOARD_Y_SIZE = 5;

   // Block type IDs
   enum BlockId
   {
      BLOCK_2X2 = 1, // 2x2 (goal) type block (must start at 1)
      BLOCK_1X1,     // 1x1 type block
      BLOCK_2X1,     // 2x1 type block
      BLOCK_1X2      // 1x2 type block
   };

 public:
   Block();

   unsigned int getX() const { return x; } // Blocks X (horizontal) position; one is most left
   unsigned int getY() const { return y; } // blocks Y (vertical) position; one is at the bottom

   unsigned int getReferenceID() const { return refId; } // Block's reference ID number

   virtual BlockId getTypeId() const = 0;     // Blocks type ID
   virtual unsigned int getSizeX() const = 0; // Block's X size
   virtual unsigned int getSizeY() const = 0; // Block's Y size

   virtual bool testMove(const int dx, const int dy) const;  // Tests to see if we can move dx, dy; returns true if we can
   virtual bool move(const int dx, const int dy);            // Tries to move block by dx and dy; returns true if successful
   virtual bool collisionCheck(const Block *const b2) const; // True if we collide with the test block

   friend bool operator>(const Block &b1, const Block &b2);
   friend bool operator==(const Block &b1, const Block &b2);
   friend bool operator!=(const Block &b1, const Block &b2);

   // Compute a hash value for this block
   virtual unsigned int computeHashValue(const unsigned int blockIndex, const unsigned int rehashCount) const;

   // Slot function(s)
   virtual bool setSlotPosition(const oe::base::List *const msg);
   virtual bool setSlotRefId(const oe::base::Integer *const msg);

 protected:
   virtual bool setInitPosition(const unsigned int x, const unsigned int y);
   virtual bool setReferenceID(const unsigned int v); // Sets the block's reference ID number

 private:
   unsigned int x{}, y{}; // Location
   unsigned int refId{};  // Block's ref ID number
};

//------------------------------------------------------------------------------
// Class:  Block1x1
// Base class:  base::Object-> Block -> Block1x1
// Description:  Block size 1 by 1
//------------------------------------------------------------------------------
class Block1x1 : public Block
{
   DECLARE_SUBCLASS(Block1x1, Block)
 public:
   Block1x1();

   virtual BlockId getTypeId() const override;
   virtual unsigned int getSizeX() const override;
   virtual unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block1x2
// Base class:  base::Object-> Block -> Block1x2
// Description:  Block size 1 by 2
//------------------------------------------------------------------------------
class Block1x2 : public Block
{
   DECLARE_SUBCLASS(Block1x2, Block)
 public:
   Block1x2();

   virtual BlockId getTypeId() const override;
   virtual unsigned int getSizeX() const override;
   virtual unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block2x1
// Base class:  base::Object-> Block -> Block2x1
// Description:  Block size 2 by 1
//------------------------------------------------------------------------------
class Block2x1 : public Block
{
   DECLARE_SUBCLASS(Block2x1, Block)
 public:
   Block2x1();

   virtual BlockId getTypeId() const override;
   virtual unsigned int getSizeX() const override;
   virtual unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block2x2
// Base class:  base::Object-> Block -> Block2x2
// Description:  Block size 2 by 2
//------------------------------------------------------------------------------
class Block2x2 : public Block
{
   DECLARE_SUBCLASS(Block2x2, Block)
 public:
   Block2x2();

   virtual BlockId getTypeId() const override;
   virtual unsigned int getSizeX() const override;
   virtual unsigned int getSizeY() const override;
};

#endif
