//------------------------------------------------------------------------------
// Class: Display
//------------------------------------------------------------------------------
#ifndef __oe_test_Display_H__
#define __oe_test_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
   namespace basic { class IoHandler; class Number; class String; }

namespace test {

//------------------------------------------------------------------------------
// Class Display
// Description: Display class for the I/O devices test program (see display.epp)
//
// Factory name: TestIoDisplay
// Slots --
//    ioHandler   <basic::IoHandler>     Single I/O data handler
//    item        <basic::Integer>       Item number [ 1 ... TBL_SIZE ];
//                                         -- clear current channel number and
//                                         -- type for this item.  Next 'ai' or
//                                         -- 'di' will define for this 'item'.
//    di          <basic::Integer>       DI channel number for last 'item'
//    ai          <basic::Integer>       AI channel number for last 'item'
//    label       <basic::String>        (optional) Label
//
// Example:
//   ( TestIoDisplay
//       item:  1   ai: 5     // Item #1 is AI #5
//       item:  2   ai: 5     // Item #2 is AI #6
//       item:  3             // Item #3 is blank
//       item:  4   di: 10    // Item #4 is DI #10
//       item:  5   di: 11    // Item #4 is DI #11
//   )
//------------------------------------------------------------------------------
class Display : public glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, glut::GlutDisplay)

public:
   static const unsigned int ROWS = 20;      /* see display.epp */
   static const unsigned int COLUMNS = 3;    /* see display.epp */
   static const unsigned int TBL_SIZE = (ROWS*COLUMNS);
   static const unsigned int LABEL_SIZE = 10;

public:
   Display();

   void reset() override;
   void updateData(const LCreal dt = 0.0) override;
   void updateTC(const LCreal dt = 0.0) override;

protected:
   virtual bool setSlotIoHandler(basic::IoHandler* const msg);
   virtual bool setSlotItem(const basic::Number* const msg);
   virtual bool setSlotAiChannel(const basic::Number* const msg);
   virtual bool setSlotDiChannel(const basic::Number* const msg);
   virtual bool setSlotLabel(const basic::String* const msg);

   bool onEscKey() override;

private:
   enum Type { NONE, AI, DI };
   enum { R_BLANK = 1, R_AI, R_DI_0, R_DI_1 };

   void initData();
   void updateDisplay();

   basic::safe_ptr<basic::IoHandler> ioHandler;   // The I/O data handler

   // Item/Channel mapping
   unsigned short item;
   Type types[TBL_SIZE];
   unsigned short channels[TBL_SIZE];
   bool labelFlags[TBL_SIZE];
   char labels[TBL_SIZE][LABEL_SIZE+1];
   char labelBuffs[TBL_SIZE][LABEL_SIZE+1+1]; // Labels with a ':' and a null char

   // Table data
   char* table_Label[TBL_SIZE];
   int   table_typeRo[TBL_SIZE];
   LCreal table_ai[TBL_SIZE];
   SendData table_LabelSD[TBL_SIZE];
   SendData table_typeRoSD[TBL_SIZE];
   SendData table_aiSD[TBL_SIZE];
};

} // End of test namespace
} // End of oe namespace

#endif
