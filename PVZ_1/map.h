#ifndef MAP_H
#define MAP_H

#include "plant.h"
#include <QGraphicsItem>


class Map : public QGraphicsItem
{
protected:
    void TypetoPlant(int type, Plant *&plant);
public:
    Map();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

};

#endif // MAP_H
