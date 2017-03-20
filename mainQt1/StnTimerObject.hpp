
#ifndef __StnTimerObject_H__
#define __StnTimerObject_H__

#include <QObject>

class QTimer;
class Station;

//------------------------------------------------------------
// Class: StnTimerObject
// Description: helper object for background station tasks
//------------------------------------------------------------
class StnTimerObject : public QObject
{
   Q_OBJECT

public:
   StnTimerObject(Station* station, QObject* parent = nullptr);
   ~StnTimerObject();

public slots:
   virtual void updateStation();

private:
   Station* stn {};
   QTimer* bgTimer {};
};

#endif
