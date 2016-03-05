
#include "TdAzPtr.h"
#include "openeaagles/base/Number.h"

namespace oe {
namespace example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TdAzPtr,"TdAzPtr")
EMPTY_SERIALIZER(TdAzPtr)


//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TdAzPtr::TdAzPtr()
{
    STANDARD_CONSTRUCTOR()
    azimuth = 0.0;
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void TdAzPtr::copyData(const TdAzPtr& org, const bool)
{
    BaseClass::copyData(org);
    azimuth = 0.0;
}

EMPTY_DELETEDATA(TdAzPtr)


//------------------------------------------------------------------------------
// event() -- default event handler
//------------------------------------------------------------------------------
bool TdAzPtr::event(const int event, base::Object* const obj)
{
    bool used = false;

    if (event == UPDATE_VALUE)
    {
        const base::Number* num = dynamic_cast<const base::Number*>(obj);
        if (num != nullptr) {
            azimuth = num->getReal();
            used = true;
        }
    }
    
    if (!used)
    {
        // Otherwise, pass key events up to our base class
        used = BaseClass::event(event,obj);
    }

    return used;
}


//------------------------------------------------------------------------------
// draw() -- draw the pointer
//------------------------------------------------------------------------------
void TdAzPtr::draw()
{
   if (isVisible())  {
       lcSaveMatrix();
       lcTranslate( azimuth, 0.0 );
       BaseClass::draw();
       lcRestoreMatrix();
   }
}

} // End example namespace
} // End oe namespace
