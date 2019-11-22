#ifndef PUTONG
#define PUTONG

#include"block.h"

class putong:public block
{
public :
    block*clearBlock();  //单个清除函数
    void show(QPainter &paint);
    void suiji(int i);
};


#endif // PUTONG

