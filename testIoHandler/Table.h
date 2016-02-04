//------------------------------------------------------------------------------
// Class: Table
//------------------------------------------------------------------------------
#ifndef __oe_test_Table_H__
#define __oe_test_Table_H__

#include "openeaagles/graphics/Field.h"

namespace oe {
   namespace basic { class Number; class PairStream; }

namespace test {

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

   virtual const basic::PairStream* getColumns() const;
   virtual unsigned int getNumberOfRows() const;

   // Slot functions
   virtual bool setSlotRows(basic::Number* const);
   virtual bool setSlotSpacing(basic::Number* const);
   virtual bool setSlotColumns(basic::PairStream* const);

   int line() const override;
   int line(const int ll) override;
   int column() const override;
   int column(const int cc) override;

   void reset() override;

private:
   void initData();
   void build();        // Builds the table into our components
   void position();     // Positions the table

   unsigned int  rows;     // Number of rows in table
   unsigned int  spacing;  // Spacing between rows (default: 1)
   const basic::PairStream* columns;  // columns items
};

} // End of test namespace
} // End of oe namespace

#endif

