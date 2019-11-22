#include "m_widget.h"
#include "ui_m_widget.h"
#include "map.h"

#include<QMessageBox>

extern Map m;

int m_widget::currentBarrier=3;

m_widget::m_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::m_widget)
{
    ui->setupUi(this);
    //之前进入这个界面时，停止了父界面的音乐播放，所以返回时应该再重新播放
    //关卡的页面跳转
    connect(ui->guan1,SIGNAL(clicked()),this,SLOT(onGuan1Button()));
    connect(ui->guan2,SIGNAL(clicked()),this,SLOT(onGuan2Button()));
    connect(ui->guan3,SIGNAL(clicked()),this,SLOT(onGuan3Button()));
    connect(ui->guan4,SIGNAL(clicked()),this,SLOT(onGuan4Button()));
}


m_widget::~m_widget()
{
    delete ui;
}

void m_widget::on_returnButton_clicked()
{
    //关闭当前窗口，返回到父窗口界面
    this->close();
}

//进入第一关
void m_widget::onGuan1Button()
{
    qDebug()<<"进入第一关的按钮按下";
    //新建第一关页面
    Guanqia_1 = new guanqia_1(this);
    //覆盖原ui
    Guanqia_1->show();
}

void m_widget::onGuan2Button()
{
    qDebug()<<"进入第二关的按钮按下";
    //建立第二关页面
    Guanqia_2 = new guanqia_1(this,2);
    //覆盖原ui
    Guanqia_2->show();
}

void m_widget::onGuan3Button()
{
    qDebug()<<"进入第三关的按钮按下";
    //建立第三关页面
    Guanqia_3 = new guanqia_1(this,3);
    //覆盖原ui
    Guanqia_3->show();
}

void m_widget::onGuan4Button()
{
    QMessageBox::information(this,"提示","功能正在维护中",QMessageBox::Ok);
}

void m_widget::paintEvent(QPaintEvent *)
{
    //监视开启关卡
    switch(currentBarrier)
    {
    case 2:
        ui->guan2->setEnabled(true);
        break;
    case 3:
        ui->guan3->setEnabled(true);
        break;
    case 4:
        ui->guan4->setEnabled(true);
        break;
    case 5:
        ui->guan5->setEnabled(true);
        break;
    case 6:
        ui->guan6->setEnabled(true);
        break;
    case 7:
        ui->guan7->setEnabled(true);
        break;
    case 8:
        ui->guan8->setEnabled(true);
        break;
    case 9:
        ui->guan9->setEnabled(true);
        break;
    }
}
