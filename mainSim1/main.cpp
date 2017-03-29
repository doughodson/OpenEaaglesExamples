
#include "openeaagles/simulation/Station.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Integer.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/base/util/system_utils.hpp"

// factories
#include "../shared/xzmq/factory.hpp"
#include "openeaagles/simulation/factory.hpp"
#include "openeaagles/models/factory.hpp"
#include "openeaagles/interop/dis/factory.hpp"
#include "openeaagles/otw/factory.hpp"
#include "openeaagles/terrain/factory.hpp"
#include "openeaagles/base/factory.hpp"

#include <string>
#include <cstdlib>

// background frame rate
const unsigned int bgRate = 10;

// class factory
oe::base::Object* factory(const std::string& name)
{
   // example libraries
   oe::base::Object* obj = oe::xzmq::factory(name);

   // framework libraries
   if (obj == nullptr) obj = oe::otw::factory(name);
   if (obj == nullptr) obj = oe::simulation::factory(name);
   if (obj == nullptr) obj = oe::models::factory(name);
   if (obj == nullptr) obj = oe::terrain::factory(name);
   if (obj == nullptr) obj = oe::dis::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);
   return obj;
}

// station builder
oe::simulation::Station* builder(const std::string& filename)
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
   const auto station = dynamic_cast<oe::simulation::Station*>(obj);
   if (station == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return station;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "test0.edl";

   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build Station
   oe::simulation::Station* station = builder(configFilename);

   // send a reset event and frame sim once
   station->event(oe::base::Component::RESET_EVENT);
   station->tcFrame( static_cast<double>(1.0/static_cast<double>(station->getTimeCriticalRate())) );

   // create time critical thread
   station->createTimeCriticalProcess();
   // short pause to allow os to startup thread
   oe::base::msleep(2000);

   // calc delta time for background thread
   const double dt = 1.0/static_cast<double>(bgRate);

   // system Time of Day
   double simTime = 0.0;                                   // Simulator time reference
   const double startTime = oe::base::getComputerTime();   // Time of day (sec) run started

   int k = 0;
   std::cout << "Starting background main loop ..." << std::endl;
   for(;;) {

      // update background thread
      station->updateData( static_cast<double>(dt) );

      simTime += dt;                                       // time of next frame
      const double timeNow = oe::base::getComputerTime();  // time now
      const double elapsedTime = timeNow - startTime;
      const double nextFrameStart = simTime - elapsedTime;
      const auto sleepTime = static_cast<int>(nextFrameStart*1000.0);

      // wait for the next frame
      if (sleepTime > 0)
         oe::base::msleep(sleepTime);

      std::cout << ".";
      k += 1;
      if ( k == 40 ) {
         std::cout << "\n";
         k = 0;
      }
   }
   return 0;
}
