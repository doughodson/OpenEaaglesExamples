//------------------------------------------------------------------------------
// Test Matrix class functions
//------------------------------------------------------------------------------

#include "openeaagles/base/Matrix.hpp"
#include "openeaagles/base/Vectors.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include <iostream>
#include <iomanip>

using namespace oe::base;

namespace d {   // constants that define matrix dimensions
const unsigned int rows = 4;
const unsigned int cols = 4;
const unsigned int size = rows * cols;
}

// Size = 3
//double pArr[] = {4,-1,1,-1,3,-2,1,-2,3};

// Size = 4
const double pArr[] = {4,1,-2,2,1,2,0,1,-2,0,3,-2,2,1,-2,-1};

////////////////////////////////////////////////////////////////////////////////
void testConstructors();
void testInformation();
void testOverloadedOps();
void test_getQR();
void test_getLU();
void test_getCholesky();
void test_getTriDiagonal();
void test_getEigenPower();
void test_getInverse();

int main(int argc, char**)
{
   std::cout << "===============================================================" << std::endl;
   // Select a matrix feature to test
   std::cout << "Select a Matrix function test:" << std::endl;
   std::cout << "   1) testConstructors()" << std::endl
             << "   2) testInformation()" << std::endl
             << "   3) testOverloadedOps()" << std::endl
             << "   4) getQR()" << std::endl
             << "   5) getLU()" << std::endl
             << "   6) getCholesky()" << std::endl
             << "   7) getTriDiagonal()" << std::endl
             << "   8) getEigenPower()" << std::endl
             << "   9) getInverse()" << std::endl
             << std::endl;

   int num = 0;
   std::cout << "Enter a number: ";
   std::cin >> num;

   switch (num)
   {
      case 1:
         testConstructors();
         break;

      case 2:
         testInformation();
         break;

      case 3:
         testOverloadedOps();
         break;

      case 4:
         test_getQR();
         break;

      case 5:
         test_getLU();
         break;

      case 6:
         test_getCholesky();
         break;

      case 7:
         test_getTriDiagonal();
         break;

      case 8:
         test_getEigenPower();
         break;

      case 9:
         test_getInverse();
         break;

      default:
         std::cout << "Bad selection." << std::endl;
         break;
   }
   return 0;
}

//------------------------------------------------------------------------------
// Test Matrix class constructors
//------------------------------------------------------------------------------
void testConstructors()
{
   // Test Matrix class constructors
   std::cout << "=============================================" << std::endl;
   std::cout << "Test constructors" << std::endl;

   //---------------------------------------------
   // Default Constructor
   // The default matrix has mda = rows = cols = 0
   //---------------------------------------------
   Matrix A;                                      // default declaration
   std::cout << "A = " << std::endl;              // Matrix name associated with matrix output in next step.
   std::cout << A << std::endl;                   // Matrix not displayed by "<<" since it is not a "good" matrix.
   std::cout << "A = " << std::endl;
   A.showMatrix(); std::cout << std::endl;        // Matrix cannot be displayed by showMatrix (same reason).

   //---------------------------------------------
   // Size Constructor
   //---------------------------------------------
   Matrix B(d::rows, d::cols);                    // Creates a rows x cols matrix with all zero elements.
   B.setFldWidth(12);                             // Field width is set to 12 for each matrix element.
   B.setDecPoint(5);                              // Decimal point is set to 5 digits of precision.
   std::cout << "B = " << std::endl;
   std::cout << B << std::endl;                   // Matrix displayed using overloaded "<<" operator
                                                  // Note that decimal point = 5 and all elements are zero,
                                                  // as expected, but field width = 10, not 12. The overloaded
                                                  // operator "<<" always calculates an appropriate field
                                                  // width regardless of the current setting.
   std::cout << "B = " << std::endl;
   B.showMatrix(4); std::cout << std::endl;       // Matrix displayed using "showMatrix" member function
                                                  // with 4 decimal point precision and field width = 12.

   //---------------------------------------------
   // Data Constructor
   //---------------------------------------------
   const auto pM1 = new Matrix(d::rows, d::cols, pArr, d::size); // Constructor allocates memory for a 3x3 matrix and
                                                                 // inits matrix with data from array pArr and returns
                                                                 // a pointer to the matrix
   std::cout << "M1 = " << std::endl;
   std::cout << *pM1 << std::endl;                               // Note fldWidth=DEF_FLDWIDTH and decPoint=DEF_DECPOINT
   std::cout << "M1 = " << std::endl;
   pM1->showMatrix(3,10); std::cout << std::endl;                // Note that showMatrix used decPoint=3 to set decimal
                                                                 // precision and fldWidth=10.

   //---------------------------------------------
   // Copy Constructor
   //---------------------------------------------
   const auto pM2 = new Matrix(*pM1);                // Constructor creates a new matrix D with the same
                                                     // elements as matrix C.
   pM2->setDecPoint(8);
   pM2->setFldWidth(11);                             // This field width leaves no margin between row elements
                                                     // in this example.
   std::cout << "M2 = " << std::endl;
   std::cout << *pM2 << std::endl;                   // The output for the matrix is FW=14 and DP=8.
   std::cout << "M2 = " << std::endl;
   pM2->showMatrix(6,9); std::cout << std::endl;     // Since the field width value of 9 would leaves no space
                                                     // between some of the matrix elements, the function
                                                     // showMatrix calculates a field width that leaves >= 2
                                                     // spaces between row elements for readability.

   //---------------------------------------------
   // cleanup
   //---------------------------------------------
   if (pM1 != nullptr) pM1->unref();                    // Decrement the reference counter for pointer pM1
   if (pM2 != nullptr) pM2->unref();                    // Decrement the reference counter for pointer pM2.

}

