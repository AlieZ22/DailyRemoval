#include"map.h"
#include<QPixmap>
#include<QFile>
#include<fstream>
#include<QRect>
#include<QDebug>
#include<QPainter>
#include<string.h>
#include <iostream>
#include <QTimerEvent>
#include <QPropertyAnimation>
#include"guanqia_1.h"
#include<QtWidgets>

Map m;
//展示地图
void Map::show(QPainter &painter)
{
    QPixmap pix,pix_bing1,pix_bing2;
    pix.load(":/images/res/beijingkuai.png");      //加载背景块图片
    pix_bing1.load(":/images/res/bing1.png");    //一级冰块层
    pix_bing2.load(":/images/res/bing2.png");    //二级冰块层
    //qDebug()<<"地图展示";
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
            //如果是普通而非冰块
            if(map[i][j]->color!=-1&&map[i][j]->color!=27)
                painter.drawPixmap(KUAI_a*i,KUAI_a*j+50,KUAI_a,KUAI_a,pix);
            else if(map[i][j]->color==27)
                //color属性为20则为冰块
                {
                    painter.drawPixmap(KUAI_a*i,KUAI_a*j+50,KUAI_a,KUAI_a,pix);
                    //进一步判断是否为双层冰块
                    if(map[i][j]->isShuangCeng)
                    {
                        painter.drawPixmap(KUAI_a*i,KUAI_a*j+50,KUAI_a,KUAI_a,pix_bing2);
                    }
                    else
                    {
                        painter.drawPixmap(KUAI_a*i,KUAI_a*j+50,KUAI_a,KUAI_a,pix_bing1);
                    }
                 }
}

//构造函数
Map::Map()
{
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
        {
                map[i][j]= new putong;
                map[i][j]->setxy(i,j);
        }
    cor1.X=cor1.Y=cor2.X=cor2.Y=-1;
    jiaohuan=0;
    m_pTimer = new QTimer;
    QObject::connect(m_pTimer,SIGNAL(timeout()),this,SLOT(handleTimeout()));

}

//保存地图
void Map::savemap(const char *str)
{

}

//载入地图
void Map::loadmap(const char *str)
{
    //QString displayString;
    QFile file(str);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
         qDebug()<<"Can't open the file!";
    }
    QTextStream stream(&file);

    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
        {
            int t;
            stream>>t;
            if(t>0&&t<7)
            {
                map[i][j]=new putong;
                map[i][j]->setxy(i,j);
                map[i][j]->color=(t);
                //qDebug()<<"t:"<<t;
            }
            //加载时创建冰块(因为冰块是地图初始化时产生的)
            if(t==27)
            {
                map[i][j] = new putong;
                map[i][j] ->setxy(i,j);
                map[i][j] ->color=(t);
                //随机产生冰块中小动物类型
                map[i][j]->detail_inIce=map[i][j]->suiji();                //
                qDebug()<<"t(冰块):"<<t;
            }
            if(t==0)
            {
                map[i][j]=new kongkuai;
                map[i][j]->setxy(i,j);
            }
        }
}


//void Map::cal(int x,int y,int &i,int &j);//根据鼠标点击位置计算出地图块的二维编号地址
int Map::tianchong(QLabel* l[WIDTH_MAP][HEIGTH_MAP])      //填充
{
    qDebug()<<"填充函数";
    guanqia->setlable();
    int flag=0;
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=HEIGTH_MAP-1;j>0;j--)
            {
                if(map[i][j]->color==0||map[i][j]->detail_inIce==0)
                {
                    qDebug()<<"color 0 填补";
                    if(1)
                    {
                        this->yidong(i,j,i,j-1,l);
                        swap_xy(i,j,i,j-1);
                        flag=1;
                    }
                }
            }
    for(int i=0;i<WIDTH_MAP;i++)
            if(map[i][0]->color==0||map[i][0]->detail_inIce==0)
            {
                flag=1;
                delete map[i][0];
                map[i][0]=new putong;
                map[i][0]->suiji(6);
                map[i][0]->setxy(i,0);



                QPixmap pix;
                int t=m.map[i][0]->color;
                switch (t) {
                case 1:
                    pix.load(":/images/res/bear.png");
                    break;
                case 2:
                    pix.load(":/images/res/fox.png");
                    break;
                case 3:
                    pix.load(":/images/res/Eagel.png");
                    break;
                case 4:
                    pix.load(":/images/res/frog.png");
                    break;
                case 5:
                    pix.load(":/images/res/hippo.png");
                    break;
                case 6:
                    pix.load(":/images/res/chic1.png");
                    break;
                }
                QLabel *ll=new QLabel(guanqia);
                v.push_back(ll);
                ll->setScaledContents(true);
                ll->setPixmap(pix);
                ll->resize(KUAI_a,KUAI_a);
                ll->show();
                QPropertyAnimation *animation = new QPropertyAnimation(ll,"geometry");

                animation->setDuration(xialuoshijian);

                animation->setStartValue(QRect(i*KUAI_a, -KUAI_a+50, KUAI_a, KUAI_a));

                animation->setEndValue(QRect(i*KUAI_a, 50, KUAI_a, KUAI_a));


                QTimer *timer = new QTimer(this);
                QObject::connect(timer, SIGNAL(timeout()), this, SLOT(shanchu_duoyu()));
                timer->setSingleShot(true);
                timer->start(xialuoshijian);

                animation->start();

            }




            if(flag==1)//如果填充了就在动画结束时重置数据
            {
                qDebug()<<"填充结束";
                m.jiaohuan=1;
                m_pTimer->start(xialuoshijian);
                m_pTimer->setSingleShot(true);
            }
            return flag;

}

