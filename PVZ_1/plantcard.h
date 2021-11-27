#ifndef PLANTCARD_H
#define PLANTCARD_H

#include "configure.h"
#include <QGraphicsItem>
#include <QString>


class PlantCard : public QGraphicsItem
{
protected:
    int plant_type;
    int price;
    int cd;

    int clk_counter;

    int refresh;
    int selected;

    QString name;

    QString TypetoName(int type);
public:
    PlantCard();
    void CardSet(int type,int _price,int _cd);

    enum { Type = UserType + PLANTCARD};
    int type() const override{return Type;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    friend class Store;
};

#endif // PLANTCARD_H
