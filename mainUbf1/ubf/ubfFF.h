//------------------------------------------------------------------------------
// Form function for the 'ubf' behaviors for mainUbf1 example
//
//    The form functions are class factories that will create an object
//    by its 'form' name and will return a pre-ref() pointer to the new
//    object or zero if the form name wasn't found.
//
//------------------------------------------------------------------------------

#ifndef __Eaagles_MainUbf1_Ubf_FormFunc_H__
#define __Eaagles_MainUbf1_Ubf_FormFunc_H__

namespace Eaagles {

   namespace Basic { class Object; }

   namespace MainUbf1 {
      extern Basic::Object* ubfFormFunc(const char* formname);
   }
}

#endif

