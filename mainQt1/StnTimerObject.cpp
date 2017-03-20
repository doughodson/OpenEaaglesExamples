
#include "StnTimerObject.hpp"

#include "Station.hpp"
#include "MainWindow.hpp"

#include <QTimer>

StnTimerObject::StnTimerObject(Station* station, QObject* parent) : QObject(parent), stn(station)
{
   if (stn != nullptr) stn->ref();
   // create a timer for our background thread
   bgTimer = new QTimer(this);
   connect(bgTimer, SIGNAL(timeout()), this, SLOT(updateStation()));
   // 20 milliseconds
   bgTimer->start(20);
}

StnTimerObject::~StnTimerObject()
{
   if (stn != nullptr) {
      stn->unref();
      stn = nullptr;
   }
}

void StnTimerObject::updateStation()
{
   if (stn != nullptr) {
      stn->updateData(20.0f/1000.0f);
   }
}

