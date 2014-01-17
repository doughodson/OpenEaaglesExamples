
#include "Factory.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/StateMachine.h"
#include "openeaagles/basic/Timers.h"

// Default configuration file
static const char* const DEFAULT_CONFIG_FILE = "test1.edl";

namespace Eaagles {
namespace Test {

// build a state machine
static Basic::StateMachine* builder(const char* const fileName)
{
   Basic::StateMachine* p = 0;

   // Read the description file
   int errors = 0;
   Eaagles::Basic::Object* q1 =
         Eaagles::Basic::lcParser(fileName, Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << fileName << ", errors: " << errors << std::endl;
      return 0;
   }

   if (q1 != 0) {
      // When we were given a Basic::Pair, get the pointer to its object.
      Eaagles::Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
      if (pp != 0) {
         q1 = pp->object();
      }

      // What we should have here is the State Machine object
      p = dynamic_cast<Basic::StateMachine*>(q1);
   }
    
   return p;
}

//-----------------------------------------------------------------------------
// The main test loop
//-----------------------------------------------------------------------------
static void theTest(Basic::StateMachine* sys)
{
   LCreal dt = 0.05f;  // Fake delta time

   while (sys->getState() != 99) {
      Basic::Timer::updateTimers((LCreal)dt);
      sys->updateTC(dt);
      sys->updateData(dt);
   }
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   // Config file file
   const char* configFile = DEFAULT_CONFIG_FILE;

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

   // ---
   // Read in the description files
   // ---
   Basic::StateMachine* sys = builder(configFile);
   if (sys == 0) {
      std::cerr << "Invalid configuration file!" << std::endl;
      exit(EXIT_FAILURE);
   }
   //sys->serialize(std::cout);

   // ---
   // Reset the system
   // ---
   sys->event(Eaagles::Basic::Component::RESET_EVENT);

   // ---
   // Run the test
   // ---
   theTest(sys);

   return EXIT_SUCCESS;
}

} // End TestStateMach namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Test::main(argc,argv);
}
