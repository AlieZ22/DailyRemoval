#include"block.h"

#include<QtGlobal>
#include<QTime>

//单个块的消除，供地图使用
block * block ::clearBlock()
{
    return this;
}


void block::setxy(int x, int y)
{
    stay.X=x;  stay.Y=y;
}
int block::getcolor()
{
    return 0;         //返回color会报错
}
//void block::setcolor(int c)
//{
//    color=c;
//}


int block::suiji()
{
    int num = qrand()%6+1;
    return num;
}
