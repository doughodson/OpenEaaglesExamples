
#include <iostream>
#include <string>
#include <cstdlib>

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/base/Color.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/String.hpp"

// factories
#include "openeaagles/base/factory.hpp"

#include "MyObj.hpp"

// our class factory
oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   // look in application's classes
   if ( name == MyObj::getFactoryName() ) {
      obj = new MyObj;
   }
   // look in base classes
   if (obj == nullptr) obj = oe::base::factory(name);
   return obj;
}

// MyObj builder
MyObj* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   const auto pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto myObj = dynamic_cast<MyObj*>(obj);
   if (myObj == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return myObj;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "file0.edl";

   // build my object
   MyObj* myObj = builder(configFilename);

   // print out some color information
   const oe::base::PairStream* colorTable = myObj->getColorTable();
   if (colorTable != nullptr) {
//    Pair* p = colorTable->findByName("green");
      const oe::base::Identifier* id = myObj->getTextColor();
      if (id != nullptr) {
         const oe::base::Pair* p = colorTable->findByName(id->getString());
         if (p != nullptr) {
            std::cout << "Text color: " << id->getString();
            const auto color = dynamic_cast<const oe::base::Color*>(p->object());
            if (color != nullptr) {
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
   const oe::base::List* vector = myObj->getVector();
   if (vector != nullptr) {
      int numValues = vector->entries();
      const auto values = new int[numValues];
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
   const oe::base::String* message = myObj->getMessage();
   std::cout << "Message: " << message->getString() << "\n";

   myObj->unref();

   return 0;
}
