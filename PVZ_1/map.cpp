#include "map.h"
#include "store.h"
#include"plant.h"
#include<QPainter>
#include<QEvent>
#include<QMimeData>
#include<QGraphicsSceneDragDropEvent>
#include<QGraphicsScene>
#include<QDebug>
#include <QSound>
Map::Map()
{
    setAcceptDrops(true);
}

QRectF Map::boundingRect() const
{
    return QRectF(250, 80, 738, 500);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
   // painter->setPen(Qt::black);
   // painter->drawRect(boundingRect());
}

void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
        update();
    }
    else
        event->setAccepted(false);
}

void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    update();
}

void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QSound::play(":/audio/plant2.wav");
    QString s = event->mimeData()->text();
    QPointF pos = mapToScene(event->pos());
    pos.setX((int(pos.x()) - 249) / 82 * 82 + 290);
    pos.setY((int(pos.y()) - 81) / 98 * 98 + 130);

    int plant_type = -1;

    QList<QGraphicsItem *> items = scene()->items();
    foreach (QGraphicsItem *item, items) {
         if (item->type() == UserType + STORE) {
            Store* store = qgraphicsitem_cast<Store*>(item);
            //获取当前植物种类
            plant_type = store->BuyPlant(s);
            break;
         }
    }
    Plant* plant;
    TypetoPlant(plant_type,plant);
    // 种植
    scene()->addItem(plant);
    plant->setPos(pos);

}

void Map::TypetoPlant(int type, Plant *&plant)
{
    plant = nullptr;
    switch (type)
    {
    case PEASHOOTER:
        plant = new PeaShooter();
        break;
    case SNOWPEA:
        plant = new SnowPea();
        break;
    case REPEATER:
        plant = new Repeater();
        break;
    case WALLNUT:
        plant = new WallNut();
        break;
    case TALLNUT:
        plant = new TallNut();
        break;
    case SUNFLOWER:
        plant = new SunFlower();
        break;

//    case SQUASH:
//        plant = new Squash();
//        break;
//    case CHERRYBOMB:
//        plant = new CherryBomb();
//        break;
//    case GARLIC:
//        plant = new Garlic();
//        break;
    default:
        break;
    }
    return;
}
