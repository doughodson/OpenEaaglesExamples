
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Color.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/String.h"

// class factories
#include "openeaagles/basic/Factory.h"

#include "MyObj.h"

namespace Eaagles {
namespace Tutorial {

static class MyObj* myObj = nullptr;

// our class factory
static Basic::Object* factory(const char* const name)
{
   Basic::Object* obj = nullptr;

   // look in application's classes
   if ( std::strcmp(name, MyObj::getFactoryName()) == 0 ) {
      obj = new MyObj;
   }
   // look in base classes
   if (obj == nullptr) obj = Basic::Factory::createObj(name);
   return obj;
}

// MyObj builder
static MyObj* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   MyObj* myObj = dynamic_cast<MyObj*>(obj);
   if (myObj == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return myObj;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "file0.edl";

   // build my object
   myObj = builder(configFilename);

   // print out some color information
   const Basic::PairStream* colorTable = myObj->getColorTable();
   if (colorTable != 0) {
//    Pair* p = colorTable->findByName("green");
      const Basic::Identifier* id = myObj->getTextColor();
      if (id != 0) {
         const Basic::Pair* p = colorTable->findByName(id->getString());
         if (p != 0) {
            std::cout << "Text color: " << id->getString();
            const Basic::Color* color = dynamic_cast<const Basic::Color*>(p->object());
            if (color != 0) {
               std::cout << " Red: "   << color->red();
               std::cout << " Green: " << color->green();
               std::cout << " Blue: "  << color->blue();
            }
            std::cout << std::endl;
         } else {
            std::cout << "Text color not found\n" << std::endl;
         }
      }
   }

   // print out vector information
   const Basic::List* vector = myObj->getVector();
   if (vector != 0) {
      int numValues = vector->entries();
      int* values = new int[numValues];
      int n = vector->getNumberList(values,numValues);
      std::cout << "Vector: ";
      std::cout << "# Numeric Entries: " << n << " Values: ";
      for (int i=0; i < n; i++)
         std::cout << values[i] << " ";
      std::cout << std::endl;
      delete[] values;
   }

   // print out visible and message info
   std::cout << "Visible: " << myObj->getVisible() << "\n";
   const Basic::String* message = myObj->getMessage();
   std::cout << "Message: " << message->getString() << "\n";

   myObj->unref();

   return 0;
}

} // namespace Tutorial
} // namespace Eaagles

//
int main(int argc, char* argv[])
{
   Eaagles::Tutorial::main(argc, argv);
}
