#include "sun.h"
#include "store.h"
#include "configure.h"
#include <QMovie>
#include <QTime>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QSound>
Sun::Sun()
{
    //自动掉落的太阳
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));//generate a new random number as a seed
    dest = QPointF(290 + qrand() % (Grid_Width * 7), 130 + qrand() % (Grid_Heigt * 5));
    setPos(QPointF(dest.x(), 70));
    speed = 60.0 * 50 / 1000;
    counter = 0;
    time = 10.0 * 1000 / Refresh_Time;
    movie = new QMovie(":/image/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

Sun::Sun(QPointF pos)
{
    //向日葵产生的太阳
    dest = QPointF(pos.x() + qrand() % 30 - 15, pos.y() + qrand() % 30 + 15);
    setPos(QPointF(dest.x(), pos.y()));
    speed = 60 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/image/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

Sun::~Sun()
{
    if (movie)
        delete movie;
}

QRectF Sun::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QSound::play(":/audio/tap.wav");
   QList<QGraphicsItem *> items = scene()->items();
   foreach (QGraphicsItem *item, items) {
        if (item->type() == UserType + STORE) {

        Store* store = qgraphicsitem_cast<Store*>(item);
        store->sun += 25;
        event->setAccepted(true);
        qDebug()<<"got sun";
        break;
        }
   }
   qDebug()<<"delete sun";
   delete  this;
}

void Sun::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (counter >= time)
        delete this;
    else if (y() < dest.y())
        setY(y() + speed);
    else
        ++counter;
}
