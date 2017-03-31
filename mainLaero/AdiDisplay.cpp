
#include "AdiDisplay.hpp"

#include "TestStation.hpp"

#include "openeaagles/models/player/AirVehicle.hpp"

#include "openeaagles/base/osg/Vec3d"

#include "openeaagles/base/units/Distances.hpp"
#include "openeaagles/base/units/Times.hpp"

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(AdiDisplay, "AdiDisplay")
EMPTY_SERIALIZER(AdiDisplay)
EMPTY_DELETEDATA(AdiDisplay)

AdiDisplay::AdiDisplay()
{
   STANDARD_CONSTRUCTOR()
}

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

   myStation = nullptr;
}

void AdiDisplay::updateData(const double dt)
{
   // Update base classes stuff
   BaseClass::updateData(dt);

   oe::base::Vec3d av;

   // get access pointer to ownship
   oe::models::Aircraft* pA = getOwnship();
   if (pA != nullptr) {
      psiRO = pA->getHeadingD();
      thtRO = pA->getPitchD();
      phiRO = pA->getRollD();
      //velRO = pA->getTotalVelocity() * base::Distance::M2NM / base::Time::S2H;
      velRO = pA->getTotalVelocityKts();
      altRO = pA->getAltitudeFt();

      av = pA->getAngularVelocities();

      pRO   = av[0] * oe::base::angle::R2DCC;
      qRO   = av[1] * oe::base::angle::R2DCC;
      rRO   = av[2] * oe::base::angle::R2DCC;

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

oe::simulation::Station* AdiDisplay::getStation()
{
   if (myStation == nullptr) {
      const auto s = dynamic_cast<oe::simulation::Station*>( findContainerByType(typeid(oe::simulation::Station)) );
      if (s != nullptr) {
         myStation = s;
      }
   }
   return myStation;
}

oe::models::Aircraft* AdiDisplay::getOwnship()
{
   oe::models::Aircraft* pA = nullptr;
   oe::simulation::Station* sta = getStation();
   if (sta != nullptr) {
      pA = dynamic_cast<oe::models::Aircraft*>(sta->getOwnship());
      //const unsigned int ffrate = 5;    //LDB
      //sta->setFastForwardRate(ffrate);  //LDB
   }
   return pA;
}
