
#ifndef __NavRadio_H__
#define __NavRadio_H__

#include "openeaagles/models/system/Radio.hpp"

namespace oe {
namespace dafif { class AirportLoader; class NavaidLoader; }
}

//------------------------------------------------------------------------------
// Class: NavRadio
// Description: General class for all navigation radio models
// The NAV radios are being updated and are not current fully functional!!!
// Factory name: NavRadio
//------------------------------------------------------------------------------
class NavRadio : public oe::models::Radio
{
   DECLARE_SUBCLASS(NavRadio, oe::models::Radio)

public:
   NavRadio();

protected:
   double getLatitude() const;
   double getLongitude() const;
   double getAltitude() const;

   oe::dafif::NavaidLoader* getNavaidLoader();
   oe::dafif::AirportLoader* getAirportLoader();

   // Slave our position to our ownship
   virtual bool setPosition();

   virtual bool shutdownNotification() override;

private:
   oe::base::safe_ptr<oe::dafif::AirportLoader> apdb; // Pointer to Airport loader
   oe::base::safe_ptr<oe::dafif::NavaidLoader> nvdb;  // Pointer to Navaid loader

   double latitude {};           // Ownship Latitude
   double longitude {};          // Ownship Longitude
   double altitude {};           // Ownship altitude HAE (ft)
};

//------------------------------------------------------------------------------
// Class: TacanRadio
// Description: Tactical air navigation system (TACAN) radio model
// Factory name: TacanRadio
//------------------------------------------------------------------------------
class TacanRadio : public NavRadio
{
   DECLARE_SUBCLASS(TacanRadio, NavRadio)

public:
   // bands
   enum class Band { TCN_X_BAND = 0, TCN_Y_BAND };

   // power modes
   enum class PwrModes {
      PWR_TCN_OFF = BaseClass::PWR_OFF,
      PWR_TCN_REC,          // REC mode
      PWR_TCN_TRAN_REC,     // T/R mode
      PWR_TCN_AA_TRAN_REC,  // AA TR mode
   };

public:
   TacanRadio();

   Band getBand() const;
   virtual bool setBand(const Band x);

   double getRange() const;       // Range (nautical miles)
   double getBearing() const;     // Bearing (degrees)

   virtual void updateData(const double dt = 0.0) override;

protected:
   // Get Range and Bearing - Input pointers for your outputs
   bool computeRangeBearing(bool* rngIsValid, double* range, double* grdrange, bool* bearingIsValid, double* bearing);

private:
   void initData();

   Band band {Band::TCN_X_BAND};

   bool rangeIsValid {};
   bool bearingIsValid {};

   double range {};
   double grdrange {};
   double bearing {};
   double destLatitude {};
   double destLongitude {};
   double currentMagVar {};
};

//------------------------------------------------------------------------------
// Class: IlsRadio
// Description: Instrument landing system (ILS) navigation radio model
// Factory name: IlsRadio
//------------------------------------------------------------------------------
class IlsRadio : public NavRadio
{
   DECLARE_SUBCLASS(IlsRadio, NavRadio)

public:
   // constants for figuring degrees to dots
   static const double GS_DEG_PER_DOT;
   static const double LOC_DEG_PER_DOT;

public:
   IlsRadio();

   //Outside Access FCNs
   double getGlideslopeDifference();
   double getLocalizerDifference();
   double getGlideslopeDifferenceDots();
   double getLocalizerDifferenceDots();

   virtual void updateData(const double dt = 0.0) override;

protected:
   //Always find the glideslope first!!!!
   virtual bool findILSGlideslopeByFreq(double freq);
   virtual bool findLocalizerByFreq(double freq);

private:
   int timerCounter {};              // For Only doing calc every so often
   bool localizerValid {};
   bool glideSlopeValid {};
   double range {};                  // slant range to the end of the runway
   double grdrange {};               // ground range to the end of the RWY
   double bearing {};                // bearing of the end of the RWY
   double destLatitude {};           // lat for end of RWY
   double destLongitude {};          // lon for end of RWY
   double deltaGlideSlope {};
   double deltaLocalizerBearing {};
   double currentMagVar {};          // mag var at glideslope emitter
   double acGlideSlope {};
   double acLocalizerBearing {};
   double ilsGlideSlope {};
   double ilsLocalizerBearing {};
};

#endif