//------------------------------------------------------------------------------
// Test Matrix class information access
//------------------------------------------------------------------------------
void testInformation()
{
   // Test Matrix class information functions
   std::cout << "=============================================" << std::endl;
   std::cout << "Test information functions" << std::endl;

   //---------------------------------------------
   // Matrix data
   //---------------------------------------------
   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   // Numerical info
   std::cout << "Rows             = " << pA->getRows()        << std::endl;
   std::cout << "Columns          = " << pA->getCols()        << std::endl;
   std::cout << "Field Width      = " << pA->getFldWidth()    << std::endl;
   std::cout << "Precision        = " << pA->getDecPoint()    << std::endl;
   std::cout << "Max Mag          = " << pA->getMaxMag()      << std::endl;
   std::cout << "Min Mag          = " << pA->getMinMag()      << std::endl;
   std::cout << "Element(1,2)     = " << pA->getElem(1,2)     << std::endl;

   // Boolean info
   std::cout << "Good index(1,0)? = " << std::boolalpha << pA->isGoodIndex(1,0) << std::endl;
   std::cout << "Good index(1,8)? = " << std::boolalpha << pA->isGoodIndex(1,8) << std::endl;
   std::cout << "Good matrix?     = " << std::boolalpha << pA->isGoodMatrix()   << std::endl;
   std::cout << "Square?          = " << std::boolalpha << pA->isSquare()       << std::endl;
   std::cout << "Symmetric?       = " << std::boolalpha << pA->isSymmetric()    << std::endl;

   // Cleanup
   if (pA != nullptr) pA->unref();                    // Decrement the reference counter for pointer pA
}

//------------------------------------------------------------------------------
// Test Matrix class overloaded operators
//------------------------------------------------------------------------------
void testOverloadedOps()
{
   // Test Matrix class overloaded operators
   std::cout << "=============================================" << std::endl;
   std::cout << "Test overloaded operators" << std::endl;

   //---------------------------------------------
   // Matrix data
   //---------------------------------------------
   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   // overloaded "="
   Matrix B = *pA;  // Now matrix A and B are identical
   std::cout << "B = " << std::endl;
   B.showMatrix(); std::cout << std::endl;

   // overloaded "()"
   std::cout << "B(1,1)     = " << B(1,1) << std::endl;

   // overloaded "[]"
   std::cout << "B[2]       = " << B[2] << std::endl;
   std::cout << std::endl;

   // overloaded "=="
   std::cout << "A == B (?) = " << std::boolalpha << (*pA == B) << std::endl;
   std::cout << "A != B (?) = " << std::boolalpha << (*pA != B) << std::endl;

   // overloaded "!="
   B(0,0) = 0.0;  // Now matrix A and B are different
   std::cout << "A == B (?) = " << std::boolalpha << (*pA == B) << std::endl;
   std::cout << "A != B (?) = " << std::boolalpha << (*pA != B) << std::endl;
   std::cout << std::endl;

   // overloaded "<<"
   std::cout << "B = " << std::endl << B << std::endl;

   const auto pV = new CVector(3);
   (*pV)[0] = std::sqrt(2.0);
   (*pV)[1] = std::log(2.0);
   (*pV)[2] = std::exp(2.0);

   pV->setDecPoint(7);
   pV->setFldWidth(15);
   std::cout << "DP = " << pV->getDecPoint() << std::endl;
   std::cout << "FW = " << pV->getFldWidth() << std::endl;
   std::cout << "V = " << std::endl;
   std::cout << *pV << std::endl;              // Note field width setting of 15 is ignored for
                                               // display with "<<"

   std::cout << "DP = " << pV->getDecPoint() << std::endl;
   std::cout << "FW = " << pV->getFldWidth() << std::endl;
   std::cout << "V = " << std::endl;
   pV->showVector(3,16);

   // Cleanup
   if (pA != nullptr) pA->unref();                    // Decrement the reference counter for pointer pA
   if (pV != nullptr) pV->unref();                    // Decrement the reference counter for pointer pV
}

