
#ifndef __MapItem_H__
#define __MapItem_H__

#include <QGraphicsItem>

class MapView;

class MapItem: public QGraphicsItem
{
public:
   MapItem(MapView* v, QGraphicsItem* parent = nullptr);
   ~MapItem();

   // initialize using given ref lat / lon range
   virtual void initialize(const double lat, const double lon, const double range);
   bool isInit() const;

   // background call (from the graphics thread)
   virtual void updateBG();

   // based on the pixel location with the center being CENTER of the screen,
   // we compute the earth miles in north, east coordinates
   virtual void pixelsToLL(const double px, const double py, double& lon, double& lat) const;
   virtual void llToPixels(const double lat, const double lon, double& py, double& px) const;

   // should be called from the top level view when a resize occurs
   virtual void setSize(const int w, const int h);

   // set heading
   virtual void setHeading(const double x);

   // positional information
   virtual bool setRefLat(const double x);
   virtual bool setRefLon(const double x);
   virtual bool setRange(const double x);
   double getRefLat() const;
   double getRefLon() const;
   double getRange() const;

   // optional additional drawing information
   virtual bool setGridVis(const bool x);
   bool isGridOn() const;
   virtual bool setNorthUp(const bool x);
   bool isNorthUp() const;

   double getCosRefLat() const;

   // Qt required classes
   QRectF boundingRect() const;
   virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

protected:
   // move the map around some delta N, delta E
   virtual void moveMap(const double deltaN, const double deltaE);

   // draw a lat/lon grid
   void drawGrid(QPainter* painter);

   // get our resolutions
   double getNSPixelRes() const;
   double getWEPixelRes() const;

   // Qt interface
   virtual void wheelEvent(QGraphicsSceneWheelEvent* event);
   virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
   QRectF getBoundingRect() const;

private:
   // bounding rect, will show how much to draw, and determines our width and height
   QRectF bRect;

   // reference lat/lon
   double refLat {};
   double refLon {};
   // range (NM)
   double range {500.0};

   // pixel resolutions (nautical miles)
   double pixNSRes {1.0};
   double pixWERes {1.0};

   // grid visibility
   bool gridVis {};

   // cosine of our reference latitude
   double cosineLatReference {1.0};
   // heading (rad)
   double heading {};
   // cosine of heading
   double headingCos {};
   // sine of heading
   double headingSin {};
   // flag to use north/up or track/up map math
   bool northUp {true};

   // Our view
   MapView* view {};
   bool init {};        // our we initialized
};

// inline functions
inline double MapItem::getRefLat() const                 { return refLat; }
inline double MapItem::getRefLon() const                 { return refLon; }
inline double MapItem::getRange() const                  { return range; }
inline QRectF MapItem::getBoundingRect() const           { return bRect; }
inline bool MapItem::setGridVis(const bool x)            { gridVis = x; return true; }
inline bool MapItem::isGridOn() const                    { return gridVis; }
inline double MapItem::getCosRefLat() const              { return cosineLatReference; }
inline bool MapItem::setNorthUp(const bool x)            { northUp = x; return true; }
inline bool MapItem::isNorthUp() const                   { return northUp; }
inline double MapItem::getNSPixelRes() const             { return pixNSRes; }
inline double MapItem::getWEPixelRes() const             { return pixWERes; }
inline bool MapItem::isInit() const                      { return init; }

#endif
