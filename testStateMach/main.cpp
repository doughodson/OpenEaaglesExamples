
#include "Factory.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/StateMachine.h"
#include "openeaagles/basic/Timers.h"

#include <cstring>
#include <cstdlib>

namespace Eaagles {
namespace Test {

// state machine builder
static Basic::StateMachine* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Basic::StateMachine* stateMachine = dynamic_cast<Basic::StateMachine*>(obj);
   if (stateMachine == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return stateMachine;
}

// main test loop
static void theTest(Basic::StateMachine* stateMachine)
{
   LCreal dt = 0.05;  // Fake delta time

   while (stateMachine->getState() != 99) {
      Basic::Timer::updateTimers(static_cast<LCreal>(dt));
      stateMachine->updateTC(dt);
      stateMachine->updateData(dt);
   }
}

//
int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "test1.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i], "-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // ---
   // Read in the description files
   // ---
   Basic::StateMachine* stateMachine = builder(configFilename);

   //stateMachine->serialize(std::cout);

   // reset the system
   stateMachine->event(Eaagles::Basic::Component::RESET_EVENT);

   // run the test
   theTest(stateMachine);

   return EXIT_SUCCESS;
}

} // end TestStateMach namespace
} // end Eaagles namespace

//
int main(int argc, char* argv[])
{
   return Eaagles::Test::main(argc,argv);
}
