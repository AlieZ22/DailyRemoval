#ifndef GUANQIA_1_H
#define GUANQIA_1_H
#define WIDTH_MAP 10      //要改为10
#define HEIGTH_MAP 10
#include <QWidget>
#include<QLabel>
#include"main.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>

/**
 *小试牛刀：完成15次简单消除
 */

namespace Ui {
class guanqia_1;
}

class guanqia_1 : public QWidget
{
    Q_OBJECT

public:

     int num_frog=0;     //记录消除青蛙的个数（第一关通关条件）
     int iceremind=8;        //记录消除冰块的个数（第二关通关条件）
     int grades=0;          //记录当前分数（第三关通关条件）
    explicit guanqia_1(QWidget *parent = 0,int guanQia=1);       //默认是第一关，可以通过构造函数来指定生成第几关的地图
    ~guanqia_1();

    int flag=0;
    QLabel* map_tu[WIDTH_MAP][HEIGTH_MAP];


    void setlable();

    void success();

private:
    Ui::guanqia_1 *ui;

    int guanNum;
    QMediaPlayer *myPlayer;
    QMediaPlaylist *myPlayList;





private slots:
    void paintEvent(QPaintEvent*event);
    void mousePressEvent(QMouseEvent*event);

    void onReturnButton();
};

#endif // GUANQIA_1_H
