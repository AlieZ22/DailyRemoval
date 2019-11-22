#ifndef KONGKUAI
#define KONGKUAI

#include"block.h"

class kongkuai:public block
{
public :
    kongkuai()
    {
        color=0;
    }

    block *clearBlock();     //单块消除函数
    void show(QPainter &paint);   //显示
    //int getcolor();
};


#endif // KONGKUAI

