
#include "factory.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/StateMachine.h"
#include "openeaagles/basic/Timers.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace test {

// state machine builder
static basic::StateMachine* builder(const char* const filename)
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
   basic::StateMachine* stateMachine = dynamic_cast<basic::StateMachine*>(obj);
   if (stateMachine == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return stateMachine;
}

// main test loop
static void theTest(basic::StateMachine* stateMachine)
{
   LCreal dt = 0.05;  // Fake delta time

   while (stateMachine->getState() != 99) {
      basic::Timer::updateTimers(static_cast<LCreal>(dt));
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
   basic::StateMachine* stateMachine = builder(configFilename);

   //stateMachine->serialize(std::cout);

   // reset the system
   stateMachine->event(oe::basic::Component::RESET_EVENT);

   // run the test
   theTest(stateMachine);

   return EXIT_SUCCESS;
}

} // end test namespace
} // end oe namespace

//
int main(int argc, char* argv[])
{
   return oe::test::main(argc,argv);
}
