#include "store.h"
#include "configure.h"
#include <QPainter>



Store::Store()
{
    sun = 200;
    setPos(520, 45);

    for (int i = 0; i < Plant_Num; ++i)
    {
        goods[i].setParentItem(this);
        goods[i].setPos(-140 + 60 * i, -20);
    }
    //加载植物卡片
    goods[0].CardSet(PEASHOOTER,100,7.5 * 1000 / Refresh_Time);
    goods[1].CardSet(REPEATER, 200, 7.5 * 1000 / Refresh_Time);
    goods[2].CardSet(SNOWPEA, 175, 7.5 * 1000 / Refresh_Time);
    goods[3].CardSet(WALLNUT, 50, 30 * 1000 / Refresh_Time);
    goods[4].CardSet(TALLNUT, 125, 30 * 1000 / Refresh_Time);
    goods[5].CardSet(SUNFLOWER, 50, 7.5 * 1000 / Refresh_Time);

}

QRectF Store::boundingRect() const
{
    return QRectF(-270, -45, 600, 80);
}

void Store::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-270, -45, 600, 80), QPixmap(":/image/Shop.png"));
    QFont font;
    font.setPointSizeF(20);
    painter->setFont(font);
    painter->drawText(QRectF(-250, 10, 65, 22), Qt::AlignCenter, QString::number(sun));
}

void Store::advance(int phase)
{
    if (!phase)
        return;
    update();

}

int Store::BuyPlant(QString s)
{
    QList<QGraphicsItem *> child = childItems();
    foreach (QGraphicsItem *item, child)
    {
        PlantCard *card = qgraphicsitem_cast<PlantCard *>(item);
        if (card->name == s)
        {
            sun -= card->price;
            card->clk_counter = 0;//进入冷却
            return card->plant_type;
        }
    }
    return -1;
}

