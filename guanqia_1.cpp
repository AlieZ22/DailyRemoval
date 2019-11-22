#include "guanqia_1.h"
#include "ui_guanqia_1.h"
#include"m_widget.h"
#include<QFileDialog>
#include<QDebug>
#include<QMessageBox>
#include<QMainWindow>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QPainter>
#include<QTimer>
#include<QFont>
#include<math.h>
#include<windows.h>
#include"map.h"


guanqia_1::guanqia_1(QWidget *parent,int guanQia) :
    QWidget(parent),
    ui(new Ui::guanqia_1)
{
    //更新ui，覆盖之前的界面
    ui->setupUi(this);

    guanNum=guanQia;

    connect(ui->returnButton,SIGNAL(clicked()),this,SLOT(onReturnButton()));

    qDebug()<<"进入关卡一的构造函数";

    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
            map_tu[i][j]=new QLabel(this);

    //播放音乐
    myPlayer = new QMediaPlayer(this);
    myPlayList = new QMediaPlaylist(this);
    //设置单曲循环
    myPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    //为不同关配置不同音乐
    switch(guanNum)
    {
    case 1: case 4: case 7: case 9:
        myPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/guan_one.mp3"));
        break;
    case 2:case 5:case 8:
        myPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/guan_two.mp3"));
        break;
    case 3:case 6:
        myPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/guan_three.mp3"));
        break;
    }

    //为播放器myPlayer设置歌单
    myPlayer->setPlaylist(myPlayList);
    //播放音乐
    myPlayer->play();



    QFont myFont("Arial",12,75);          //设置字体
    ui->goalLabel->setFont(myFont);
    ui->showLabel->setFont(myFont);
    //为不同关卡匹配不同通关条件的说明
    switch(guanNum)
    {
    case 1:
        ui->goalLabel->setText("小试牛刀：消除15个青蛙");
        ui->showLabel->setText("个数：");
        break;
    case 2:
        ui->goalLabel->setText("初试冰层：消除8个冰层");
        ui->showLabel->setText("剩余：");
        break;
    case 3:
        ui->goalLabel->setText("分数达人：达到1000分");
        ui->showLabel->setText("分数：");
        break;
    }


}

guanqia_1::~guanqia_1()
{
    delete ui;
}
extern Map m;

//重写绘图函数
void guanqia_1::paintEvent(QPaintEvent *event)
{
    int ice_num=0;
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
            if(m.map[i][j]->color==27)
            {
                ice_num++;
            }
    iceremind=ice_num;


    //为不同关卡匹配过关判据
    switch(guanNum)
    {
    case 1:
        ui->timesLabel->setText(QString::number(num_frog));
        break;
    case 2:
        ui->timesLabel->setText(QString::number(iceremind));
        break;
    case 3:
        ui->timesLabel->setText(QString::number(grades));
        break;
    }



    m.guanqia=this;
    setFixedSize(600,800);
    QPainter painter(this);

    if(flag==0){
        //为不同关卡加载不同地图
        switch(guanNum)
        {
        case 1:
            m.loadmap("D:/Program/Qt/DailyRemoval/res/1.txt");
            break;
        case 2:
            m.loadmap("D:/Program/Qt/DailyRemoval/res/2.txt");
            break;
        case 3:
            m.loadmap("D:/Program/Qt/DailyRemoval/res/3.txt");
            break;
        }

        setlable();
        flag=1;
    }
    m.show(painter);
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
            map_tu[i][j]->show();
}

