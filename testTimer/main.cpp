//------------------------------------------------------------------------------
// basic::Timer test program
//
// 1) Reads an EDL file that must contain our Tester component and timers to be tested.
// 2) Creates a periodic thread to call basic::Timer::updateTimers();
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

// class factory
#include "openeaagles/basic/Factory.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace oe {
namespace test {

static const double MAIN_TIMER_VALUE = 10.0; // Sec
static const double TIMERS_PRINT_RATE = 5;   // Hz

//------------------------------------------------------------------------------
// Timer thread
//------------------------------------------------------------------------------
static const double THREAD_RATE = 20.0;      // hz
static const double THREAD_PRI  =  0.5;      // Pri (0 .. 1)

class TimerThread : public basic::ThreadPeriodicTask {
   DECLARE_SUBCLASS(TimerThread,basic::ThreadPeriodicTask)
   public: TimerThread(basic::Component* const parent, const LCreal priority, const LCreal rate);
   private: virtual unsigned long userFunc(const LCreal dt);
};

IMPLEMENT_SUBCLASS(TimerThread,"TimerThread")
EMPTY_SLOTTABLE(TimerThread)
EMPTY_COPYDATA(TimerThread)
EMPTY_DELETEDATA(TimerThread)
EMPTY_SERIALIZER(TimerThread)

TimerThread::TimerThread(basic::Component* const parent, const LCreal priority, const LCreal rate)
      : ThreadPeriodicTask(parent, priority, rate)
{
   STANDARD_CONSTRUCTOR()
}

unsigned long TimerThread::userFunc(const LCreal dt)
{
   basic::Timer::updateTimers(dt);
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
      thread = nullptr;
      std::cerr << "createTheThread(): ERROR, failed to create the thread!" << std::endl;
   }

   return thread;
}

// our class factory
static basic::Object* factory(const char* const name)
{
  basic::Object* obj = nullptr;

  if ( std::strcmp(name, Tester::getFactoryName()) == 0 ) {
    obj = new Tester;
  }

  // Default to base classes
  if (obj == nullptr) obj = basic::Factory::createObj(name);
  return obj;
}

// Tester builder
static Tester* builder(const char* const filename)
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
   Tester* tester = dynamic_cast<Tester*>(obj);
   if (tester == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return tester;
}

//------------------------------------------------------------------------------
// run the test
//------------------------------------------------------------------------------
void run(Tester* const tester)
{
   if (tester != nullptr) {
      basic::Timer::freeze(true);

      // Time between printing the timer data
      double dt = 1.0 / static_cast<double>(TIMERS_PRINT_RATE);

      // Our main test control timer
      basic::UpTimer* mainTimer = new basic::UpTimer();
      mainTimer->setAlarmTime(MAIN_TIMER_VALUE);
      mainTimer->start();

      // ---
      // First pass
      // ---
      std::cout << "#### First Test ####" << std::endl;

      basic::Timer::freeze(false);
      while ( !mainTimer->alarm()) {
         lcSleep( static_cast<unsigned int>(dt * 1000.0 + 0.5) );
         std::printf("time(%4.1f)\n", mainTimer->getCurrentTime());
         tester->printTimers();
      }

      // ---
      // Restart the timers
      // ---
      basic::Timer::freeze(true);

      std::cout << std::endl;
      std::cout << "#### Restarting Timers (all active) ####" << std::endl;
      tester->restartAllTimers();
      mainTimer->restart();

      // ---
      // Second pass
      // ---
      std::cout << std::endl;
      std::cout << "#### Second Test ####" << std::endl;

      basic::Timer::freeze(false);
      while ( !mainTimer->alarm()) {
         lcSleep( static_cast<unsigned int>(dt * 1000.0 + 0.5) );
         std::printf("time(%4.1f)\n", mainTimer->getCurrentTime());
         tester->printTimers();
      }
   }
}

//
int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "test01.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build tester
   Tester* tester = builder(configFilename);

   // create the thread
   TimerThread* thread = createTheThread(tester);
   if (thread != nullptr) {

      // run the test
      run(tester);

      tester->event(basic::Component::SHUTDOWN_EVENT);
      tester->unref();
      tester = nullptr;

      // stop the thread
      thread->terminate();
      thread->unref();
      thread = nullptr;
   }

   return 0;
}

} // namespace test
} // namespace oe

//
int main(int argc, char* argv[])
{
   oe::test::main(argc, argv);
}

