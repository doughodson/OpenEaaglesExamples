//------------------------------------------------------------------------------
// Class:  Block1, Block2, ... Block15, Block
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_Blocks_H__
#define __Eaagles_Example_Blocks_H__

#include "openeaagles/basic/Object.h"

namespace Eaagles {
   namespace Basic { class List; class Integer; }

namespace Example {

class Puzzle;

//------------------------------------------------------------------------------
// Class:  Block
// Base class:  Basic::Object-> Block
//
// Description:  Abstract puzzle block
//
// Block locations (x, y): lower left is (1,1)
// Block type IDs are unique to blocks of the same type (e.g., size and shape)
//------------------------------------------------------------------------------
class Block : public Basic::Object
{
    DECLARE_SUBCLASS(Block, Basic::Object)

public:
   Block();

   unsigned int getX() const        { return x; }              // Blocks X (horizontal) position; one is most left
   unsigned int getY() const        { return y; }              // blocks Y (vertical) position; one is at the bottom

   unsigned int getReferenceID() const { return refId; }       // Block's reference ID number

   virtual unsigned int getTypeId() const = 0;                      // Blocks type ID
   virtual unsigned int getSizeX() const = 0;                  // Block's X size
   virtual unsigned int getSizeY() const = 0;                  // Block's Y size

   // Tests to see if we can move dx, dy; returns true if we can
   virtual bool testMove(const int dx, const int dy, const Puzzle* const puz) const;

   // Tries to move block by dx and dy; returns true if successful
   virtual bool move(const int dx, const int dy, const Puzzle* const puz);

   // True if we collide with the test block
   virtual bool collisionCheck(const Block* const b2) const;

   friend int compare(const Block& b1, const Block& b2);
   friend int comparePosition(const Block& b1, const Block& b2);

   // Compute a hash value for this block
   virtual unsigned int computeHashValue(const unsigned int blockIndex, const unsigned int rehashCount) const;

   // Slot function(s)
   virtual bool setSlotPosition(const Basic::List* const msg);
   virtual bool setSlotRefId(const Basic::Integer* const msg);

protected:
   virtual bool setInitPosition(const unsigned int x, const unsigned int y);
   virtual bool setReferenceID(const unsigned int v);          // Sets the block's reference ID number

private:
   unsigned int   x,y;     // Location
   unsigned int   refId;   // Block's ref ID number
};

//------------------------------------------------------------------------------
// Class:  Block1
//------------------------------------------------------------------------------
class Block1 : public Block {
    DECLARE_SUBCLASS(Block1,Block)
public:
   Block1();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block2
//------------------------------------------------------------------------------
class Block2 : public Block {
    DECLARE_SUBCLASS(Block2,Block)
public:
   Block2();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block3
//------------------------------------------------------------------------------
class Block3 : public Block {
    DECLARE_SUBCLASS(Block3,Block)
public:
   Block3();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block4
//------------------------------------------------------------------------------
class Block4 : public Block {
    DECLARE_SUBCLASS(Block4,Block)
public:
   Block4();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block5
//------------------------------------------------------------------------------
class Block5 : public Block {
    DECLARE_SUBCLASS(Block5,Block)
public:
   Block5();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block6
//------------------------------------------------------------------------------
class Block6 : public Block {
    DECLARE_SUBCLASS(Block6,Block)
public:
   Block6();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block7
//------------------------------------------------------------------------------
class Block7 : public Block {
    DECLARE_SUBCLASS(Block7,Block)
public:
   Block7();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block8
//------------------------------------------------------------------------------
class Block8 : public Block {
    DECLARE_SUBCLASS(Block8,Block)
public:
   Block8();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block9
//------------------------------------------------------------------------------
class Block9 : public Block {
    DECLARE_SUBCLASS(Block9,Block)
public:
   Block9();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block10
//------------------------------------------------------------------------------
class Block10 : public Block {
    DECLARE_SUBCLASS(Block10,Block)
public:
   Block10();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block11
//------------------------------------------------------------------------------
class Block11 : public Block {
    DECLARE_SUBCLASS(Block11,Block)
public:
   Block11();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block12
//------------------------------------------------------------------------------
class Block12 : public Block {
    DECLARE_SUBCLASS(Block12,Block)
public:
   Block12();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block13
//------------------------------------------------------------------------------
class Block13 : public Block {
    DECLARE_SUBCLASS(Block13,Block)
public:
   Block13();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block14
//------------------------------------------------------------------------------
class Block14 : public Block {
    DECLARE_SUBCLASS(Block14,Block)
public:
   Block14();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

//------------------------------------------------------------------------------
// Class:  Block15
//------------------------------------------------------------------------------
class Block15 : public Block {
    DECLARE_SUBCLASS(Block15,Block)
public:
   Block15();

   unsigned int getTypeId() const override;
   unsigned int getSizeX() const override;
   unsigned int getSizeY() const override;
};

}  // End of Example namespace
}  // End of Eaagles namespace

#endif
