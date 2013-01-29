#include "Table.h"

#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"

#include <cstdio>

// disable all deprecation warnings for now, until we fix
// they are quite annoying to see over and over again...
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace TestIo {

static const unsigned int DEFAULT_ROW     = 1;
static const unsigned int DEFAULT_SPACING = 1;

//==============================================================================
// class TableRow -- One row of in the table (used by Table only)
//          (The implementation is at the bottom of the file after the Table class)
//==============================================================================
class TableRow : public BasicGL::Field {
   DECLARE_SUBCLASS(TableRow,BasicGL::Field)
public:
   TableRow();
   
   void put(Basic::Pair* const item);
   
   // BasicGL::Field class interface
   virtual int line() const;
   virtual int line(const int ll);
   virtual int column() const;
   virtual int column(const int cc);
   
private:
   void position();
};

//==============================================================================
// Table class --
//==============================================================================
IMPLEMENT_SUBCLASS(Table,"Table")

// slot table
BEGIN_SLOTTABLE(Table)
   "rows",          //   1) Number of rows
   "spacing",       //   2) Spacing between rows
   "columns",       //   3) Column descriptions: list of items in each row
END_SLOTTABLE(Table)

// slot map
BEGIN_SLOT_MAP(Table)
   ON_SLOT( 1, setSlotRows, Basic::Number)
   ON_SLOT( 2, setSlotSpacing, Basic::Number)
   ON_SLOT( 3, setSlotColumns, Basic::PairStream)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Table::Table()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

// initData()
void Table::initData()
{
   rows = DEFAULT_ROW;
   spacing = DEFAULT_SPACING;
   columns = 0;
}

// copyData() -- copy this object's data
void Table::copyData(const Table& org, const bool cc)
{
   BaseClass::copyData(org);
   
   if (cc) initData();

   rows = org.rows;
   spacing = org.spacing;

   if (org.columns) {
      Basic::PairStream* p = org.columns->clone();
      setSlotColumns(p);
   }
   else {
      setSlotColumns(0);
   }

   build();

   line(org.line());
   column(org.column());
}

//deleteData() -- delete this object's data
void Table::deleteData()
{
   setSlotColumns(0);
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

const Basic::PairStream* Table::getColumns() const
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
   Basic::PairStream* subcomponents = getComponents();
   if (subcomponents != 0) {
   
      int ln = line();
      int cp = column();
      
      // Position our subcomponents, which are all TableRow objects (see build())
      Basic::List::Item* item = subcomponents->getFirstItem();
      while (item != 0) {
         Basic::Pair* pair = (Basic::Pair*)(item->getValue());
         TableRow* row = (TableRow*) pair->object();
         
         row->line(ln);
         row->column(cp);
         ln += spacing;
         
         item = item->getNext();
      }
      subcomponents->unref();
      subcomponents = 0;
   }
}

//------------------------------------------------------------------------------
// build() -- build the table in our components list
//------------------------------------------------------------------------------
void Table::build()
{
   Basic::PairStream* newList = 0;
   
   if (rows > 0 && columns != 0) {

      newList = new Basic::PairStream();
      
      // For each row: create a TableRow containing all the items in 'columns'
      for (unsigned int i = 1; i <= rows; i++) {
      
         // new row
         TableRow* row = new TableRow(); 
         row->container(this);
         
         const Basic::List::Item* item = columns->getFirstItem();
         while (item != 0) {
            const Basic::Pair* pair = (const Basic::Pair*)(item->getValue());
            const Basic::Object* obj = pair->object();
            if (obj->isClassType(typeid(BasicGL::Graphic))) {
               Basic::Pair* pp = pair->clone();
               BasicGL::Graphic* gobj = (BasicGL::Graphic*) pp->object();
               gobj->container(row);
               row->put(pp);
               pp->unref();
            }

            item = item->getNext();
         }

         // put the row on our components list with a slotname equal to its row number
         {
            char cbuf[8];
            sprintf(cbuf,"%d",i);
            Basic::Pair* pp = new Basic::Pair(cbuf,row);
            newList->put(pp);
            pp->unref();
         }
         
         row->unref();
      }

      // Position our subcomponents
      position();
   }

   // These are new our subcomponents ...
   processComponents(newList,typeid(Basic::Component));
   if (newList != 0) newList->unref();
}


//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool Table::setSlotRows(Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int v = msg->getInt();
      if (v >= 0) {
         rows = (unsigned int) v;
         ok = true;
      }
   }
   return ok;
}

bool Table::setSlotSpacing(Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int v = msg->getInt();
      if (v >= 0) {
         spacing = (unsigned int) v;
         ok = true;
      }
   }
   return ok;
}

bool Table::setSlotColumns(Basic::PairStream* const msg)
{
   if (columns != 0) { columns->unref(); columns = 0; }
   if (msg != 0) {
      // Make a copy of the list and Make sure we have only Field objexts
      Basic::PairStream* newColumns = new Basic::PairStream();
      Basic::List::Item* item = msg->getFirstItem();
      while (item != 0) {
          Basic::Pair* pair = (Basic::Pair*) item->getValue();
          BasicGL::Field* g = dynamic_cast<BasicGL::Field*>(pair->object());
          if (g != 0) {
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

//------------------------------------------------------------------------------
// getSlotByIndex() 
//------------------------------------------------------------------------------
Basic::Object* Table::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& Table::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
    int j = 0;
    if ( !slotsOnly ) {
        //indent(sout,i);
        sout << "( " << getFormName() << std::endl;
        j = 4;
    }
    
   indent(sout,i+j);
   sout << "rows: " << rows << std::endl;

   indent(sout,i+j);
   sout << "spacing: " << spacing << std::endl;

   indent(sout,i+j);
   sout << "columns: {" << std::endl;
    if (columns != 0) {
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

void  TableRow::put(Basic::Pair* pp)
{
   Basic::PairStream* subcomponents = getComponents();
   BaseClass::processComponents(subcomponents, typeid(BasicGL::Field), pp);
   if (subcomponents != 0) subcomponents->unref();
}

void TableRow::position()
{
   // position the fields in this table item
   Basic::PairStream* subcomponents = getComponents();
   if (subcomponents != 0) {
   
      int ln = line();
      int cp = column();
      
      Basic::List::Item* item = subcomponents->getFirstItem();
      while (item != 0) {
         Basic::Pair* pair = (Basic::Pair*)(item->getValue());
         BasicGL::Field* ti = (BasicGL::Field*) pair->object();
        
         ti->line(ln);
         ti->column(cp);
         cp += (int) ti->width();
         
         item = item->getNext();
      }
      subcomponents->unref();
      subcomponents = 0;
   }
}

} // End of TestIo namespace
} // End of Eaagles namespace
