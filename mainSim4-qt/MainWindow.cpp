
#include "MainWindow.h"
#include "Station.h"
#include "openeaagles/simulation/Simulation.h"

#include <QTimer>
#include <sstream>

namespace Example {

MainWindow::MainWindow(Station* station, QWidget* parent) :QMainWindow(parent)
{
   stn = station;
   if (stn != nullptr) stn->ref();
   setupUi(this);
   // Only use this if you want to refresh the top level window... which
   // usually doesn't draw dynamically.  If you do use this, make it not
   // update that quickly to avoid performance hits with your viewer.
   QTimer* bgTimer = new QTimer(this);
   connect(bgTimer, SIGNAL(timeout()), this, SLOT(refreshWindow()));
   // not very of
   bgTimer->start(2);
}

MainWindow::~MainWindow()
{
   if (stn != nullptr) {
      stn->unref();
      stn = nullptr;
   }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
   // tell our station to shutdown
   if (stn != nullptr && !stn->isShutdown()) {
       stn->event(Eaagles::Basic::Component::SHUTDOWN_EVENT);
   }
   QMainWindow::closeEvent(event);
}

// update our simulation status
void MainWindow::refreshWindow()
{
   if (stn != nullptr) {
      // get the simulation
      if (stn->isFrozen()) simStatus->setText("PAUSE");
      else {
         int ffRate = stn->getFastForwardRate();
         if (ffRate == 1) simStatus->setText("PLAY");
         else {
            std::ostringstream stream;
            stream << ffRate;
            QString status = ("FF ");
            status.append(stream.str().c_str());
            status.append("x");
            simStatus->setText(status);
         }
      }
   }
}

void MainWindow::play()
{
   // get the simulation and play it!
   if (stn != nullptr) {
      Eaagles::Simulation::Simulation* sim = stn->getSimulation();
      if (sim != nullptr) {
         if (stn->getFastForwardRate() != 1) stn->setFastForwardRate(1);
         if (stn->isFrozen()) stn->freeze(false);
         if (sim->isFrozen()) sim->freeze(false);
      }
   }
}
void MainWindow::pause()
{
   if (stn != nullptr) {
      Eaagles::Simulation::Simulation* sim = stn->getSimulation();
      if (sim != nullptr) {
         if (stn->isNotFrozen()) stn->freeze(true);
         if (sim->isNotFrozen()) sim->freeze(true);
      }
   }
}

void MainWindow::ff()
{
   if (stn != nullptr) {
      Eaagles::Simulation::Simulation* sim = stn->getSimulation();
      if (sim != nullptr) {
         if (stn->isFrozen()) stn->freeze(false);
         if (sim->isFrozen()) sim->freeze(false);
         int ffRate = stn->getFastForwardRate();
         // FF rate is 1, 3, 5, and 9
         if (ffRate < 9) ffRate += 2;
         else ffRate = 3;
         stn->setFastForwardRate(ffRate);
      }
   }
}

void MainWindow::reset()
{
   // also freeze and set the FF rate to 1
   if (stn != nullptr) {
      Eaagles::Simulation::Simulation* sim = stn->getSimulation();
      if (sim != nullptr) {
         if (stn->getFastForwardRate() != 1) stn->setFastForwardRate(1);
         if (stn->isNotFrozen()) stn->freeze(true);
         if (sim->isNotFrozen()) sim->freeze(true);
         stn->event(Eaagles::Basic::Component::RESET_EVENT);
      }
   }
}

}