QPixmap splitpixmap(QPixmap pix, int x, int y, int w, int h)
{
    QPixmap pix2;
    pix2 = pix.copy(x,y,w,h);
    return pix2;
}


void Map::yidong(int x1,int y1,int x2, int y2,QLabel* l[WIDTH_MAP][HEIGTH_MAP])
{
    qDebug()<<"移动函数";

    //创建动画
    QPropertyAnimation *animation = new
              QPropertyAnimation(l[x2][y2],"geometry");

    animation->setDuration(xialuoshijian-150);

    animation->setStartValue(QRect(x2*KUAI_a, y2*KUAI_a+50, KUAI_a, KUAI_a));

    animation->setEndValue(QRect(x1*KUAI_a, y1*KUAI_a+50, KUAI_a, KUAI_a));

    animation->start();


}

void Map::swap(int x1,int y1,int x2, int y2,QLabel* l[WIDTH_MAP][HEIGTH_MAP])
{
    qDebug()<<"交换函数";

    block *t;//交换属性
    if(map[x1][y1]->color!=27&&map[x2][y2]->color!=27)
    {
        t=map[x1][y1];
        map[x1][y1]=map[x2][y2];
        map[x2][y2]=t;
    }

    //如果为冰块那么不能改变其color属性
    else
    {
        int temp;
        if(map[x1][y1]->color==27)
        {
            temp=map[x1][y1]->detail_inIce;
            //交换块类型
            map[x1][y1]->detail_inIce=map[x2][y2]->color;
            map[x2][y2]->color=temp;
        }
        else if(map[x2][y2]->color==27)
        {
            temp=map[x2][y2]->detail_inIce;
            //交换块类型
            map[x2][y2]->detail_inIce=map[x1][y1]->color;
            map[x1][y1]->color=temp;
        }
        else if(map[x1][y2]->color==27&&map[x2][y2]->color==27)
        {
            temp=map[x1][y1]->detail_inIce;
            map[x1][y1]->detail_inIce=map[x2][y2]->detail_inIce;
            map[x2][y2]->detail_inIce=temp;
        }
    }
    //交换位置
    cor t2;
    t2=(map[x1][y1]->stay);
    map[x1][y1]->stay=map[x2][y2]->stay;
    map[x2][y2]->stay=t2;


    QPropertyAnimation *animation = new
              QPropertyAnimation(l[x1][y1],"geometry");

    animation->setDuration(jiaohuan_shijian);

    animation->setStartValue(QRect(x1*KUAI_a, y1*KUAI_a+50, KUAI_a, KUAI_a));

    animation->setEndValue(QRect(x2*KUAI_a, y2*KUAI_a+50, KUAI_a, KUAI_a));

    animation->start();


    QPropertyAnimation *animation2 = new
              QPropertyAnimation(l[x2][y2],"geometry");

    animation2->setDuration(jiaohuan_shijian);

    animation2->setStartValue(QRect(x2*KUAI_a, y2*KUAI_a+50, KUAI_a, KUAI_a));

    animation2->setEndValue(QRect(x1*KUAI_a, y1*KUAI_a+50, KUAI_a, KUAI_a));

    animation2->start();

}

