//-----------------------------------------------------------------------------
// Test NetHandler functionality
//-----------------------------------------------------------------------------

#include "Endpoint.h"
#include "Sender.h"
#include "Echo.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

// factories
#include "openeaagles/basic/factory.h"
#include "../shared/xzmq/factory.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace test {

const float UPDATE_RATE = 10.0; // main loop update rate

// our class factory
static basic::Object* factory(const char* name)
{
   basic::Object* obj = nullptr;

   if ( std::strcmp(name, Sender::getFactoryName()) == 0 ) {
      obj = new Sender();
   }
   else if ( std::strcmp(name, Echo::getFactoryName()) == 0 ) {
      obj = new Echo();
   }

   // example libraries
   if (obj == nullptr) obj = xZeroMQHandlers::factory(name);
   // framework libraries
   if (obj == nullptr) obj = basic::factory(name);

   return obj;
}

// endpoint builder
static Endpoint* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   basic::Object* obj = basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a basic::Pair, if so, point to object in Pair, not Pair itself
   basic::Pair* pair = dynamic_cast<basic::Pair*>(obj);
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
   const char* configFilename = "configs/senderUdpBroadcast.edl";
   // parse command line arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build an endpoint
   Endpoint* endpoint = builder(configFilename);

   // send a reset event
   std::cout << "Reset event: which will establish the networks." << std::endl;
   endpoint->event(basic::Component::RESET_EVENT);

   // system time of day
   double dt = 1.0/static_cast<double>(UPDATE_RATE);             // Delta time
   double simTime = 0.0;                            // Simulator time reference
   double startTime = oe::getComputerTime();   // Time of day (sec) run started

   // main loop
   std::cout << "Starting main loop ..." << std::endl;
   for(;;) {

      endpoint->updateTC( static_cast<LCreal>(dt) );
      endpoint->updateData( static_cast<LCreal>(dt) );

      simTime += dt;                       // time of next frame
      double timeNow = oe::getComputerTime();  // time now

      double elapsedTime = timeNow - startTime;
      double nextFrameStart = simTime - elapsedTime;
      int sleepTime = static_cast<int>(nextFrameStart*1000.0);

      // wait for the next frame
      if (sleepTime > 0)
         lcSleep(sleepTime);
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
