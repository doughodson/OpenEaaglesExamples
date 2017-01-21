//------------------------------------------------------------------------------
// Test object metadata capabilities
//------------------------------------------------------------------------------

#include <iostream>

#include "openeaagles/base/Metadata.hpp"

#include "openeaagles/base/Decibel.hpp"
#include "openeaagles/base/Color.hpp"
#include "openeaagles/base/Matrix.hpp"

void printMetadata(const oe::base::Metadata* md)
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

   const auto db = new oe::base::Decibel();
   printMetadata(oe::base::Decibel::getMetadata());

   const auto c1 = new oe::base::Color();
   const auto c2 = new oe::base::Color();
   const auto c3 = new oe::base::Color();
   c2->unref();
   printMetadata(oe::base::Color::getMetadata());

   const auto matrix1 = new oe::base::Matrix();
   printMetadata(oe::base::Matrix::getMetadata());

   return 0;
}

