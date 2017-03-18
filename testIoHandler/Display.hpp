
#ifndef __Display_H__
#define __Display_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include <array>

namespace oe {
namespace base { class IoHandler; class Number; class String; }
}

//------------------------------------------------------------------------------
// Class Display
// Description: Display class for the I/O devices test program (see display.epp)
//
// Factory name: TestIoDisplay
// Slots --
//    ioHandler   <base::IoHandler>     Single I/O data handler
//    item        <base::Integer>       Item number [ 1 ... TBL_SIZE ];
//                                         -- clear current channel number and
//                                         -- type for this item.  Next 'ai' or
//                                         -- 'di' will define for this 'item'.
//    di          <base::Integer>       DI channel number for last 'item'
//    ai          <base::Integer>       AI channel number for last 'item'
//    label       <base::String>        (optional) Label
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
class Display : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, oe::glut::GlutDisplay)

public:
   static const unsigned int ROWS = 20;      /* see display.epp */
   static const unsigned int COLUMNS = 3;    /* see display.epp */
   static const unsigned int TBL_SIZE = (ROWS*COLUMNS);
   static const unsigned int LABEL_SIZE = 10;

public:
   Display();

   virtual void reset() override;
   virtual void updateData(const double dt = 0.0) override;
   virtual void updateTC(const double dt = 0.0) override;

protected:
   virtual bool setSlotIoHandler(oe::base::IoHandler* const msg);
   virtual bool setSlotItem(const oe::base::Number* const msg);
   virtual bool setSlotAiChannel(const oe::base::Number* const msg);
   virtual bool setSlotDiChannel(const oe::base::Number* const msg);
   virtual bool setSlotLabel(const oe::base::String* const msg);

   virtual bool onEscKey() override;

private:
   enum class Type { NONE, AI, DI };
   enum { R_BLANK = 1, R_AI, R_DI_0, R_DI_1 };

   void initData();
   void updateDisplay();

   oe::base::safe_ptr<oe::base::IoHandler> ioHandler;   // The I/O data handler

   // Item/Channel mapping
   unsigned short item {};
   std::array<Type, TBL_SIZE> types;
   std::array<unsigned short, TBL_SIZE> channels {};
   std::array<bool, TBL_SIZE> labelFlags {};
   char labels[TBL_SIZE][LABEL_SIZE+1] {};
   char labelBuffs[TBL_SIZE][LABEL_SIZE+1+1] {}; // Labels with a ':' and a null char

   // Table data
   std::array<char*, TBL_SIZE> table_Label {};
   std::array<int, TBL_SIZE> table_typeRo {};
   std::array<double, TBL_SIZE> table_ai {};
   std::array<SendData, TBL_SIZE> table_LabelSD;
   std::array<SendData, TBL_SIZE> table_typeRoSD;
   std::array<SendData, TBL_SIZE> table_aiSD;
};

#endif
