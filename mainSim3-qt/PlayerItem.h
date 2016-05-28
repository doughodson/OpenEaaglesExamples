
#ifndef __PlayerItem_H__
#define __PlayerItem_H__

#include <QGraphicsItem>

namespace  oe {
   namespace simulation { class Player; }
}

class MapView;
class MapItem;

class PlayerItem : public QGraphicsItem
{
public:
   PlayerItem(MapView* viewer, MapItem* map = nullptr, QGraphicsItem* parent = nullptr);
   ~PlayerItem();

   // update function
   virtual void refreshPlayer(const oe::simulation::Player* const ownship);

   // we can tell our PlayerItem to use a specific image file to draw
   virtual unsigned short getPlayerId() const;
   virtual bool useDefaultImage(QString fullName, QSize x);
   virtual bool setDefaultImageSize(QSize x);

   // Qt interface function
   QRectF boundingRect() const;
   void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
   unsigned short plyId;                         // ID of the player we are representing
   MapItem* myMap;
   MapView* view;

   QImage* defaultImage;                        // this will be our default image (if we define one)
   QSize size;                                  // our default icon size
   QString name;                                // player's name
};

inline unsigned short PlayerItem::getPlayerId() const      { return plyId; }

#endif