void Map::swap_xy(int x1, int y1, int x2, int y2)
{
    //只交换属性，不创建动画
    block *t;//交换属性
    if(map[x1][y1]->color!=27&&map[x2][y2]->color!=27)
    {
        t=map[x1][y1];
        map[x1][y1]=map[x2][y2];
        map[x2][y2]=t;
    }
    //如果为冰块那么不能改变其color属性
    else
    {
        int temp;
        if(map[x1][y1]->color==27)
        {
            temp=map[x1][y1]->detail_inIce;
            //交换块类型
            map[x1][y1]->detail_inIce=map[x2][y2]->color;
            map[x2][y2]->color=temp;
        }
        else if(map[x2][y2]->color==27)
        {
            temp=map[x2][y2]->detail_inIce;
            //交换块类型
            map[x2][y2]->detail_inIce=map[x1][y1]->color;
            map[x1][y1]->color=temp;
        }
        else if(map[x1][y2]->color==27&&map[x2][y2]->color==27)
        {
            temp=map[x1][y1]->detail_inIce;
            map[x1][y1]->detail_inIce=map[x2][y2]->detail_inIce;
            map[x2][y2]->detail_inIce=temp;
        }
    }

    //交换位置
    cor t2;
    t2=(map[x1][y1]->stay);
    map[x1][y1]->stay=map[x2][y2]->stay;
    map[x2][y2]->stay=t2;
}

