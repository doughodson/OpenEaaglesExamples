//------------------------------------------------------------------------------
// Basic::Timer test program
//
// 1) Reads an EDL file that must contain our Tester component and timers to be tested.
// 2) Creates a periodic thread to call Basic::Timer::updateTimers();
// 3) Runs the timers for 'MAIN_TIMER_VALUE' seconds, while printing the timer
//    values at a 'TIMERS_PRINT_RATE' rate
// 4) Restarts all of the Tester's timers
// 5) Runs a second pass
//
//------------------------------------------------------------------------------

#include "Tester.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Thread.h"

// class factories
#include "openeaagles/basic/Factory.h"

namespace Eaagles {
namespace Test {

static const double MAIN_TIMER_VALUE = 10.0; // Sec
static const double TIMERS_PRINT_RATE = 5;   // Hz

//------------------------------------------------------------------------------
// Timer thread
//------------------------------------------------------------------------------
static const double THREAD_RATE = 20.0;      // hz
static const double THREAD_PRI  =  0.5;      // Pri (0 .. 1)

class TimerThread : public Basic::ThreadPeriodicTask {
   DECLARE_SUBCLASS(TimerThread,Basic::ThreadPeriodicTask)
   public: TimerThread(Basic::Component* const parent, const LCreal priority, const LCreal rate);
   private: virtual unsigned long userFunc(const LCreal dt);
};

IMPLEMENT_SUBCLASS(TimerThread,"TimerThread")
EMPTY_SLOTTABLE(TimerThread)
EMPTY_COPYDATA(TimerThread)
EMPTY_DELETEDATA(TimerThread)
EMPTY_SERIALIZER(TimerThread)

TimerThread::TimerThread(Basic::Component* const parent, const LCreal priority, const LCreal rate)
      : ThreadPeriodicTask(parent, priority, rate)
{
   STANDARD_CONSTRUCTOR()
}

unsigned long TimerThread::userFunc(const LCreal dt)
{
   Basic::Timer::updateTimers(dt);
   return 0;
}

//------------------------------------------------------------------------------
// createTheThread() -- Create the data acq thread
//------------------------------------------------------------------------------
TimerThread* createTheThread(Tester* const tester)
{
   TimerThread* thread = new TimerThread(tester, THREAD_PRI, THREAD_RATE);

   bool ok = thread->create();
   if (!ok) {
      thread = 0;
      std::cerr << "createTheThread(): ERROR, failed to create the thread!" << std::endl;
   }

   return thread;
}

// our class factory
static Basic::Object* factory(const char* const name)
{
  Basic::Object* obj = 0;

  if ( strcmp(name, Tester::getFactoryName()) == 0 ) {
    obj = new Tester;
  }
   
  // Default to base classes
  if (obj == 0) obj = Basic::Factory::createObj(name);
  return obj;
}

// build a tester
static Tester* builder(const char* const testFileName)
{
    // Read the description file
    int errors = 0;
    Basic::Object* q1 = Basic::lcParser(testFileName, factory, &errors);
    if (errors > 0) {
        std::cerr << "Errors in reading file: " << errors << std::endl;
        exit(1);
    }

    // Set 'sys' to our basic description object.
    Tester* sys = 0;
    if (q1 != 0) {

        // When we were given a Pair, get the pointer to its object.
        Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
        if (pp != 0) {
           std::cout << "Form: " << *pp->slot() << std::endl;
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'Tester'.
        sys = dynamic_cast<Tester*>(q1);
    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //sys->serialize(std::cout);
    return sys;
}


//------------------------------------------------------------------------------
// Run the test
//------------------------------------------------------------------------------
void run(Tester* const tester)
{
   if (tester != 0) {
      Basic::Timer::freeze(true);

      // Time between printing the timer data
      double dt = 1.0/double(TIMERS_PRINT_RATE);

      // Our main test control timer
      Basic::UpTimer* mainTimer = new Basic::UpTimer();
      mainTimer->setAlarmTime(MAIN_TIMER_VALUE);
      mainTimer->start();


      // ---
      // First pass
      // ---
      std::cout << "#### First Test ####" << std::endl;

      Basic::Timer::freeze(false);
      while ( !mainTimer->alarm()) {
         lcSleep( (unsigned int)(dt * 1000.0 + 0.5) );
         printf("time(%4.1f)\n", mainTimer->getCurrentTime());
         tester->printTimers();
      }


      // ---
      // Restart the timers
      // ---
      Basic::Timer::freeze(true);

      std::cout << std::endl;
      std::cout << "#### Restarting Timers (all active) ####" << std::endl;
      tester->restartAllTimers();
      mainTimer->restart();


      // ---
      // Second pass
      // ---
      std::cout << std::endl;
      std::cout << "#### Second Test ####" << std::endl;

      Basic::Timer::freeze(false);
      while ( !mainTimer->alarm()) {
         lcSleep( (unsigned int)(dt * 1000.0 + 0.5) );
         printf("time(%4.1f)\n", mainTimer->getCurrentTime());
         tester->printTimers();
      }

   }
}

//------------------------------------------------------------------------------
// main test executive
//------------------------------------------------------------------------------
int exec(int argc, char* argv[])
{

   // Config file file
   const char* configFile = "test01.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

   // Read in the description files
   Tester* tester = builder(configFile);
   if (tester != 0) {

      // create the thread
      TimerThread* thread = createTheThread(tester);
      if (thread != 0) {

         // Run the test
         run(tester);

         tester->event(Basic::Component::SHUTDOWN_EVENT);
         tester->unref();
         tester = 0;

         // Stop the thread
         thread->terminate();
         thread->unref();
         thread = 0;
      }

   }

   return 0;
}

} // namespace Test
} // namespace Eaagles

//=============================================================================
// main() -- Main routine
//=============================================================================
int main(int argc, char* argv[])
{
   Eaagles::Test::exec(argc, argv);
}