void guanqia_1::mousePressEvent(QMouseEvent *event)
{
    //不是交换状态
    if(m.jiaohuan==0)
    {
            int i=event->pos().rx()/KUAI_a,j=(event->pos().ry()-50)/KUAI_a;
            this->update();

            if(m.cor1.X!=-1)
            {
                m.cor2.X=i;m.cor2.Y=j;
                //相邻交换
                if((m.cor2.X==m.cor1.X&&(abs(m.cor2.Y-m.cor1.Y)==1))
                        ||(m.cor2.Y==m.cor1.Y&&(abs(m.cor2.X-m.cor1.X)==1)))
                {
                    setlable();
                    m.swap(m.cor1.X,m.cor1.Y,m.cor2.X,m.cor2.Y,map_tu);

                    if(m.jianche()==0)
                    {
                        m.houzhi_swap();
                    }
                    else
                    {
                        m.jiance_xiaochu_tianchong();
                    }


                }
                //非相邻交换
                else
                    m.cor1=m.cor2;

             m.cor1.X==-1;
            }

            else{
                m.cor1.X=i;m.cor1.Y=j;
            }
        }
    //不同关卡配置不同过关条件
    switch(guanNum)
    {
    case 1:
        if(num_frog>=15)
        {
            success();
        }
        break;
    case 2:
        if(iceremind==0)
        {
            success();
        }
        break;
    case 3:
        if(grades>=1000)
        {
            success();
        }

    }

}

void guanqia_1::success()
{
    //跳出恭喜过关弹窗
    QDialog *dialog;
    dialog = new QDialog(this);
    dialog->setWindowTitle("Congratulation");
    QLabel label(dialog);
    QFont font;
    font.setPointSize(13);
    label.setFont(font);
    label.setText("\n恭喜你，完成任务!");
    dialog->setModal(true);
    dialog->resize(250,77);
    dialog->show();
    dialog->exec();

    //结束音乐播放
    myPlayer->stop();

    //开启第二关
    m_widget::currentBarrier++;
    //关闭当前窗口
    this->close();
    qDebug()<<"完成";
}

void guanqia_1::setlable()
{
    for(int i=0;i<WIDTH_MAP;i++)
        for(int j=0;j<HEIGTH_MAP;j++)
        {
            map_tu[i][j]->move(i*KUAI_a,j*KUAI_a+50);
            QPixmap pix;
            int t=m.map[i][j]->color;
            //qDebug()<<"color"<<t;
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
                pix.load(":/images/res/chic1");
                break;
            case 7:
                pix.load(":/images/res/bear2.png");
                break;
            case 8:
                pix.load(":/images/res/fox2.png");
                break;
            case 9:
                pix.load(":/images/res/Eagel2.png");
                break;
            case 10:
                pix.load(":/images/res/frog2.png");
                break;
            case 11:
                pix.load(":/images/res/hippo2.png");
                break;
            case 12:
                pix.load(":/images/res/chic2.png");
                break;
            case 13:case 19:
                pix.load(":/images/res/bear3.png");
                break;
            case 14:case 20:
                pix.load(":/images/res/fox3.png");
                break;
            case 15:case 21:
                pix.load(":/images/res/Eagel3.png");
                break;
            case 16:case 22:
                pix.load(":/images/res/frog3.png");
                break;
            case 17:case 23:
                pix.load(":/images/res/hippo3.png");
                break;
            case 18:case 24:
                pix.load(":/images/res/chic3.png");
                break;
            case 25:
                pix.load(":/images/res/maotouying.png");
                break;
            case 27:
                qDebug()<<"detail_inIce:"<<m.map[i][j]->detail_inIce;
                switch(m.map[i][j]->detail_inIce)
                {
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
                    pix.load(":/images/res/dongwu");//鸡的截图还没有
                    pix=splitpixmap(pix,0,368,100,100);
                    break;
                }

                break;
            default:
                break;
            }
            map_tu[i][j]->setScaledContents(true);
            map_tu[i][j]->setPixmap(pix);
            map_tu[i][j]->resize(KUAI_a,KUAI_a);

        }
}


void guanqia_1::onReturnButton()
{
    int flag;

    flag=QMessageBox::warning(this,"提示","确定要返回吗？",QMessageBox::No,QMessageBox::Ok);
    if (flag==QMessageBox::Ok)
    {
        //结束音乐播放
        myPlayer->stop();
        this->close();
    }

}
