
#ifndef __oe_example_MapView_H__
#define __oe_example_MapView_H__

#include <QGraphicsView>

namespace example {

class Station;
class MapItem;
class PlayerItem;

class MapView : public QGraphicsView
{
   Q_OBJECT

public:
   MapView(QWidget* parent = nullptr);
   ~MapView();

public slots:
   // refresh our view graphics
   virtual void refreshView();

protected:
   virtual void resizeEvent(QResizeEvent* event);

private:
   void clearPlayers();
   Station* stn;                 // holds a station for reference
   MapItem* map;                 // our map
   QList<PlayerItem*> players;   // our "graphical" players
};

}

#endif
