#ifndef M_WIDGET_H
#define M_WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QPaintEvent>
#include"guanqia_1.h"


/*
 *分数机制：
 *  三消每个10分，
 *  四消时3个10分+30，共60分
 * 五消时100分
 * */


namespace Ui {
class m_widget;
}

class m_widget : public QWidget
{
    Q_OBJECT

public:
    explicit m_widget(QWidget *parent = 0);
    static int currentBarrier;    //记录当前关卡数
    void paintEvent(QPaintEvent*);
    ~m_widget();

private slots:
    void on_returnButton_clicked();
    void onGuan1Button();
    void onGuan2Button();
    void onGuan3Button();
    void onGuan4Button();
//    void onGuan5Button();
//    void onGuan6Button();
//    void onGuan7Button();
//    void onGuan8Button();
//    void onGuan9Button();

signals:
    void returned();

private:
    Ui::m_widget *ui;
    //基于第一关产生随后的关卡
    guanqia_1 *Guanqia_1;
    guanqia_1*Guanqia_2;
    guanqia_1*Guanqia_3;
    guanqia_1*Guanqia_4;
//    guanqia_1*Guanqia_5;
//    guanqia_1*Guanqia_6;
//    guanqia_1*Guanqia_7;
//    guanqia_1*Guanqia_8;
//    guanqia_1*Guanqia_9;

};

#endif // M_WIDGET_H
