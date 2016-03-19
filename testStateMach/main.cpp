
#include "factory.h"

#include "openeaagles/base/parser.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/StateMachine.h"
#include "openeaagles/base/Timers.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace test {

// state machine builder
static base::StateMachine* builder(const char* const filename)
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
   base::StateMachine* stateMachine = dynamic_cast<base::StateMachine*>(obj);
   if (stateMachine == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return stateMachine;
}

// main test loop
static void theTest(base::StateMachine* stateMachine)
{
   double dt = 0.05;  // Fake delta time

   while (stateMachine->getState() != 99) {
      base::Timer::updateTimers(static_cast<double>(dt));
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
   base::StateMachine* stateMachine = builder(configFilename);

   //stateMachine->serialize(std::cout);

   // reset the system
   stateMachine->event(oe::base::Component::RESET_EVENT);

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
