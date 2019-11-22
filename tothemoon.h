#ifndef TOTHEMOON
#define TOTHEMOON




#include<block.h>
class tothemoon:public block
{
public:
    tothemoon();
    block * clearBlock();//单个块的消除函数，供地图调用
    block *clear(int i,int j);
    void show(QPainter &paint);//显示
    void setxy(int x,int y);
    //int getcolor();
};

#endif // TOTHEMOON

