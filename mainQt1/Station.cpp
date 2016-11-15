

#include "Station.hpp"

#include "StnTimerObject.hpp"

#include "MainWindow.hpp"

#include <QApplication>
#include <QTimer>

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Station, "QtStation")
EMPTY_SERIALIZER(Station)

EMPTY_CONSTRUCTOR(Station)
EMPTY_COPYDATA(Station)
EMPTY_DELETEDATA(Station)

int Station::createWindow(int argc, char* argv[])
{
   QApplication a(argc, argv);

   // start our background timer, which will call our update data
   timerObj = new StnTimerObject(this);

   // default flags for now
   MainWindow* win = new MainWindow(this);
   win->show();

   return a.exec();
}
