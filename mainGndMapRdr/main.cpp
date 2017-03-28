
#include "TestStation.hpp"
#include "factory.hpp"

#include "openeaagles/terrain/ded/DedFile.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/functors/Tables.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include "openeaagles/graphics/Graphic.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include <GL/glut.h>

#include <string>
#include <cstdlib>

// background rate
const unsigned int bgRate = 20;

// System descriptions
TestStation* testStation = nullptr;

// updateDataCB() -- Station's background tasks
void updateDataCB(int)
{
   const double dt0 = 1.0 / static_cast<double>(bgRate);
   const auto millis = static_cast<unsigned int>(dt0 * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   // current time
   const double time = oe::base::getComputerTime();

   // N-1 Time
   static double time0 = time;

   // compute delta time
   const auto dt = static_cast<double>(time - time0);
   time0 = time;

   oe::base::Timer::updateTimers(dt);
   oe::graphics::Graphic::flashTimer(dt);
   testStation->updateData(dt);
}

// test station builder
TestStation* builder(const std::string& filename)
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
   const auto testStation = dynamic_cast<TestStation*>(obj);
   if (testStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return testStation;
}

//
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

   // default configuration filename
   std::string configFilename = "test.edl";

   // build a test station
   testStation = builder(configFilename);

   // resetting the system will load the data files

   std::cout << "starting loading files --" << std::endl;
   const double start = oe::base::getComputerTime();

   testStation->reset();

   const double end = oe::base::getComputerTime();
   const double dtime = (end - start);
   std::cout << "finished loading files: time(s) = " << dtime << std::endl;

   // set timer for background tasks
   const double dt = 1.0 / static_cast<double>(bgRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   testStation->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}
