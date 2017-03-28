//------------------------------------------------------------------------------
// Timer test program
//
// 1) Reads an EDL file that must contain our Tester component and timers to be tested.
// 2) Creates a periodic thread to call base::Timer::updateTimers();
// 3) Runs the timers for 'MAIN_TIMER_VALUE' seconds, while printing the timer
//    values at a 'TIMERS_PRINT_RATE' rate
// 4) Restarts all of the Tester's timers
// 5) Runs a second pass
//
//------------------------------------------------------------------------------

#include "Tester.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/concurrent/PeriodicTask.hpp"
#include "openeaagles/base/util/system_utils.hpp"

// class factory
#include "openeaagles/base/factory.hpp"

#include <cstdio>
#include <string>
#include <cstdlib>

const double MAIN_TIMER_VALUE = 10.0; // Sec
const double TIMERS_PRINT_RATE = 5;   // Hz

//------------------------------------------------------------------------------
// Timer thread
//------------------------------------------------------------------------------
const double THREAD_RATE = 20.0;      // hz
const double THREAD_PRI  =  0.5;      // Pri (0 .. 1)

class TimerThread : public oe::base::PeriodicTask
{
   DECLARE_SUBCLASS(TimerThread, oe::base::PeriodicTask)
   public: TimerThread(oe::base::Component* const parent, const double priority, const double rate);
   private: virtual unsigned long userFunc(const double dt) override;
};

IMPLEMENT_SUBCLASS(TimerThread, "TimerThread")
EMPTY_SLOTTABLE(TimerThread)
EMPTY_COPYDATA(TimerThread)
EMPTY_DELETEDATA(TimerThread)
EMPTY_SERIALIZER(TimerThread)

TimerThread::TimerThread(oe::base::Component* const parent, const double priority, const double rate)
      : PeriodicTask(parent, priority, rate)
{
   STANDARD_CONSTRUCTOR()
}

unsigned long TimerThread::userFunc(const double dt)
{
   oe::base::Timer::updateTimers(dt);
   return 0;
}

//------------------------------------------------------------------------------
// createTheThread() -- Create the data acq thread
//------------------------------------------------------------------------------
TimerThread* createTheThread(Tester* const tester)
{
   auto thread = new TimerThread(tester, THREAD_PRI, THREAD_RATE);

   bool ok = thread->create();
   if (!ok) {
      thread = nullptr;
      std::cerr << "createTheThread(): ERROR, failed to create the thread!" << std::endl;
   }

   return thread;
}

// class factory
oe::base::Object* factory(const std::string& name)
{
  oe::base::Object* obj = nullptr;

  if ( name == Tester::getFactoryName() ) {
    obj = new Tester;
  }

  // Default to base classes
  if (obj == nullptr) obj = oe::base::factory(name);
  return obj;
}

// Tester builder
Tester* builder(const std::string& filename)
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
   const auto tester = dynamic_cast<Tester*>(obj);
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
      oe::base::Timer::freeze(true);

      // Time between printing the timer data
      double dt = 1.0 / static_cast<double>(TIMERS_PRINT_RATE);

      // Our main test control timer
      const auto mainTimer = new oe::base::UpTimer();
      mainTimer->setAlarmTime(MAIN_TIMER_VALUE);
      mainTimer->start();

      // ---
      // First pass
      // ---
      std::cout << "#### First Test ####" << std::endl;

      oe::base::Timer::freeze(false);
      while ( !mainTimer->alarm()) {
         oe::base::msleep( static_cast<unsigned int>(dt * 1000.0 + 0.5) );
         std::printf("time(%4.1f)\n", mainTimer->getCurrentTime());
         tester->printTimers();
      }

      // ---
      // Restart the timers
      // ---
      oe::base::Timer::freeze(true);

      std::cout << std::endl;
      std::cout << "#### Restarting Timers (all active) ####" << std::endl;
      tester->restartAllTimers();
      mainTimer->restart();

      // ---
      // Second pass
      // ---
      std::cout << std::endl;
      std::cout << "#### Second Test ####" << std::endl;

      oe::base::Timer::freeze(false);
      while ( !mainTimer->alarm()) {
         oe::base::msleep( static_cast<unsigned int>(dt * 1000.0 + 0.5) );
         std::printf("time(%4.1f)\n", mainTimer->getCurrentTime());
         tester->printTimers();
      }
   }
}

//
int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "test01.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
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

      tester->event(oe::base::Component::SHUTDOWN_EVENT);
      tester->unref();
      tester = nullptr;

      // stop the thread
      thread->terminate();
      thread->unref();
      thread = nullptr;
   }

   return 0;
}
