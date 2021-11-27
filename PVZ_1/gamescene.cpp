#include "gamescene.h"
#include "configure.h"
#include "zombie.h"
#include "sun.h"
#include <QTime>
#include <QDebug>
#include<QtGlobal>

GameScene::GameScene(QObject *parent)
{
    setParent(parent);
    setSceneRect(150, 0, SCENE_WIDTH, SCENE_HEIGHT);
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

GameScene::~GameScene()
{
    delete backgroundMusic;
    delete timer;
}

void GameScene::PlayBgm()
{
    //背景音乐设置
    backgroundMusic = new QMediaPlayer(this);
    backgroundMusic->blockSignals(false);
    backgroundMusic->setMedia(QUrl("qrc:/audio/Grazy Dave.mp3"));
    backgroundMusic->play();
}

void GameScene::GameLoop()
{
    //游戏核心逻辑
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &GameScene::advance);
    connect(timer, &QTimer::timeout, this, &GameScene::AddZombie);
    connect(timer, &QTimer::timeout, this, &GameScene::GenSun);
    connect(timer, &QTimer::timeout, this, &GameScene::IfLose);

    timer->start(Refresh_Time);//refresh every 33msec
}

void GameScene::AddZombie()
{
    //每10秒生成一个僵尸
    static int time = 10 * 1000 / Refresh_Time;
    static int counter = 0;
    if (++counter >= time)
    {
        qsrand(QTime::currentTime().msec()*qrand()*qrand()*qrand()*qrand());//generate a new random number as a seed
        counter = 0;
        int type = 0;//qrand()%2;
        int i = qrand() % 5;
        Zombie *zombie;
        switch (type)
            {
            case NORMAL_ZOMBIE:
                zombie = new Zombie();
                break;
//            case POLE_ZOMBIE:
//                zombie = new Pole_Zombie();
//                break;
//            case CONEHEAD_ZOMBIE:
//                zombie = new Conehead_Zombie();
//                break;
//            case NEWSPAPER_ZOMBIE:
//                zombie = new Newspaper_Zombie;
//                break;

//            case BOX_ZOMBIE:
//                zombie = new Box_Zombie();
//                break;
//            case CATAPULT_ZOMBIE:
//                zombie = new Catapult_Zombie();
//                break;
            default:
                zombie = nullptr;
                break;
            }
        if(zombie != nullptr)
        {
        qDebug()<<"zombie yes";
        zombie->setPos(1000, 130+98*i);
        this->addItem(zombie);
        }
    }
}

void GameScene::GenSun()
{
    //每8秒生成一个太阳
    static int time = 8 * 1000 / Refresh_Time;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        Sun* drop_sun = new Sun;
        addItem(drop_sun);
    }

}

void GameScene::IfLose()
{
    //1秒检查一次结果
    static int time = 1 * 1000 / Refresh_Time;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = this->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Zombie::Type && item->x() < 50)
            {
                qDebug()<<"all done";
                QSound::play(":/audio/losemusic.wav");
                addPixmap(QPixmap(":/image/ZombiesWon.png"))->setPos(336, 92);
                advance();
                timer->stop();
                return;
            }
    }
}
