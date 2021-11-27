#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "mainwindow.h"
#include <QGraphicsScene>


class GameScene : public QGraphicsScene
{
protected:
    QMediaPlayer *backgroundMusic;
    QTimer *timer;

    void AddZombie();
    void GenSun();
    void IfLose();
public:

    explicit GameScene(QObject *parent = nullptr);
    ~GameScene();

    void PlayBgm();
    void GameLoop();


};

#endif // GAMESCENE_H
