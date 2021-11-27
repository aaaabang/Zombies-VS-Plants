#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "configure.h"

class Bullet : public QGraphicsItem
{
public:
    Bullet();
    ~Bullet(){}
    enum { Type = UserType + BULLET};
    int type() const override{return Type;}
    QRectF boundingRect() const override;
   // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override ;
protected:
    int attack;	//攻击力
    int slow_down;//减缓僵尸速度
    int clk_counter;
    int speed;
};
class Pea:public Bullet
{
public:
    Pea();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class Snow :public Bullet
{
public:
    Snow();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // BULLET_H
