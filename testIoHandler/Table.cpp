
#include "Table.hpp"

#include "openeaagles/base/Number.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"

#include <cstdio>

using namespace oe;

//==============================================================================
// class TableRow -- One row of in the table (used by Table only)
//          (The implementation is at the bottom of the file after the Table class)
//==============================================================================
class TableRow : public graphics::Field
{
   DECLARE_SUBCLASS(TableRow,graphics::Field)

public:
   TableRow();

   void put(base::Pair* const item);

   // graphics::Field class interface
   virtual int line() const override;
   virtual int line(const int ll) override;
   virtual int column() const override;
   virtual int column(const int cc) override;

private:
   void position();
};

//==============================================================================
// Table class --
//==============================================================================
IMPLEMENT_SUBCLASS(Table, "Table")

BEGIN_SLOTTABLE(Table)
   "rows",          //   1) Number of rows
   "spacing",       //   2) Spacing between rows
   "columns",       //   3) Column descriptions: list of items in each row
END_SLOTTABLE(Table)

BEGIN_SLOT_MAP(Table)
   ON_SLOT( 1, setSlotRows, base::Number)
   ON_SLOT( 2, setSlotSpacing, base::Number)
   ON_SLOT( 3, setSlotColumns, base::PairStream)
END_SLOT_MAP()

Table::Table()
{
   STANDARD_CONSTRUCTOR()
}

void Table::copyData(const Table& org, const bool)
{
   BaseClass::copyData(org);

   rows = org.rows;
   spacing = org.spacing;

   if (org.columns) {
      base::PairStream* p = org.columns->clone();
      setSlotColumns(p);
   }
   else {
      setSlotColumns(nullptr);
   }

   build();

   line(org.line());
   column(org.column());
}

//deleteData() -- delete this object's data
void Table::deleteData()
{
   setSlotColumns(nullptr);
}

//------------------------------------------------------------------------------
// reset() -- Reset parameters
//------------------------------------------------------------------------------
void Table::reset()
{
    BaseClass::reset();

    // force a reposition
    line( line() );
    column( column() );
}

//------------------------------------------------------------------------------
// get functions
//------------------------------------------------------------------------------
int Table::line() const
{
   return BaseClass::line();
}

int Table::column() const
{
   return BaseClass::column();
}

const base::PairStream* Table::getColumns() const
{
   return columns;
}

unsigned int Table::getNumberOfRows() const
{
   return rows;
}

//------------------------------------------------------------------------------
// set functions
//------------------------------------------------------------------------------
int Table::line(const int ll)
{
   BaseClass::line(ll);
   position();
   return BaseClass::line();
}

int Table::column(const int cc)
{
   BaseClass::column(cc);
   position();
   return BaseClass::column();
}

//------------------------------------------------------------------------------
// position() -- position the rows in this table
//------------------------------------------------------------------------------
void Table::position()
{
   base::PairStream* subcomponents = getComponents();
   if (subcomponents != nullptr) {

      int ln = line();
      int cp = column();

      // Position our subcomponents, which are all TableRow objects (see build())
      base::List::Item* item = subcomponents->getFirstItem();
      while (item != nullptr) {
         const auto pair = static_cast<base::Pair*>(item->getValue());
         const auto row = static_cast<TableRow*>(pair->object());

         row->line(ln);
         row->column(cp);
         ln += spacing;

         item = item->getNext();
      }
      subcomponents->unref();
      subcomponents = nullptr;
   }
}

//------------------------------------------------------------------------------
// build() -- build the table in our components list
//------------------------------------------------------------------------------
void Table::build()
{
   base::PairStream* newList = nullptr;

   if (rows > 0 && columns != nullptr) {

      newList = new base::PairStream();

      // For each row: create a TableRow containing all the items in 'columns'
      for (unsigned int i = 1; i <= rows; i++) {

         // new row
         const auto row = new TableRow();
         row->container(this);

         const base::List::Item* item = columns->getFirstItem();
         while (item != nullptr) {
            const auto pair = static_cast<const base::Pair*>(item->getValue());
            const base::Object* obj = pair->object();
            if (obj->isClassType(typeid(graphics::Graphic))) {
               base::Pair* pp = pair->clone();
               const auto gobj = static_cast<graphics::Graphic*>(pp->object());
               gobj->container(row);
               row->put(pp);
               pp->unref();
            }

            item = item->getNext();
         }

         // put the row on our components list with a slotname equal to its row number
         {
            char cbuf[8];
            std::sprintf(cbuf, "%d", i);
            const auto pp = new base::Pair(cbuf,row);
            newList->put(pp);
            pp->unref();
         }

         row->unref();
      }

      // Position our subcomponents
      position();
   }

   // These are new our subcomponents ...
   processComponents(newList,typeid(base::Component));
   if (newList != nullptr) newList->unref();
}


