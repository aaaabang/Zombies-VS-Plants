#ifndef SUN_H
#define SUN_H

#include <QGraphicsItem>
#include "configure.h"
class Sun : public QGraphicsItem
{
private:
    QMovie *movie;
    QPointF dest;
    int counter;
    int time;
    double speed;


public:
    Sun();
    Sun(QPointF pos);
    ~Sun();
    enum { Type = UserType + SUN};
    int type() const override{return Type;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
};

#endif // SUN_H
