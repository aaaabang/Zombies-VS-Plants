#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <QTimer>
#include <QGraphicsView>
#include <QMediaPlayer>
#include "configure.h"
#include "gamescene.h"

class MainView;
class GameScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    GameScene *scene;
    MainView *view;

    const int width,height;
};


class MainView : public QGraphicsView
{
    Q_OBJECT

public:
    MainView(MainWindow *parent = nullptr);

};
#endif // MAINWINDOW_H
