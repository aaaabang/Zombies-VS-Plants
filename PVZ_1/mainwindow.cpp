#include "mainwindow.h"
#include "map.h"
#include "zombie.h"
#include "map.h"
#include "store.h"
#include <QTime>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : width(920), height(606),
      QMainWindow(parent)

{
    //场景设置
    scene = new GameScene(this);

    //播放背景音乐
    scene->PlayBgm();

    //添加商店
    Store* store = new Store();
    scene->addItem(store);

    Map* map = new Map();
    scene->addItem(map);
    //连接视图和场景
    view = new MainView(this);

    //执行游戏逻辑
    scene->GameLoop();

    //打印视图
    view->show();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete view;
}

MainView::MainView(MainWindow *parent)
{
    setParent(parent);//让视图显示在窗口内

    setScene(parent->scene);//视图添加场景

    //一些视图初始化设置
    resize(parent->width,parent->height);
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QPixmap(":/image/Background.jpg"));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}



