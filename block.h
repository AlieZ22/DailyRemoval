#ifndef BLOCK
#define BLOCK
#include"dailyremoval.h"
#include"guanqia_1.h"
#include<QMainWindow>

//coord表示坐标
class cor{
public:
    int X;
    int Y;

};
class block{
protected:

public:
    int color;//表示该块的状态
    int yidong;//是否可移动
    int pipei;//是否可以匹配
    cor stay;//坐标
    bool isShuangCeng=false;  //判断是否为双层冰块(27),二级被破除后变为false,一级被破除后color变成detail_inIce
    int detail_inIce=100;   //冰块中具体的小动物

    virtual block * clearBlock();//单个块的消除函数，供地图调用
    //virtual void show(QPainter &paint);//显示
   void setxy(int x,int y);
    int getcolor();          //该函数有bug
    //void setcolor(int t);
    virtual void suiji(int i){}
    int suiji();    //随机获得小动物类型
};

#endif // BLOCK

