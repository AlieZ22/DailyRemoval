#include "dailyremoval.h"
#include "ui_dailyremoval.h"
#include"m_widget.h"
#include<windows.h>
#include<QMessageBox>

int DailyRemoval::musicFlag=0;

DailyRemoval::DailyRemoval(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DailyRemoval)
{
    ui->setupUi(this);

    setWindowTitle("天天消消乐");

    //信号与槽的连接
    connect(ui->quitButton,SIGNAL(clicked()),this,SLOT(onQuitButton()));
    connect(ui->playButton,SIGNAL(clicked()),this,SLOT(onPlayButton()));
    connect(ui->instructionButton,SIGNAL(clicked()),this,SLOT(onInstructionButton()));
            //两个播放音乐的按钮（不同状态）连接同一个槽，但每个时刻只有一个按钮被显示
    connect(ui->musicPlayButton,SIGNAL(clicked()),this,SLOT(onMusicPlayButton()));
    connect(ui->musicPlayButton_2,SIGNAL(clicked()),this,SLOT(onMusicPlayButton()));
            //play页面返回时，接收重新播放音乐的返回信号
    //connect(&m_widget,SIGNAL(returned()),this,SLOT(onMusicPlayButton()));


    //设置一进界面就播放音乐
    ui->musicPlayButton_2->setVisible(false);      //刚开始隐藏静音状态
    myPlayer = new QMediaPlayer(this);
    myPlayList = new QMediaPlaylist(this);
    //设置单曲循环
    myPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    myPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/startmusic.mp3"));
    //为播放器myPlayer设置歌单
    myPlayer->setPlaylist(myPlayList);
    //播放音乐
    myPlayer->play();

    resize(600,770);
    Sleep(1500);
}

//按下Play按钮
void DailyRemoval::onPlayButton()
{
    //按钮被新界面覆盖，按钮不可见且无法使用了，所以先关掉原音乐按钮
    onMusicPlayButton();

    //设置按键音效
    tempPlayer=new QMediaPlayer(this);
    tempPlayList=new QMediaPlaylist(this);
    tempPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    tempPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/pressed.mp3"));
    tempPlayer->setPlaylist(tempPlayList);
    tempPlayer->play();

    //进入游戏界面
    myWidget = new m_widget(this);
    myWidget->show();
}

//按下Instruction按钮
void DailyRemoval::onInstructionButton()
{
    //播放按键音效
    tempPlayer=new QMediaPlayer(this);
    tempPlayList=new QMediaPlaylist(this);
    tempPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    tempPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/pressed.mp3"));
    tempPlayer->setPlaylist(tempPlayList);
    tempPlayer->play();
    //跳转到游戏规则的介绍
    myInstruction = new m_instruction(this);
    myInstruction->show();
}

//按下Quit按钮
void DailyRemoval::onQuitButton()
{
    //播放按键音效
    tempPlayer=new QMediaPlayer(this);
    tempPlayList=new QMediaPlaylist(this);
    tempPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    tempPlayList->addMedia(QUrl::fromLocalFile("D:/Program/Qt/DailyRemoval/pressed.mp3"));
    tempPlayer->setPlaylist(tempPlayList);
    tempPlayer->play();

    //定义QMessageBox,默认为模态对话框
   int flag = QMessageBox::warning(this,"提示","系统即将退出",QMessageBox::Ok,QMessageBox::No);
   //如果按下OK按钮则退出程序
   if(flag==QMessageBox::Ok)
   {
       close();
   }
}

//按下音乐播放的按钮（因为默认是一进程序就打开音乐，所以开始显示的按钮为关）
void DailyRemoval::onMusicPlayButton()
{
    musicFlag+=1;    //记录该槽被触发的次数，%2获得状态
    //musicFlag为单数时，之前为正在播放音乐，之后要停止播放，并将按钮改成静音状态
    if(musicFlag%2)
    {
        myPlayer->stop();
        ui->musicPlayButton->setVisible(false);      //播放状态隐藏
        ui->musicPlayButton_2->setVisible(true);     //静音状态显示
    }
    //musicFlag为偶数时，之前没有播放音乐，之后要开始播放，并将按钮改成正在播放状态
    else
    {
        myPlayer->play();
        ui->musicPlayButton->setVisible(true);      //播放状态显示
        ui->musicPlayButton_2->setVisible(false);     //静音状态隐藏
    }

}


DailyRemoval::~DailyRemoval()
{
    delete ui;
}

