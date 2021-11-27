#include "plantcard.h"
#include "store.h"
#include <QPainter>
#include <QFont>
#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QApplication>
#include <QtWidgets>
#include <QMimeData>
#include <QSound>
PlantCard::PlantCard()
{

}

void PlantCard::CardSet(int _type, int _price, int _cd)
{
    plant_type = _type;
    price = _price;
    cd = _cd;
    clk_counter = 0;
    name = TypetoName(plant_type);
}

QRectF PlantCard::boundingRect() const
{
    return QRectF(-50, -30, 95, 100);
}

void PlantCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->scale(0.6, 0.7);//收缩图片
    painter->drawImage(boundingRect(), QImage(":/image/Card.png"));//卡片
    painter->drawImage(QRect(-35, -20, 70, 70), QImage(":/image/" + name + ".png"));//植物

    QFont font;
    font.setPointSizeF(23);
    painter->setFont(font);
    painter->drawText(QRectF(-40, 48, 70, 20), Qt::AlignCenter, QString::number(price));//价格
    if (clk_counter < cd)
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-49, -30, 98, 100 * (1 - double(clk_counter) / cd)));
    }

    Store *store = qgraphicsitem_cast<Store *>(parentItem());
    if (price > store->sun)
    {
        QBrush brush(QColor(59, 59, 59, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-49, -30, 98, 100 ));
    }

}

void PlantCard::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (clk_counter < cd)
        ++clk_counter;
}

void PlantCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QSound::play(":/audio/bleep.wav");
    event->setAccepted(true);
    if (clk_counter < cd)
        event->setAccepted(false);
    Store *store = qgraphicsitem_cast<Store *>(parentItem());
    if (price > store->sun)
        event->setAccepted(false);
}

void PlantCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
            < QApplication::startDragDistance())//防误触
        return;

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/image/" + name + ".png");
    mime->setText(name);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));//设置拖拽时的植物图片
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();

}

void PlantCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}

QString PlantCard::TypetoName(int type)
{
    QString name = "";
    switch (type)
    {
    case PEASHOOTER:
        name = "Peashooter";
        break;
    case REPEATER:
        name = "Repeater";
        break;
    case SNOWPEA:
        name = "SnowPea";
        break;
    case WALLNUT:
        name = "WallNut";
        break;
    case TALLNUT:
        name = "TallNut";
        break;
    case SUNFLOWER:
        name = "SunFlower";
        break;
//	case SQUASH:
//		name = "窝瓜";
//		break;
//	case CHERRYBOMB:
//		name = "樱桃炸弹";
//		break;
//	case GARLIC:
//		name = "大蒜";
//		break;
    default:
        break;
    }
    return name;
}
