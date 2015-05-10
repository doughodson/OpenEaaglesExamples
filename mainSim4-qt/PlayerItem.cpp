#include "PlayerItem.h"
#include "MapItem.h"
#include "openeaagles/simulation/Player.h"

#include <QPainter>
#include <sstream>

namespace Example {

PlayerItem::PlayerItem(MapView* viewer, MapItem* map, QGraphicsItem* parent) : QGraphicsItem(parent)
{
   view = viewer;
   myMap = map;
   plyId = 0;
   defaultImage = nullptr;
}

PlayerItem::~PlayerItem()
{
   myMap = nullptr;
   view = nullptr;
}

// ---
// boundingRect() - returns the bounding rectangle of this PlayerItem
// ---
QRectF PlayerItem::boundingRect() const
{
   return QRectF();
}

// ---
// paint() - draw stuff here
// ---
void PlayerItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
   // get our width and height from our icon
   int w = size.width();
   int h = size.height();
   if (defaultImage != nullptr) {
      painter->drawImage(QRectF(QPointF(-w/2, -h/2), QSizeF(w, h)), *defaultImage);
   }
   else painter->drawEllipse(0, 0, 30, 30);

   // draw the player's name
   QFontMetrics fm = painter->fontMetrics();
   QPen pen(Qt::white, 2.0f);
   QRectF fontRect = fm.boundingRect(name + "X");
   painter->save();

   double hdg = rotation();
   painter->rotate(-hdg);
   if (hdg < 270 && hdg > 90) painter->translate(-fontRect.width()/2, -size.height() + fontRect.height() - 5);
   else painter->translate(-fontRect.width()/2, size.height() + 5);
   QColor sideColor(qRgba(0, 0, 0, 255));
   sideColor.setAlpha(150);
   painter->setBrush(sideColor);
   painter->setPen(pen);
   painter->matrix().mapRect(fontRect);
   painter->drawRoundedRect(fontRect, 5, 5);
   painter->drawText(fontRect, Qt::AlignCenter, name);
   painter->restore();
}

// ---
// useDefaultImage() - passes a string with the relative path of the image file you wish to use
// as the PlayerItem's icon.  It will use this image for it's symbol.
// ---
bool PlayerItem::useDefaultImage(QString fullName, QSize x)
{
   if (defaultImage == nullptr) {
      defaultImage = new QImage(fullName);
      if (defaultImage->isNull()) std::cout << "DEFAULT IMAGE NAME NOT LOADED: " << fullName.toLatin1().data() << std::endl;
   }
   else {
      bool ok = defaultImage->load(fullName);
      if (!ok) std::cout << "DEFAULT IMAGE NAME NOT LOADED: " << fullName.toLatin1().data() << std::endl;
   }

   // set our size to display
   size = x;
   return true;
}

// ---
// setDefaultImageSize() - simply adjusts the size of our image
// ---
bool PlayerItem::setDefaultImageSize(QSize x)
{
   size = x;
   return true;
}

void PlayerItem::refreshPlayer(const Eaagles::Simulation::Player* const ownship)
{
   if (ownship != nullptr) {
      plyId = ownship->getID();
      double oLat = 0.0, oLon = 0.0, tpLat = 0.0, tpLon = 0.0;
      ownship->getPositionLL(&oLat, &oLon);
      if (myMap != nullptr) {
         myMap->llToPixels(oLat, oLon, tpLat, tpLon);
         setPos(tpLon, tpLat);
      }
      setRotation(ownship->getHeadingD());
      // update the player's name
      if (ownship->getName() != nullptr) {
         name = ownship->getName()->getString();
      }
      else {
         std::ostringstream stream;
         stream << plyId;
         name = stream.str().c_str();
      }

   }
   else {
      plyId = 0;
   }
}


}
