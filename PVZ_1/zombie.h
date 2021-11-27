#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "configure.h"


class Zombie : public QGraphicsItem
{
public:
    int hp;
    int atk;
    int state;
    double speed;
    int clk;
    int ice_on;//冷冻效果
    int ice_cd;
    int ice_clk;

    QMovie *movie;
    QMovie *head;

    enum { Type = UserType + ZOMBIE};
    int type() const override;

    Zombie();
    ~Zombie() override;
    void setMovie(QString path);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;

    virtual bool GetHit(int attack,int slow_down);
};

//撑杆僵尸
class Pole_Zombie : public Zombie
{
protected:
    int pole;
public:
    Pole_Zombie();
    void advance(int phase) override;
};

#endif // ZOOMBIE_H
