
#ifndef __oe_example_MainWindow_H__
#define __oe_example_MainWindow_H__

#include <QMainWindow>
#include "ui_MainWindow.h"

namespace example {

class Station;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
   Q_OBJECT

public:
   MainWindow(Station* stn, QWidget* parent = nullptr);
   ~MainWindow();

   const Station* getStation() const;
   Station* getStation();

public slots:
   // update ourselves
   virtual void refreshWindow();
   virtual void play();
   virtual void pause();
   virtual void ff();
   virtual void reset();

protected:
   virtual void closeEvent(QCloseEvent* event);

private:
   Station* stn;        // holds our station for quick reference
};

inline Station* MainWindow::getStation()              { return stn; }
inline const Station* MainWindow::getStation() const  { return stn; }

}

#endif
