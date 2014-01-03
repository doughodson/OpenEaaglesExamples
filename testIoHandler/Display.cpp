//------------------------------------------------------------------------------
// Class: Display
//------------------------------------------------------------------------------
#include "Display.h"

#include "openeaagles/basic/IoData.h"
#include "openeaagles/basic/IoHandler.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/String.h"

#include <cstdio>

// disable all deprecation warnings for now, until we fix
// they are quite annoying to see over and over again...
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Test {

IMPLEMENT_SUBCLASS(Display,"TestIoDisplay")

//------------------------------------------------------------------------------
// Slot table
//------------------------------------------------------------------------------
BEGIN_SLOTTABLE(Display)
   "ioHandler",   // 1: I/O data handler
   "item",        // 2: Item number [ 1 ... TBL_SIZE ]
   "di",          // 3: DI channel number for last 'item'
   "ai",          // 4: AI channel number for last 'item'
   "label"        // 5: (optional) Label
END_SLOTTABLE(Display)

//------------------------------------------------------------------------------
// Slot table                                                               SLS
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(Display)
    ON_SLOT(1, setSlotIoHandler, Basic::IoHandler)
    ON_SLOT(2, setSlotItem,      Basic::Number)
    ON_SLOT(3, setSlotDiChannel, Basic::Number)
    ON_SLOT(4, setSlotAiChannel, Basic::Number)
    ON_SLOT(5, setSlotLabel,     Basic::String)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Display::Display()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

//------------------------------------------------------------------------------
// initData() -- Init member data (from constructors and copyData())
//------------------------------------------------------------------------------
void Display::initData()
{
   ioHandler = 0;

   // Item/Channel mapping
   for (unsigned int i = 0; i < TBL_SIZE; i++) {
      types[i] = NONE;
      channels[i] = 0;
      labelFlags[i] = false;
      labels[i][0] = '\0';
      labelBuffs[i][0] = '\0';
   }
   item = 0;

   // Display buffers
   for (unsigned int i = 0; i < TBL_SIZE; i++) {
      table_typeRo[i] = R_BLANK;
      table_Label[i] = labelBuffs[i];
      table_ai[i] = 0;
   }

}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Display::copyData(const Display& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();

   if (org.ioHandler != 0) {
      Basic::IoHandler* copy = org.ioHandler->clone();
      setSlotIoHandler(copy);
      copy->unref();
   }
   else setSlotIoHandler(0);

   // Item/Channel mapping
   for (unsigned int i = 0; i < TBL_SIZE; i++) {
      types[i] = org.types[i];
      channels[i] = org.channels[i];
      labelFlags[i] = org.labelFlags[i];
      lcStrcpy(labels[i], sizeof(labels[i]), org.labels[i]);
      lcStrcpy(labelBuffs[i], sizeof(labelBuffs[i]), org.labelBuffs[i]);
   }
   item = org.item;

   // Display buffers
   for (unsigned int i = 0; i < TBL_SIZE; i++) {
      table_typeRo[i] = org.table_typeRo[i];
      table_Label[i] = labelBuffs[i];
      table_ai[i] = org.table_ai[i];
   }
}

//------------------------------------------------------------------------------
// deleteData() -- delete this object's data
//------------------------------------------------------------------------------
void Display::deleteData()
{
   setSlotIoHandler(0);
}

//-----------------------------------------------------------------------------
// onEscKey() - from event handler
//-----------------------------------------------------------------------------
bool Display::onEscKey()
{
   std::cout<<"Display::onEscKey() -- Exit by the ESC key!"<<std::endl;
   exit(0);
}

//------------------------------------------------------------------------------
// reset() -- Reset parameters
//------------------------------------------------------------------------------
void Display::reset()
{
   BaseClass::reset();
   setNormColor( getColor("NormalText") );
   setHighlightColor( getColor("HighlightText") );
    
   // Reset the I/O Handler
   if (ioHandler != 0) {
      ioHandler->event(RESET_EVENT);
   }
}

//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void Display::updateTC(const LCreal dt)
{ 
   // I/O Handler
   if (ioHandler != 0) {
      ioHandler->inputDevices(dt);
      //ioHandler->updateTC(dt);
      ioHandler->outputDevices(dt);
   }

   BaseClass::updateTC(dt);
}

//------------------------------------------------------------------------------
// updateData() --
//------------------------------------------------------------------------------
void Display::updateData(const LCreal dt)
{
   // I/O Handler
   if (ioHandler != 0) {
      //ioHandler->updateData(dt);
   }

   // Update the display buffers
   updateDisplay();

   // Left column (column1)
   {
      unsigned int idx = 0;
      send( "column1.%d.label",   UPDATE_VALUE,   &table_Label[idx],     &table_LabelSD[idx],     ROWS );
      send( "column1.%d.typeRo",  SELECT,         &table_typeRo[idx],    &table_typeRoSD[idx],    ROWS );
      send( "column1.%d.typeRo.ai", UPDATE_VALUE, &table_ai[idx],       &table_aiSD[idx],        ROWS );
   }

   // Center column (column2)
   {
      unsigned int idx = ROWS;
      send( "column2.%d.label",   UPDATE_VALUE,   &table_Label[idx],     &table_LabelSD[idx],     ROWS );
      send( "column2.%d.typeRo",  SELECT,         &table_typeRo[idx],    &table_typeRoSD[idx],    ROWS );
      send( "column2.%d.typeRo.ai", UPDATE_VALUE, &table_ai[idx],       &table_aiSD[idx],        ROWS );
   }

   // Right column (column3)
   {
      unsigned int idx = ROWS*2;
      send( "column3.%d.label",   UPDATE_VALUE,   &table_Label[idx],     &table_LabelSD[idx],     ROWS );
      send( "column3.%d.typeRo",  SELECT,         &table_typeRo[idx],    &table_typeRoSD[idx],    ROWS );
      send( "column3.%d.typeRo.ai", UPDATE_VALUE, &table_ai[idx],       &table_aiSD[idx],        ROWS );
   }

   BaseClass::updateData(dt);
}

//------------------------------------------------------------------------------
// Function collect the data to be displayed
//------------------------------------------------------------------------------
void Display::updateDisplay()
{
   Basic::IoData* ioData = 0;
   if (ioHandler != 0) ioData = ioHandler->getInputData();

   // Item/channel mapping
   for (unsigned int i = 0; i < TBL_SIZE; i++) {

      bool ok = false;

      if (types[i] != NONE && ioData != 0) {

         // Set the data
         if (types[i] == AI) {
            LCreal v = 0;
            ok = ioData->getAnalogInput(channels[i], &v);
            if (ok) {
               table_ai[i] = v;
               table_typeRo[i] = R_AI;
            }
         }
         else if (types[i] == DI) {
            bool flg = false;
            ok = ioData->getDiscreteInput(channels[i], &flg);
            if (ok) {
               if (flg) table_typeRo[i] = R_DI_1;
               else table_typeRo[i] = R_DI_0;
            }
         }

         // Create the label
         {
            // if not provided; make the default label
            if (!labelFlags[i]) {
               char cbuff[32];
               if (types[i] == AI) sprintf(cbuff, "AI(%03d)", channels[i]);
               else                sprintf(cbuff, "DI(%03d)", channels[i]);
               lcStrcpy(labels[i], sizeof(labels[i]), cbuff);
            }

            // copy the label with a ':'
            lcStrcpy(labelBuffs[i], sizeof(labelBuffs[i]), labels[i]);
            lcStrcat(labelBuffs[i], sizeof(labelBuffs[i]), ":");
         }

      }

      if (!ok) {
         table_ai[i] = 0;
      }

   }
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

bool Display::setSlotIoHandler(Basic::IoHandler* const msg)
{
   if (ioHandler != 0) {
      ioHandler->container(0);
   }
   ioHandler = msg;
   if (ioHandler != 0) {
      ioHandler->container(this);
   }
   return true;
}

bool Display::setSlotItem(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int v = msg->getInt();
      if (v >= 1 && v <= TBL_SIZE) {
         item = (unsigned short) v;
         types[item-1] = NONE;
         channels[item-1] = 0;
         ok = true;
      }
      else {
         std::cerr << "Display::setSlotItem(): Invalid 'item' number, range: [ 1 ... " << TBL_SIZE << " ]" << std::endl;
      }
   }
   return ok;
}

bool Display::setSlotAiChannel(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0 && item >= 1 && item <= TBL_SIZE) {
      int v = msg->getInt();
      if (v >= 0 && v <= 0xFFFF) {
         channels[item-1] = (unsigned short) v;
         types[item-1] = AI;
         ok = true;
      }
   }
   else {
      std::cerr << "Display::setSlotAiChannel(): Invalid item number; set using slot 'item'" << std::endl;
   }
   return ok;
}