//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool Table::setSlotRows(base::Number* const msg)
{
   bool ok = false;
   if (msg != nullptr) {
      int v = msg->getInt();
      if (v >= 0) {
         rows = static_cast<unsigned int>(v);
         ok = true;
      }
   }
   return ok;
}

bool Table::setSlotSpacing(base::Number* const msg)
{
   bool ok = false;
   if (msg != nullptr) {
      int v = msg->getInt();
      if (v >= 0) {
         spacing = static_cast<unsigned int>(v);
         ok = true;
      }
   }
   return ok;
}

bool Table::setSlotColumns(base::PairStream* const msg)
{
   if (columns != nullptr) { columns->unref(); columns = nullptr; }
   if (msg != nullptr) {
      // Make a copy of the list and Make sure we have only Field objexts
      const auto newColumns = new base::PairStream();
      base::List::Item* item = msg->getFirstItem();
      while (item != nullptr) {
          const auto pair = static_cast<base::Pair*>(item->getValue());
          const auto g = dynamic_cast<graphics::Field*>(pair->object());
          if (g != nullptr) {
              // We have a Field object, so add it to the new columns list
              newColumns->put(pair);
          }
          item = item->getNext();
      }
      columns = newColumns;
   }
   build();
   return true;
}

std::ostream& Table::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
    int j = 0;
    if ( !slotsOnly ) {
        //indent(sout,i);
        sout << "( " << getFactoryName() << std::endl;
        j = 4;
    }

   indent(sout,i+j);
   sout << "rows: " << rows << std::endl;

   indent(sout,i+j);
   sout << "spacing: " << spacing << std::endl;

   indent(sout,i+j);
   sout << "columns: {" << std::endl;
    if (columns != nullptr) {
        columns->serialize(sout,i+j+4,slotsOnly);
    }
   indent(sout,i+j);
   sout << "}" << std::endl;

    BaseClass::serialize(sout,i+j,true);

    if ( !slotsOnly ) {
        indent(sout,i);
        sout << ")" << std::endl;
    }

    return sout;
}

//==============================================================================
// class TableRow -- One row of in the table (used by Table only)
//==============================================================================

IMPLEMENT_SUBCLASS(TableRow,"TableRow")
EMPTY_SLOTTABLE(TableRow)
EMPTY_SERIALIZER(TableRow)

TableRow::TableRow()
{
   STANDARD_CONSTRUCTOR()
}

void TableRow::copyData(const TableRow& org, const bool)
{
   BaseClass::copyData(org);
}

void TableRow::deleteData()
{
}

int TableRow::line() const
{
   return BaseClass::line();
}

int TableRow::line(const int ll)
{
   BaseClass::line(ll);
   position();
   return BaseClass::line();
}

int TableRow::column() const
{
   return BaseClass::column();
}

int TableRow::column(const int cc)
{
   BaseClass::column(cc);
   position();
   return BaseClass::column();
}

void  TableRow::put(base::Pair* pp)
{
   base::PairStream* subcomponents = getComponents();
   BaseClass::processComponents(subcomponents, typeid(graphics::Field), pp);
   if (subcomponents != nullptr) subcomponents->unref();
}

void TableRow::position()
{
   // position the fields in this table item
   base::PairStream* subcomponents = getComponents();
   if (subcomponents != nullptr) {

      int ln = line();
      int cp = column();

      base::List::Item* item = subcomponents->getFirstItem();
      while (item != nullptr) {
         const auto pair = static_cast<base::Pair*>(item->getValue());
         const auto ti = static_cast<graphics::Field*>(pair->object());

         ti->line(ln);
         ti->column(cp);
         cp += static_cast<int>(ti->width());

         item = item->getNext();
      }
      subcomponents->unref();
      subcomponents = nullptr;
   }
}
