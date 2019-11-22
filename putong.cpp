#include"putong.h"
#include"map.h"
#include<QPainter>
#include<QDebug>
#include<QMovie>


extern Map m;
//单块消除函数
block * putong::clearBlock()
{


        QMovie *movie = new QMovie(":/images/dis.gif");
        m.guanqia->map_tu[stay.X][stay.Y]->setMovie(movie);
        movie->start();

        block * t=new kongkuai;
        t->setxy(stay.X,stay.Y);
        delete this;
        m.guanqia->map_tu[stay.X][stay.Y]->show();
        return t;


//    block * t=new kongkuai;
//    t->setxy(this->stay.X,this->stay.Y);
//    t->color=0;
//    delete this;
//    return t;


}
//显示函数
void putong::show(QPainter &painter)
{
}



void putong::suiji(int i)
{
    color = qrand()%i+1;
}


