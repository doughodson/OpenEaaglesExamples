//------------------------------------------------------------------------------
// Test object metadata capabilities
//------------------------------------------------------------------------------

#include <iostream>

#include "openeaagles/base/ObjMetadata.hpp"

#include "openeaagles/base/Decibel.hpp"
#include "openeaagles/base/Color.hpp"
#include "openeaagles/base/Matrix.hpp"

void printMetadata(const oe::base::ObjMetadata* md)
{
   std::cout << "class name   : " << md->getClassName()   << std::endl
             << "factory name : " << md->getFactoryName() << std::endl
             << "count        : " << md->count            << std::endl
             << "mc           : " << md->mc               << std::endl
             << "tc           : " << md->tc               << std::endl;
}

int main(int, char**)
{
   std::cout << "Testing object metadata capabilities" << std::endl;

   oe::base::Decibel* db = new oe::base::Decibel();
   printMetadata(oe::base::Decibel::getMetadata());

   oe::base::Color* c1 = new oe::base::Color();
   oe::base::Color* c2 = new oe::base::Color();
   oe::base::Color* c3 = new oe::base::Color();
   c2->unref();
   printMetadata(oe::base::Color::getMetadata());

   oe::base::Matrix* matrix1 = new oe::base::Matrix();
   printMetadata(oe::base::Matrix::getMetadata());

   return 0;
}

