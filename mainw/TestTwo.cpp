
#include "TestTwo.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(TestTwo,"TestTwo")

//------------------------------------------------------------------------------
// slot table for this class type
//------------------------------------------------------------------------------
BEGIN_SLOTTABLE(TestTwo)
    "v1",       // V1 initial value
    "v1Rate",   // V1 rate
    "v1Max",    // V1 max value
    "v1Min",    // V1 min value
    "v2",       // V2 initial value
    "v2Rate",   // V2 rate
    "v2Max",    // V2 max value
    "v2Min",    // V2 min value
END_SLOTTABLE(TestTwo)

//------------------------------------------------------------------------------
// slot mapping for this class type - replaces setSlotByIndex()
//------------------------------------------------------------------------------
BEGIN_SLOT_MAP(TestTwo)
    ON_SLOT(1, setV1, Basic::Number)
    ON_SLOT(2, setV1Rate, Basic::Number)
    ON_SLOT(3, setV1Max, Basic::Number)
    ON_SLOT(4, setV1Min, Basic::Number)
    ON_SLOT(5, setV2, Basic::Number)
    ON_SLOT(6, setV2Rate, Basic::Number)
    ON_SLOT(7, setV2Max, Basic::Number)
    ON_SLOT(8, setV2Min, Basic::Number)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// event handler macro - default - replaces event()
//------------------------------------------------------------------------------
BEGIN_EVENT_HANDLER(TestTwo)
END_EVENT_HANDLER()


//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestTwo::TestTwo()
{
    STANDARD_CONSTRUCTOR()
    iv1     = 0.0f;
    iv1Rate = 0.1f;
    v1Max  = 1.0f;
    v1Min  = 0.0f;
    iv2     = 0.0f;
    iv2Rate = 0.1f;
    v2Max  = 1.0f;
    v2Min  = 0.0f;
    reset();
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void TestTwo::copyData(const TestTwo& org, const bool)
{
    BaseClass::copyData(org);

    iv1 = org.iv1;
    iv1Rate = org.iv1Rate;
    v1Max = org.v1Max;
    v1Min = org.v1Min;

    iv2 = org.iv2;
    iv2Rate = org.iv2Rate;
    v2Max = org.v2Max;
    v2Min = org.v2Min;

    reset();
}

EMPTY_DELETEDATA(TestTwo)

//------------------------------------------------------------------------------
// resetData() -- reset member data to known state
//------------------------------------------------------------------------------
void TestTwo::reset()
{
    v1     = iv1;
    v1Rate = iv1Rate;
    v1SD.empty();
    v1TitleSD.empty();

    v2     = iv2;
    v2Rate = iv2Rate;
    v2SD.empty();
    v2TitleSD.empty();
}


//------------------------------------------------------------------------------
// updateTC() -- update time critical stuff here
//------------------------------------------------------------------------------
void TestTwo::updateTC(const LCreal dt)
{
    // Update base classes stuff
    BaseClass::updateTC(dt);

    // Update V1
    v1 += v1Rate*dt;
    if (v1 > v1Max) {
        v1 = v1Max - (v1 - v1Max);
        v1Rate = -v1Rate;
    }
    else if (v1 < v1Min) {
        v1 = v1Min - (v1 - v1Min);
        v1Rate = -v1Rate;
    }

    // Update V2
    v2 += v2Rate*dt;
    if (v2 > v2Max) {
        v2 = v2Max - (v2 - v2Max);
        v2Rate = -v2Rate;
    }
    else if (v2 < v2Min) {
        v2 = v2Min - (v2 - v2Min);
        v2Rate = -v2Rate;
    }
}


//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestTwo::updateData(const LCreal dt)
{
    // Update base classes stuff
    BaseClass::updateData(dt);

    int i = 1;
    if (v2 < 0) i++;
    if (v2Rate < 0) i += 2;

    send( "v1", UPDATE_VALUE, v1, v1SD );
    send( "v1Title", SELECT, (v1Rate < 0), v1TitleSD);
    send( "v2", UPDATE_VALUE, v2, v2SD );
    send( "v2Title", SELECT, i, v2TitleSD);
}



//------------------------------------------------------------------------------
// getSlotByIndex() for Rgb
//------------------------------------------------------------------------------
Basic::Object* TestTwo::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}



//------------------------------------------------------------------------------
// serialize() -- print functions
//------------------------------------------------------------------------------
std::ostream& TestTwo::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
    int j = 0;
    if ( !slotsOnly ) {
        sout << "( " << getFactoryName() << std::endl;
        j = 4;
    }

    indent(sout,i+j);
    sout << "v1: " << iv1 << std::endl;

    indent(sout,i+j);
    sout << "v1Rate: " << iv1Rate << std::endl;

    indent(sout,i+j);
    sout << "v1Max: " << v1Max << std::endl;

    indent(sout,i+j);
    sout << "v1Min: " << v1Min << std::endl;

    indent(sout,i+j);
    sout << "v2: " << iv2 << std::endl;

    indent(sout,i+j);
    sout << "v2Rate: " << iv2Rate << std::endl;

    indent(sout,i+j);
    sout << "v2Max: " << v2Max << std::endl;

    indent(sout,i+j);
    sout << "v2Min: " << v2Min << std::endl;

    BaseClass::serialize(sout,i+j,true);

    if ( !slotsOnly ) {
        indent(sout,i);
        sout << ")" << std::endl;
    }
    return sout;
}

// Macro functions for Setting up the slot maps//
//------------------------------------------------------------------------------
// setV1() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV1(const Basic::Number* const sv1obj)
{
    if (sv1obj != 0) iv1 = sv1obj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV1Rate() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV1Rate(const Basic::Number* const sv1robj)
{
    if (sv1robj != 0) iv1Rate = sv1robj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV1Max() --
//------------------------------------------------------------------------------
bool TestTwo::setV1Max(const Basic::Number* const sv1mobj)
{
    if (sv1mobj != 0) v1Max = sv1mobj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV1Min() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV1Min(const Basic::Number* const sv1miobj)
{
    if (sv1miobj != 0) v1Min = sv1miobj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV2() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV2(const Basic::Number* const sv2obj)
{
    if (sv2obj != 0) iv2 = sv2obj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV2Rate() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV2Rate(const Basic::Number* const sv2robj)
{
    if (sv2robj != 0) iv2Rate = sv2robj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV2Max() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV2Max(const Basic::Number* const sv2mobj)
{
    if (sv2mobj != 0) v2Max = sv2mobj->getReal();
    return true;
}

//------------------------------------------------------------------------------
// setV2Min() -- 
//------------------------------------------------------------------------------
bool TestTwo::setV2Min(const Basic::Number* const sv2miobj)
{
    if (sv2miobj != 0) v2Min = sv2miobj->getReal();
    return true;
}

} // End Example namespace
} // End Eaagles namespace