int Map::jianche()//检测(拼音有问题)
{
    qDebug()<<"检测函数";
    int flag=0;
    memset(xiaochu,0,sizeof xiaochu);      //将消除数组全部置0
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
        {
            if(map[i][j]->color<=0||xiaochu[i][j]!=0||map[i][j]->color==25)
                continue;
            //判断第i，j块是否被消掉
            int x_lianji=0,y_lianji=0;
            //横坐标连击数检测
            for(int k=i;k<i+5&&k<WIDTH_MAP;k++)
            {
                if(map[i][j]->color==27)
                {
                    //如果含冰层
                    if(map[k][j]->color==27)
                    {
                        if(map[k][j]->detail_inIce%6==map[i][j]->detail_inIce%6)
                            x_lianji++;
                        else
                            break;
                    }
                    else{
                        if(map[k][j]->color%6==map[i][j]->detail_inIce%6)
                            x_lianji++;
                        else
                            break;
                    }
                }
                else
                {
                    //如果含冰层
                    if(map[k][j]->color==27)
                    {
                        if(map[k][j]->detail_inIce%6==map[i][j]->color%6)
                            x_lianji++;
                        else
                            break;
                    }
                    else{
                        if(map[k][j]->color%6==map[i][j]->color%6)
                            x_lianji++;
                        else
                            break;
                    }
                }
            }
            //通过横坐标连击数，分情况为消除数组赋值
            if(x_lianji==3){
                flag=1;
                for(int k=i;k<i+3&&k<WIDTH_MAP;k++)
                {
                    if(map[i][j]->color==27)
                    {
                        //冰层情况检测
                        if(map[k][j]->color==27)
                        {
                            if(map[k][j]->detail_inIce%6==map[i][j]->detail_inIce%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[k][j]->color%6==map[i][j]->detail_inIce%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                    }
                    else
                    {
                        //冰层情况检测
                        if(map[k][j]->color==27)
                        {
                            if(map[k][j]->detail_inIce%6==map[i][j]->color%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[k][j]->color%6==map[i][j]->color%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                    }

                }
            }
            else if(x_lianji==4)
            {
                flag=1;
                for(int k=i;k<i+4&&k<WIDTH_MAP;k++)
                {
                    if(map[i][j]->color==27)
                    {
                        //冰层情况检测
                        if(map[k][j]->color==27)
                        {
                            if(map[k][j]->detail_inIce%6==map[i][j]->detail_inIce%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[k][j]->color%6==map[i][j]->detail_inIce%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                    }
                    else
                    {
                        //冰层情况检测
                        if(map[k][j]->color==27)
                        {
                            if(map[k][j]->detail_inIce%6==map[i][j]->color%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[k][j]->color%6==map[i][j]->color%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                    }

                }
                xiaochu[i+2][j]=1000;       //四个消除的中间块
            }
            else if(x_lianji==5)
            {
                flag=1;
                for(int k=i;k<i+5&&k<WIDTH_MAP;k++)
                {
                    if(map[i][j]->color==27)
                    {
                        //冰层情况检测
                        if(map[k][j]->color==27)
                        {
                            if(map[k][j]->detail_inIce%6==map[i][j]->detail_inIce%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[k][j]->color%6==map[i][j]->detail_inIce%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                    }
                    else
                    {
                        //冰层情况检测
                        if(map[k][j]->color==27)
                        {
                            if(map[k][j]->detail_inIce%6==map[i][j]->color%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[k][j]->color%6==map[i][j]->color%6)
                                xiaochu[k][j]++;
                            else
                                break;
                        }
                    }

                }


                xiaochu[i+2][j]=100;
            }


            //纵坐标连击数检测
            for(int k=j;k<j+5&&k<WIDTH_MAP;k++)
            {
                if(map[i][j]->color==27)
                {
                    //如果含冰层
                    if(map[i][k]->color==27)
                    {
                        if(map[i][k]->detail_inIce%6==map[i][j]->detail_inIce%6)
                            y_lianji++;
                        else
                            break;
                    }
                    else{
                        if(map[i][k]->color%6==map[i][j]->detail_inIce%6)
                            y_lianji++;
                        else
                            break;
                    }
                }
                else{
                    //如果含冰层
                    if(map[i][k]->color==27)
                    {
                        if(map[i][k]->detail_inIce%6==map[i][j]->color%6)
                            y_lianji++;
                        else
                            break;
                    }
                    else{
                        if(map[i][k]->color%6==map[i][j]->color%6)
                            y_lianji++;
                        else
                            break;
                    }
                }

            }
            //通过纵坐标连击数，分情况为消除数组赋值
            if(y_lianji==3)
            {
                flag=1;
                for(int k=j;k<j+3&&k<WIDTH_MAP;k++)
                {
                    if(map[i][j]->color==27)
                    {
                        if(map[i][k]->color==27)
                        {
                            if(map[i][k]->detail_inIce%6==map[i][j]->detail_inIce%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[i][k]->color%6==map[i][j]->detail_inIce%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                    }
                    else
                    {
                        if(map[i][k]->color==27)
                        {
                            if(map[i][k]->detail_inIce%6==map[i][j]->color%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[i][k]->color%6==map[i][j]->color%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                    }

                }
            }
            else if(y_lianji==4)
            {
                flag=1;
                for(int k=j;k<j+4&&k<WIDTH_MAP;k++)
                {
                    if(map[i][j]->color==27)
                    {
                        if(map[i][k]->color==27)
                        {
                            if(map[i][k]->detail_inIce%6==map[i][j]->detail_inIce%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[i][k]->color%6==map[i][j]->detail_inIce%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                    }
                    else
                    {
                        if(map[i][k]->color==27)
                        {
                            if(map[i][k]->detail_inIce%6==map[i][j]->color%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[i][k]->color%6==map[i][j]->color%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                    }

                }
                xiaochu[i][j+2]=2000;
            }
            else if(y_lianji==5)
            {
                flag=1;
                for(int k=j;k<j+5&&k<WIDTH_MAP;k++)
                {
                    if(map[i][j]->color==27)
                    {
                        if(map[i][k]->color==27)
                        {
                            if(map[i][k]->detail_inIce%6==map[i][j]->detail_inIce%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[i][k]->color%6==map[i][j]->detail_inIce%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                    }
                    else
                    {
                        if(map[i][k]->color==27)
                        {
                            if(map[i][k]->detail_inIce%6==map[i][j]->color%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                        else
                        {
                            if(map[i][k]->color%6==map[i][j]->color%6)
                                xiaochu[i][k]++;
                            else
                                break;
                        }
                    }

                }
                xiaochu[i][j+2]=200;
            }
            //消除函数
            //特效块赋值
        }
    qDebug()<<"检测函数的返回值："<<flag;
    return flag;
}

void Map::xianchu(QLabel* l[WIDTH_MAP][HEIGTH_MAP])
{
    qDebug()<<"消除函数";
    guanqia->setlable();
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
        {

            if(xiaochu[i][j]!=0)
            {
                //冰层的消除（注意：并不会引起小动物消除个数的改变，所以不用加）
                if(map[i][j]->color==27)
                {
                    if(map[i][j]->isShuangCeng)
                    {       //双层冰则降为单层冰
                        qDebug()<<"双层冰将为单层";
                        map[i][j]->isShuangCeng=false;
                        map[i][j]->color=27;
                        xiaochu[i][j]=0;
                    }
                    else
                    {        //单层冰则破除
                        qDebug()<<"单层冰破除";
                        map[i][j]->color=map[i][j]->detail_inIce;
                        map[i][j]->detail_inIce=100;   //化为默认值
                        xiaochu[i][j]=0;


                    }
                }

                //消除函数后的特效
                switch (xiaochu[i][j])
                {
                case 1:         //三个简单消除
                   // qDebug()<<"消除case 1";
                    countFrog(i,j);     //记录第一关消除的青蛙数
                    map[i][j]=map[i][j]->clearBlock();//调用消除函数
                    guanqia->grades+=10;
                    break;
                case 100:case 101:case 200:case 201:
                    //qDebug()<<"消除case 100,101,200,201";
                    countFrog(i,j);
                    map[i][j]=map[i][j]->clearBlock();//调用消除函数
                    delete map[i][j];
                    map[i][j]=new tothemoon;
                    map[i][j]->color=25;
                    map[i][j]->setxy(i,j);
                    guanqia->grades+=60;
                    break;
                case 2:case 1001:case 2001:
                    //qDebug()<<"消除case 2,1001,2001";
                    int k;
                    k=map[i][j]->color;
                    countFrog(i,j);
                    map[i][j]=map[i][j]->clearBlock();//调用消除函数
                    delete map[i][j];
                    map[i][j]=new tothemoon;
                    map[i][j]->color=k+6;
                    map[i][j]->setxy(i,j);
                    guanqia->grades+=30;
                    break;
                case 1000:
                    //qDebug()<<"消除case 1000";
                    int kk;
                    kk=map[i][j]->color;
                    countFrog(i,j);
                    map[i][j]=map[i][j]->clearBlock();//调用消除函数
                    delete map[i][j];
                    map[i][j]=new tothemoon;
                    map[i][j]->color=kk+12;
                    map[i][j]->setxy(i,j);
                    guanqia->grades+=30;
                    break;
                case 2000:
                    //qDebug()<<"消除case 2000";
                    int kkk;
                    kkk=map[i][j]->color;
                    countFrog(i,j);
                    map[i][j]=map[i][j]->clearBlock();//调用消除函数
                    delete map[i][j];
                    map[i][j]=new tothemoon;
                    map[i][j]->color=kkk+18;
                    map[i][j]->setxy(i,j);
                    guanqia->grades+=30;
                    break;
                default:
                    break;
                }
            }
        }


}

void Map::handleTimeout()
{
    m.jiaohuan=0;     //交换完成
    //交换数据
    guanqia->setlable();    //图片匹配
    if(m.tianchong(guanqia->map_tu))//是否还可交换
        {
            m.jiaohuan=1;//继续交换
        }
        else
        {
            if(jianche())
            {
                //消除与填充之间的时间槽函数
                xiaochu_tianchong();
            }
        }
}

//后置交换函数
void Map::houzhi_swap()
{
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(swap_houzhi()));
    timer->setSingleShot(true);
    timer->start(jiaohuan_shijian);
}
//后置交换槽函数
void Map::swap_houzhi()
{
    guanqia->setlable();
    swap(cor1.X,cor1.Y,cor2.X,cor2.Y,guanqia->map_tu);
    cor1.X=-1;//重置
}

void Map::jiance_xiaochu_tianchong()
{

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(diaoyong_sanweiyiti()));
    timer->setSingleShot(true);
    timer->start(jiaohuan_shijian+300);
}

void Map::diaoyong_sanweiyiti()
{
    guanqia->setlable();
    if(m.jianche()){
        xiaochu_tianchong();
    }
}
void Map::xiaochu_tianchong()//二位一体
{

    xianchu(guanqia->map_tu);
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tianchong_slot()));
    timer->setSingleShot(true);
    timer->start(xiaochu_shijian);

}

void Map::tianchong_slot()//二位一体
{
    guanqia->setlable();

    tianchong(guanqia->map_tu);

}


void Map::shanchu_duoyu()
{
    for(int i=0;i<v.size();i++)
        delete v[i];
    v.clear();
}



void Map::countFrog(int x,int y)
{
    if(map[x][y]->color==4)
    {
        guanqia->num_frog++;
    }
}