bool Display::setSlotDiChannel(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0 && item >= 1 && item <= TBL_SIZE) {
      int v = msg->getInt();
      if (v >= 0 && v <= 0xFFFF) {
         channels[item-1] = (unsigned short) v;
         types[item-1] = DI;
         ok = true;
      }
   }
   else {
      std::cerr << "Display::setSlotAiChannel(): Invalid item number; set using slot 'item'" << std::endl;
   }
   return ok;
}

bool Display::setSlotLabel(const Basic::String* const msg)
{
   bool ok = false;
   if (item >= 1 && item <= TBL_SIZE) {
      if (msg != 0) {
         lcStrcpy(labels[item-1], sizeof(labels[item-1]), *msg);
         labelFlags[item-1] = true;
      }
      else {
         labelFlags[item-1] = false;
      }
      ok = true;
   }
   else {
      std::cerr << "Display::setSlotAiChannel(): Invalid item number; set using slot 'item'" << std::endl;
   }
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* Display::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}


//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& Display::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      indent(sout,i);
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   // I/O handlers
   if (ioHandler != 0) {
      indent(sout,i+j);
      sout << "ioHandler: " << std::endl;
      ioHandler->serialize(sout,i+j+4);
   }

   // Item/channel mapping
   for (unsigned int idx = 0; idx < TBL_SIZE; idx++) {
      if (types[idx] != NONE) {
         indent(sout,i+j);
         sout << "item: " << (idx+1) << "   ";
         if (types[idx] == AI) {
            sout << "ai: ";
         }
         else if (types[idx] == DI) {
            sout << "di: ";
         }
         sout << channels[idx] << std::endl;
      }
   }

   if ( !slotsOnly ) {
      indent(sout,i);
      sout << ")" << std::endl;
   }

   return sout;
}

} // End of Test namespace
} // End of Eaagles namespace
