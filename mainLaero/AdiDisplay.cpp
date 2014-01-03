//------------------------------------------------------------------------------
// Class: AdiDisplay
//------------------------------------------------------------------------------

#include "AdiDisplay.h"

#include "TestStation.h"

#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/basic/osg/Vec3"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/units/Times.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(AdiDisplay,"AdiDisplay")
EMPTY_SERIALIZER(AdiDisplay)
EMPTY_DELETEDATA(AdiDisplay)

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// constructor
AdiDisplay::AdiDisplay() : myStation(0)
{
   STANDARD_CONSTRUCTOR()

   psiRO    = 0.0;
   thtRO    = 0.0;
   phiRO    = 0.0;
   velRO    = 0.0;
   altRO    = 0.0;
   pRO      = 0.0;
   qRO      = 0.0;
   rRO      = 0.0;
   bankADI  = 0.0; 
   pitchADI = 0.0;

   psiRO_SD.empty();
   thtRO_SD.empty();
   phiRO_SD.empty();
   velRO_SD.empty();
   altRO_SD.empty();
   pRO_SD.empty();
   qRO_SD.empty();
   rRO_SD.empty();
   bankADI_SD.empty();
   pitchADI_SD.empty();
}

// copy member data
void AdiDisplay::copyData(const AdiDisplay& org, const bool)
{
   BaseClass::copyData(org);

   psiRO    = org.psiRO;   
   thtRO    = org.thtRO;   
   phiRO    = org.phiRO;   
   velRO    = org.velRO;   
   altRO    = org.altRO;   
   pRO      = org.pRO;     
   qRO      = org.qRO;     
   rRO      = org.rRO;     
   bankADI  = org.bankADI; 
   pitchADI = org.pitchADI;

   myStation = 0;
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void AdiDisplay::updateData(const LCreal dt)
{
   // Update base classes stuff
   BaseClass::updateData(dt);

   Eaagles::osg::Vec3d av;

   // get access pointer to ownship
   Simulation::Aircraft* pA = getOwnship();
   if (pA != 0) {
      psiRO = pA->getHeadingD();
      thtRO = pA->getPitchD();
      phiRO = pA->getRollD();
      //velRO = pA->getTotalVelocity() * Basic::Distance::M2NM / Basic::Time::S2H;
      velRO = pA->getTotalVelocityKts();
      altRO = pA->getAltitudeFt();
      
      av = pA->getAngularVelocities();
      
      pRO   = av[0] * Basic::Angle::R2DCC;
      qRO   = av[1] * Basic::Angle::R2DCC;
      rRO   = av[2] * Basic::Angle::R2DCC;
      
      pitchADI = pA->getPitchD();
      bankADI  = pA->getRollD();
   }

   // now send the data
   send("psiRO", UPDATE_VALUE, psiRO, psiRO_SD);
   send("thtRO", UPDATE_VALUE, thtRO, thtRO_SD);
   send("phiRO", UPDATE_VALUE, phiRO, phiRO_SD);
   send("velRO", UPDATE_VALUE, velRO, velRO_SD);
   send("altRO", UPDATE_VALUE, altRO, altRO_SD);
   
   send("pRO",  UPDATE_VALUE, pRO, pRO_SD);
   send("qRO",  UPDATE_VALUE, qRO, qRO_SD);
   send("rRO",  UPDATE_VALUE, rRO, rRO_SD);

   // adi information
   send("mfdADI", UPDATE_INSTRUMENTS, pitchADI, pitchADI_SD);
   send("mfdADI", UPDATE_VALUE,       bankADI,  bankADI_SD);
   //send("pitchangle",   UPDATE_INSTRUMENTS, pitch,    pitchSD);
}

//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
Simulation::Station* AdiDisplay::getStation()
{
   if (myStation == 0) {
      Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
      if (s != 0) {
         myStation = s;
      }
   }
   return myStation;
}

Simulation::Aircraft* AdiDisplay::getOwnship()
{
   Simulation::Aircraft* pA = 0;
   Simulation::Station* sta = getStation();
   if (sta != 0) {
      pA = dynamic_cast<Simulation::Aircraft*>(sta->getOwnship());

      const unsigned int ffrate = 5;    //LDB
      sta->setFastForwardRate(ffrate);  //LDB
   }
   return pA;
}

}
}

