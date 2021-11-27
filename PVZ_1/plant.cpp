#include "plant.h"
#include "bullet.h"
#include "zombie.h"
#include "sun.h"
#include<QSound>
Plant::Plant()
{
    movie = nullptr;
    skipable = 1;
    color = 15;
    hitted = 0;
}
bool Plant::eat_music = 0;
Plant::~Plant()
{
    delete movie;
}
void Plant::PlantSetting(int _hp)
{
    hp = _hp;
    max_hp = hp;
}

QRectF Plant::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y());
}

int Plant::type() const
{
    return Type;
}

void Plant::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}
void Plant::advance(int phase)
{
    if (!phase)
        return;
    if (hp <= 0)
        delete this;
}

void Plant::GetHit(int attack)
{
    static int eat_clk = 1*1000/Refresh_Time;
    static int eat_time = 1*1000/Refresh_Time;
    hp -= attack;
    if(Plant::eat_music == 0 && eat_clk >= eat_time)
    {
        eat_music = 1;
        eat_clk = 0;
        QSound::play(":/audio/chompsoft.wav");
        eat_music = 0;
    }
    else
    {
        ++eat_clk;
    }
}

PeaShooter::PeaShooter()
{
    PlantSetting(300);
    attack = 20;//一颗豌豆的威力
    speed = 14*100/Refresh_Time;//每1400ms发射一颗豌豆
    clk_counter = speed;

    setMovie(":/image/Peashooter.gif");
}

void PeaShooter::advance(int phase)
{
    if (!phase)
        return;

    update();

    if (!collidingItems().isEmpty())
    {
        if(clk_counter >= speed)
        {
            clk_counter = 0;
            Pea* pea = new Pea;
            pea->setX(x() + 32);
            pea->setY(y());
            scene()->addItem(pea);
          //  update();
            return;
        }
        else
            ++clk_counter;
    }
    Plant::advance(phase);

}

SnowPea::SnowPea()
{
    PlantSetting(300);
    attack = 20;//一颗豌豆的威力
    speed = 14*100/Refresh_Time;//每1400ms发射一颗寒冰豌豆
    clk_counter = speed;

    setMovie(":/image/SnowPea.gif");
}
void SnowPea::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else
    {
        if (!collidingItems().isEmpty())
        {
            if(clk_counter >= speed)
            {
                clk_counter = 0;
                Snow* pea = new Snow;
                pea->setX(x() + 32);
                pea->setY(y());
                scene()->addItem(pea);
                return;
            }
            else
                ++clk_counter;
        }
    }

}
Repeater::Repeater()
{
    PlantSetting(300);
    attack = 20;//一颗豌豆的威力
    speed = 14*100/Refresh_Time;//每1400ms发射两颗豌豆
    clk_counter = speed;

    setMovie(":/image/Repeater.gif");
}
void Repeater::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else
    {
        if (!collidingItems().isEmpty())
        {
            if(clk_counter >= speed)
            {
                clk_counter = 0;
                Pea* pea1 = new Pea;
                Pea* pea2 = new Pea;
                pea1->setX(x() + 28);
                pea1->setY(y());
                pea2->setX(x() + 40);
                pea2->setY(y());
                scene()->addItem(pea1);
                scene()->addItem(pea2);
                //update();
                return;
            }
            else
                clk_counter++;
        }
    }

}

WallNut::WallNut()
{
    PlantSetting(4000);
    setMovie(":/image/WallNut.gif");
}

TallNut::TallNut()
{
    PlantSetting(4000);
    setMovie(":/image/Tallnut2.gif");
    skipable = 0;
}

SunFlower::SunFlower()
{
    PlantSetting(300);
    speed = 24*1000/Refresh_Time;//每24000ms产生一个太阳
    clk_counter = 12*1000/Refresh_Time;//每24000ms产生一个太阳;
    setMovie(":/image/SunFlower.gif");
}

void SunFlower::advance(int phase)
{
    if (!phase)
        return;

    update();
    if(hp <= 0)
    {
        delete this;
        return;
    }
    if(clk_counter >= speed)
    {
        clk_counter = 0;
        Sun* sun = new Sun(this->pos());
        scene()->addItem(sun);
    }
    else
        ++clk_counter;

}
