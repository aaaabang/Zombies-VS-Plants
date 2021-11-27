#include "zombie.h"
#include "configure.h"
#include "plant.h"
#include "timer.h"
#include <QDebug>
#include <QSound>
#include <QTimer>
Zombie::Zombie()
{
    movie = head = nullptr;

    hp = 270;
    atk = 100 * Refresh_Time / 1000;//以刷新时间为单位的伤害力
    speed = 80.0 * Refresh_Time / 1000 / 4.7;
    state = ZombieWalk;

    setMovie(":/image/ZombieWalk1.gif");
}

Zombie::~Zombie()
{
    delete movie;
    delete head;
}

QRectF Zombie::boundingRect() const
{
    return QRectF(-80, -100, 200, 140);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image = movie->currentImage();
    painter->drawImage(boundingRect(), image);
}

bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30;
}


int Zombie::type() const
{
    return Type;
}

void Zombie::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}

void Zombie::advance(int phase)
{
    if (!phase)
        return;

    update();//it schedules a paint request that is processed by QGraphicsView after control reaches the event loop.
    if (state == ZombieDead)
    {
       delete this;
        return;
    }

    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        foreach (QGraphicsItem *item, items)
        {
            if (item->type() == UserType + PLANT)
            {

                Plant *plant = qgraphicsitem_cast<Plant *>(item);
                plant->GetHit(atk);
                if (state != ZombieEat)
                {
                    state = ZombieEat;
                    setMovie(":/image/ZombieAttack.gif");
                }
            }
        }
        return;
    }

    if (state == ZombieEat)
    {
        state = ZombieWalk;
        setMovie(":/image/ZombieWalk1.gif");

    }

    setX(x() - speed);

    //看是否需要解冻
    if (ice_on == 1)
    {
        if (ice_clk >= ice_cd)
        {
            ice_clk = 0;
            ice_cd = 0;
            ice_on = 0;
            speed *= 2;
            atk *= 2;
        }
        else
        {
            ice_clk++;
        }
    }
    //qDebug()<<x();
}


/*僵尸被打到了鸭*/
bool  Zombie::GetHit(int attack, int slow_down) {
    hp -= attack;
    QSound::play(":/audio/splat1.wav");
//    switch (qrand() % 3) {
//        case 0: QSound::play(":/audio/splat1.wav"); break;
//        case 1: QSound::play(":/audio/splat2.wav"); break;
//        default: QSound::play(":/audio/splat3.wav"); break;
//    }

    if (slow_down == 1 && ice_on == 0)
    {
        //僵尸被冻，速度减半，10s后解冻
        speed /= 2;
        atk /= 2;
        ice_on = 1;
        ice_cd = 100*1000/Refresh_Time;
        ice_clk = 0;
    }

    if (hp <= 0 )
    {
        state = ZombieDead;
        return false;//僵尸死掉了
    }
    else
    {
        return true;//还活着
    }
}

Pole_Zombie::Pole_Zombie()
{
    hp = 500;
    //max_hp = 500;
    speed = 80.0 * Refresh_Time / 1000 / 2.5;
    pole = 1;
    setMovie(":/image/PoleVaultingZombie.gif");
}

void Pole_Zombie::advance(int phase)
{
    if (!phase)
        return;
    update();//it schedules a paint request that is processed by QGraphicsView after control reaches the event loop.
    if (state == ZombieDead)
    {
       delete this;
        return;
    }

    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        foreach (QGraphicsItem *item, items)
        {
            if (item->type() == UserType + PLANT)
            {

                Plant *plant = qgraphicsitem_cast<Plant *>(item);
                if (pole == 1)
                {
                    pole = 0;
                    setMovie(":/image/PoleVaultingZombieJump.gif");

                    qDebug()<<"jump";
                    if (plant->skipable == 0) {
                        //不能跳过
                        plant->GetHit(atk);
                        if (state != ZombieEat)
                        {
                            state = ZombieEat;
                            setMovie(":/image/ZombieAttack.gif");
                        }
                    }
                    else
                    {
                        qDebug()<<"jump over";
                        setX(x()-70);
                        setMovie(":/image/PoleVaultingZombieJump2.gif");

                        setX(x()-20);
                        setMovie(":/image/PoleVaultingZombieWalk.gif");
                        speed = 80.0 * Refresh_Time / 1000 / 4.5;
                    }


                ;
                }
                else
                {
                    plant->GetHit(atk);
                    if (state != ZombieEat)
                    {
                        state = ZombieEat;
                        setMovie(":/image/PoleVaultingZombieAttack.gif");
                    }
                }
            }
        }
        return;
    }

    if (state == ZombieEat)
    {
        state = ZombieWalk;
        setMovie(":/image/PoleVaultingZombieWalk.gif");
    }

    setX(x() - speed);

    //看是否需要解冻
    if (ice_on == 1)
    {
        if (ice_clk >= ice_cd)
        {
            ice_clk = 0;
            ice_cd = 0;
            ice_on = 0;
            speed *= 2;
            atk *= 2;
        }
        else
        {
            ice_clk++;
        }
    }



}

