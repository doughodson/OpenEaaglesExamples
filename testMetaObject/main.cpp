//------------------------------------------------------------------------------
// Test object Meta-Object capabilities
//------------------------------------------------------------------------------

#include <iostream>

#include "openeaagles/base/MetaObject.hpp"

#include "openeaagles/base/Decibel.hpp"
#include "openeaagles/base/Color.hpp"
#include "openeaagles/base/Matrix.hpp"

void printMetadata(const oe::base::MetaObject* metaObject)
{
   std::cout << "class name   : " << metaObject->getClassName()   << std::endl
             << "factory name : " << metaObject->getFactoryName() << std::endl
             << "count        : " << metaObject->count            << std::endl
             << "mc           : " << metaObject->mc               << std::endl
             << "tc           : " << metaObject->tc               << std::endl;
}

int main(int, char**)
{
   std::cout << "Testing object metadata capabilities" << std::endl;

   const auto db = new oe::base::Decibel();
   printMetadata(oe::base::Decibel::getMetaObject());

   const auto c1 = new oe::base::Color();
   const auto c2 = new oe::base::Color();
   const auto c3 = new oe::base::Color();
   c2->unref();
   printMetadata(oe::base::Color::getMetaObject());

   const auto matrix1 = new oe::base::Matrix();
   printMetadata(oe::base::Matrix::getMetaObject());

   return 0;
}
