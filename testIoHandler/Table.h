//------------------------------------------------------------------------------
// Class: Table
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_Table_H__
#define __Eaagles_Test_Table_H__

#include "openeaagles/basicGL/Field.h"

namespace Eaagles {
   namespace Basic { class Number; class PairStream; }

namespace Test {

//------------------------------------------------------------------------------
// Class: Table
// Description: Manages a table
//
// Factory name: Table
// Slots:
//    rows     <Number>     ! Number of rows (default: 1)
//    spacing  <Number>     ! Spacing between rows (default: 1)
//    columns  <PairStream> ! Column descriptions: list of items in each row
//------------------------------------------------------------------------------
class Table : public BasicGL::Field
{
   DECLARE_SUBCLASS(Table,BasicGL::Field)

public:
   Table();

   virtual const Basic::PairStream* getColumns() const;
   virtual unsigned int getNumberOfRows() const;

   // Slot functions
   virtual bool setSlotRows(Basic::Number* const);
   virtual bool setSlotSpacing(Basic::Number* const);
   virtual bool setSlotColumns(Basic::PairStream* const);

   // BasicGL::Field class interface
   virtual int line() const;
   virtual int line(const int ll);
   virtual int column() const;
   virtual int column(const int cc);

   // Basic::Component class interface
   virtual void reset();

private:
   void initData();
   void build();        // Builds the table into our components
   void position();     // Positions the table

   unsigned int  rows;     // Number of rows in table
   unsigned int  spacing;  // Spacing between rows (default: 1)
   const Basic::PairStream* columns;  // columns items
};

} // End of Test namespace
} // End of Eaagles namespace

#endif

