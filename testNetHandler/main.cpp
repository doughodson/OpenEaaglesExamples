//-----------------------------------------------------------------------------
// Test NetHandler functionality
//-----------------------------------------------------------------------------

#include "Endpoint.h"
#include "Sender.h"
#include "Echo.h"

#include "openeaagles/base/parser.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/util/system.h"

// factories
#include "openeaagles/base/factory.h"
#include "../shared/xzmq/factory.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace test {

const unsigned int UPDATE_RATE = 10;  // main loop update rate (Hz)

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   if ( name == Sender::getFactoryName() ) {
      obj = new Sender();
   }
   else if ( name == Echo::getFactoryName() ) {
      obj = new Echo();
   }

   // example libraries
   if (obj == nullptr) obj = xzmq::factory(name);
   // framework libraries
   if (obj == nullptr) obj = base::factory(name);

   return obj;
}

// endpoint builder
Endpoint* builder(const std::string& filename)
{
   // read configuration file
   int errors = 0;
   base::Object* obj = base::edlParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Endpoint* endpoint = dynamic_cast<Endpoint*>(obj);
   if (endpoint == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return endpoint;
}

//
int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "configs/senderUdpBroadcast.edl";
   // parse command line arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build an endpoint
   Endpoint* endpoint = builder(configFilename);

   // send a reset event
   std::cout << "Reset event: which will establish the networks." << std::endl;
   endpoint->event(base::Component::RESET_EVENT);

   // system time of day
   const double dt = 1.0 / static_cast<double>(UPDATE_RATE);   // Delta time
   double simTime = 0.0;                         // Simulator time reference
   double startTime = base::getComputerTime();   // Time of day (sec) run started

   // main loop
   std::cout << "Starting main loop ..." << std::endl;
   for(;;) {

      endpoint->updateTC( static_cast<double>(dt) );
      endpoint->updateData( static_cast<double>(dt) );

      simTime += dt;                             // time of next frame
      double timeNow = base::getComputerTime();  // time now

      double elapsedTime = timeNow - startTime;
      double nextFrameStart = simTime - elapsedTime;
      int sleepTime = static_cast<int>(nextFrameStart*1000.0);

      // wait for the next frame
      if (sleepTime > 0)
         base::msleep(sleepTime);
   }

   return EXIT_SUCCESS;
}

}
}

//
int main(int argc, char* argv[])
{
   oe::test::main(argc, argv);
}
