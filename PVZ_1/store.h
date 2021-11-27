#ifndef STORE_H
#define STORE_H

#include <QGraphicsItem>
#include "configure.h"
#include "plantcard.h"

#define Plant_Num 6

class PlantCard;
class Store : public QGraphicsItem
{
protected:

    int sun_refresh_time = 10;
    int clk;

    int sum_x, sum_y;//阳光数SUM光标位置
    int st_x, st_y;//PLANTCARD开始处光标位置

    int num_X1, num_X2;
    int num_Y;
    int sel_x, sel_y;//当前选中框所在商品坐标

    PlantCard goods[Plant_Num];
    int state;//是否处于购买状态


public:
    int sun;//当前阳光数

    Store();
    ~Store(){}

    enum { Type = UserType + STORE};
    int type() const override{return Type;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

    int BuyPlant(QString s);

//    int Shopping();
//    void SunRise();
    //bool Pay(PlantCard& p);
};

#endif // STORE_H
