#include "dailyremoval.h"
#include <QApplication>
#include<QPixmap>
#include<QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置启动画面的图片
    QPixmap pixmap(":/images/res/animation.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    //设置背景


    DailyRemoval w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
