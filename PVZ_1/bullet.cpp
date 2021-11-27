#include "bullet.h"
#include "zombie.h"

Bullet::Bullet()
{
    attack = 20;//默认普通豌豆的攻击力
    speed = 100*Refresh_Time/1000;
    clk_counter = speed;
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-12, -28, 24, 24);
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(),  QImage(":/image/Pea.png"));
}

void Snow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(),  QImage(":/image/PeaSnow.png"));
}
bool Bullet::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 10;
}

void Bullet::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    foreach (QGraphicsItem *item, items) {
         if (item->type() == UserType + ZOMBIE) {
             Zombie* zombie = qgraphicsitem_cast<Zombie*>(item);
             zombie->GetHit(attack,slow_down);
             delete this;
             return;
         }
    }
    setX(x() + speed);
    if (x() > 1000)
        delete this;
}

Pea::Pea()
{
    slow_down = 0;

}


Snow::Snow()
{
    slow_down = 1;
}
