#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "configure.h"

class Plant : public QGraphicsItem
{
protected:
    int hp;
    int max_hp;


    int color;

    int hitted;

    QMovie* movie;
    static bool eat_music ;
public:

    int skipable;
    Plant();
    void PlantSetting(int hp);
    enum { Type = UserType + PLANT};
    int type() const override;

    ~Plant() override;

    void setMovie(QString path);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;

    void GetHit(int attack);
};

class PeaShooter:public Plant
{
protected:
    int attack;
    int speed;//发射速度
    int clk_counter;//用来计算时间
public:
    PeaShooter();
    void advance(int phase);
};

class Repeater :public Plant
{
protected:
    int attack;
    int speed;//发射速度
    int clk_counter;//用来计算时间
public:
    Repeater();
    void advance(int phase);
};

class SnowPea :public Plant
{
protected:
    int attack;
    int speed;//发射速度
    int clk_counter;//用来计算时间
public:
    SnowPea();
    void advance(int phase);
};

class WallNut :public Plant
{
protected:

public:
    WallNut();

};

class TallNut :public Plant
{
protected:

public:
    TallNut();

};
class SunFlower :public Plant
{
protected:
    int speed;//产生太阳速度
    int clk_counter;//用来计算时间
public:
    SunFlower();
    void advance(int phase);
};

#endif // PLANT_H