//------------------------------------------------------------------------------
// Test Matrix class transformation functions
//------------------------------------------------------------------------------
void test_getTriDiagonal()
{
   // Test "getTriDiagonal"
   std::cout << "=============================================" << std::endl;
   std::cout << "Test getTriDiagonal" << std::endl;

   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);

   // Show the base matrix
   std::cout << "=============================================" << std::endl;
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   const auto pB = new Matrix(d::rows, d::cols);
   bool b1 = pA->getTriDiagonal(pB);
   std::cout << "getTriDiagonal function return value = " << std::boolalpha << b1 << std::endl;
   std::cout << std::endl;

   std::cout << "getTriDiagonal = " << std::endl;
   pB->showMatrix(); std::cout << std::endl;

   // cleanup
   if (pA != nullptr) pA->unref();                    // Decrement the reference counter for pointer pA
   if (pB != nullptr) pB->unref();                    // Decrement the reference counter for pointer pB
}

//------------------------------------------------------------------------------
void test_getQR()
{
   // Test "getQR"
   std::cout << "=============================================" << std::endl;
   std::cout << "Test getQR" << std::endl;

   const auto pA = new Matrix(d::rows, d::cols,pArr, d::size);

   // Show the base matrix
   std::cout << "=============================================" << std::endl;
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   const auto pQ = new Matrix(d::rows, d::cols);
   const auto pR = new Matrix(d::rows, d::cols);
   bool b1 = pA->getQR(pQ, pR);
   std::cout << "getQR function return value = " << std::boolalpha << b1 << std::endl;
   std::cout << std::endl;

   std::cout << "Q = " << std::endl;
   pQ->showMatrix(); std::cout << std::endl;

   std::cout << "R = " << std::endl;
   pR->showMatrix(); std::cout << std::endl;

   std::cout << "R = upper triangular (?)" << std::endl;
   std::cout << "Q = orthogonal (?)" << std::endl;
   std::cout << "det(Q) = " << pQ->getDeterm() << std::endl;
   std::cout << std::endl;

   Matrix* pQT = pQ->getTranspose();
   std::cout << "transpose(Q) = Q' (?)" << std::endl;
   pQT->showMatrix(); std::cout << std::endl;

   Matrix* pQinv = pQ->getInvLU();
   std::cout << "inverse(Q) = Q' (?)" << std::endl;
   pQinv->showMatrix(); std::cout << std::endl;

   Matrix* pI = multiply(*pQ, *pQinv);
   std::cout << "Q * Qinv = I (?)" << std::endl;
   pI->showMatrix(); std::cout << std::endl;

   // get eigenvalues
   auto pB = new Matrix(*pA);
   for (int i=0; i<10; i++)
   {
      pB->getQR(pQ, pR);
      pB = multiply(*pR, *pQ);
   }
   std::cout << "R * Q (after 10 iterations) = " << std::endl;
   pB->showMatrix(); std::cout << std::endl;
   CVector* pV = getDiag(*pB);
   std::cout << "Diagonal = eigenvalue estimates" << std::endl;
   pV->showVector(); std::cout << std::endl;

   // cleanup
   if (pQ != nullptr) pQ->unref();                      // Decrement the reference counter for pointer pQ
   if (pR != nullptr) pR->unref();                      // Decrement the reference counter for pointer pR
   if (pQT != nullptr) pQT->unref();                    // Decrement the reference counter for pointer pQT
   if (pQinv != nullptr) pQinv->unref();                // Decrement the reference counter for pointer pQinv
   if (pI != nullptr) pI->unref();                      // Decrement the reference counter for pointer pI
}

//------------------------------------------------------------------------------
void test_getLU()
{
   // Test "getLU"
   std::cout << "=============================================" << std::endl;
   std::cout << "Test getLU" << std::endl;

   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);

   // Show the base matrix
   std::cout << "=============================================" << std::endl;
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   const auto pL = new Matrix(d::rows,d::cols);
   const auto pU = new Matrix(d::rows,d::cols);
   bool b1 = pA->getLU(pL, pU);
   std::cout << "getLU function return value = " << std::boolalpha << b1 << std::endl;
   std::cout << std::endl;

   std::cout << "L = " << std::endl;
   pL->showMatrix(); std::cout << std::endl;

   CVector* pV = getDiag(*pL);
   std::cout << "Diagonal = all 1's (?)" << std::endl;
   pV->showVector(); std::cout << std::endl;

   std::cout << "U = " << std::endl;
   pU->showMatrix(); std::cout << std::endl;

   Matrix* pB = multiply(*pL, *pU);
   std::cout << "L*U = A (?)" << std::endl;
   pB->showMatrix(); std::cout << std::endl;

   // cleanup
   if (pA != nullptr) pA->unref();                     // Decrement the reference counter for pointer pA
   if (pB != nullptr) pB->unref();                     // Decrement the reference counter for pointer pB
   if (pL != nullptr) pL->unref();                     // Decrement the reference counter for pointer pL
   if (pU != nullptr) pU->unref();                     // Decrement the reference counter for pointer pU
   if (pV != nullptr) pV->unref();                     // Decrement the reference counter for pointer pV
}

