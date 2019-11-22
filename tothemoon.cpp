#define WIDTH_MAP 10
#define HEIGTH_MAP 10
#include<tothemoon.h>
#include<qpainter.h>
#include <QPixmap>
#include<QDebug>
#include<QDialog>
#include "block.h"
#include"map.h"

extern Map m;

void tothemoon::show(QPainter &paint)//显示
{
    QPixmap pix;

    pix.load(":/images/res/xuekuai.png");
    //pix=splitpixmap(pix,6,16,1);

    paint.drawPixmap(KUAI_a*stay.X,KUAI_a*stay.Y+50,KUAI_a,KUAI_a,pix);
}

block* tothemoon::clear(int i,int j)
{
    if((i>=0)&&(i<=WIDTH_MAP)&&(j>=0)&&(j<=HEIGTH_MAP)&&(m.map[i][j]->color!=-1))
    {
        m.map[i][j]=m.map[i][j]->clearBlock();
        return m.map[i][j];
    }
}


tothemoon::tothemoon()
{
    this->yidong=1;
}

block * tothemoon::clearBlock()
{
    block * t=new kongkuai;
    t->setxy(this->stay.X,this->stay.Y);
    int i=this->stay.X;
    int j=this->stay.Y;
    delete this;
    m.map[i][j]=t;



    if(this->color>=7&&this->color<=12)
    {
        clear(i,j+1);
        clear(i,j-1);
        clear(i,j+2);
        clear(i,j-2);
        clear(i+1,j);
        clear(i-1,j);
        clear(i+2,j);
        clear(i-2,j);
        clear(i+1,j+1);
        clear(i-1,j-1);
        clear(i+1,j-1);
        clear(i-1,j+1);

    }
    else if(this->color>=13&&this->color<=18)
    {
        for(int m=0;m<WIDTH_MAP;m++)
        {
            clear(m,j);
        }

    }
    else if(this->color>=19&&this->color<=24)
    {
        for(int m=0;m<HEIGTH_MAP;m++)
        {
            clear(i,m);
        }

    }
    else if(this->color==25)
    {
        for(int m=0;m<WIDTH_MAP;m++)
        {
            for(int n=0;n<HEIGTH_MAP;n++)
            {
                clear(m,n);
            }
        }

    }
    return t;

}






void tothemoon::setxy(int x,int y)
{
    stay.X=x;stay.Y=y;
}
