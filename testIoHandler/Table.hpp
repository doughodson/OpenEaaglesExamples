
#ifndef __Table_H__
#define __Table_H__

#include "openeaagles/graphics/Field.hpp"

namespace oe {
namespace base { class Number; class PairStream; }
}

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
class Table : public oe::graphics::Field
{
   DECLARE_SUBCLASS(Table, oe::graphics::Field)

public:
   Table();

   virtual const oe::base::PairStream* getColumns() const;
   virtual unsigned int getNumberOfRows() const;

   // Slot functions
   virtual bool setSlotRows(oe::base::Number* const);
   virtual bool setSlotSpacing(oe::base::Number* const);
   virtual bool setSlotColumns(oe::base::PairStream* const);

   virtual int line() const override;
   virtual int line(const int ll) override;
   virtual int column() const override;
   virtual int column(const int cc) override;

   virtual void reset() override;

private:
   static const unsigned int DEFAULT_ROW     = 1;
   static const unsigned int DEFAULT_SPACING = 1;

   void build();        // Builds the table into our components
   void position();     // Positions the table

   unsigned int rows {DEFAULT_ROW};         // Number of rows in table
   unsigned int spacing {DEFAULT_SPACING};  // Spacing between rows (default: 1)
   const oe::base::PairStream* columns {};  // columns items
};

#endif