//------------------------------------------------------------------------------
void test_getCholesky()
{
   // Test "getCholesky"
   std::cout << "=============================================" << std::endl;
   std::cout << "Test getCholesky" << std::endl;

   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);

   // Show the base matrix
   std::cout << "=============================================" << std::endl;
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   const auto pL = new Matrix(d::rows, d::cols);
   const auto pU = new Matrix(d::rows, d::cols);
   bool b1 = pA->getCholesky(pL, pU);
   std::cout << "getCholesky function return value = " << std::boolalpha << b1 << std::endl;
   std::cout << std::endl;

   if (pL != nullptr) {
      std::cout << "L = " << std::endl;
      pL->showMatrix(); std::cout << std::endl;
   }

   if (pU != nullptr) {
      std::cout << "U = " << std::endl;
      pU->showMatrix(); std::cout << std::endl;
   }

   Matrix* pB = multiply(*pL, *pU);
   if (pB != nullptr) {
      std::cout << "L*U = A (?)" << std::endl;
      pB->showMatrix(); std::cout << std::endl;
   }

   // cleanup
   if (pA != nullptr) pA->unref();                      // Decrement the reference counter for pointer pA
   if (pB != nullptr) pB->unref();                      // Decrement the reference counter for pointer pB
   if (pL != nullptr) pL->unref();                      // Decrement the reference counter for pointer pL
   if (pU != nullptr) pU->unref();                      // Decrement the reference counter for pointer pU
}

//------------------------------------------------------------------------------
void test_getEigenPower()
{
   double maxErr = .0001;
   int maxIter = 100;
   double Val = 0.0;
   const auto pVec = new CVector(d::rows);

   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);

   // Show the base matrix
   std::cout << "=============================================" << std::endl;
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   bool b1 = pA->getEigenPower(maxErr, maxIter, &Val, pVec);
   std::cout << "getEigenPower function return value = " << std::boolalpha << b1 << std::endl;
   std::cout << std::endl;

   std::cout << std::setprecision(4);
   std::cout << "Eigenvalue = " << Val << std::endl;
   std::cout << "EigenVector = " << std::endl << *pVec << std::endl;

   CVector* pV1 = multiply(*pA, *pVec);
   std::cout << "A*Vec = " << std::endl;
   pV1->showVector(6); std::cout << std::endl;

   CVector* pV2 = multiply(*pVec, Val);
   std::cout << "Vec*Val = " << std::endl;
   pV2->showVector(6); std::cout << std::endl;

   CVector* pErr = subtract(*pV1, *pV2);
   double NormErr = pErr->getNorm();
   std::cout << "Err = " << std::endl;
   pErr->showVector(6); std::cout << std::endl;
   std::cout << "normalized error = " << std::endl << NormErr << std::endl;

   // cleanup
   pVec->unref();
   pA->unref();
   pV1->unref();
   pV2->unref();
   pErr->unref();
}

//------------------------------------------------------------------------------
void test_getInverse()
{
   const auto pA = new Matrix(d::rows, d::cols, pArr, d::size);
   auto pI = new Matrix(d::rows, d::cols);

   // Show the base matrix
   std::cout << "=============================================" << std::endl;
   std::cout << "A = " << std::endl;
   pA->showMatrix(); std::cout << std::endl;

   // Calculate inverse by GJ method
   Matrix* pInv = pA->getInvGJ();
   std::cout << "inv(A) by Gauss-Jordan method = " << std::endl;
   pInv->showMatrix(); std::cout << std::endl;
   std::cout << "A * inv(A) = " << std::endl;
   pI = multiply(*pA, *pInv);
   pI->showMatrix(); std::cout << std::endl;

   // Calculate inverse by LU method
   pInv = pA->getInvLU();
   std::cout << "inv(A) by LU method = " << std::endl;
   pInv->showMatrix(); std::cout << std::endl;
   std::cout << "A * inv(A) = " << std::endl;
   pI = multiply(*pA, *pInv);
   pI->showMatrix(); std::cout << std::endl;

   // cleanup
   pA->unref();
   pI->unref();
   pInv->unref();
}
