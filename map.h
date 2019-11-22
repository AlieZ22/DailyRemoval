#ifndef MAP
#define MAP

#define WIDTH_MAP 10
#define HEIGTH_MAP 10
#define xialuoshijian 270
#define jiaohuan_shijian 370
#define xiaochu_shijian 370
#include"block.h"
#include<QPixmap>
#include<QObject>

#include"kongkuai.h"
#include"putong.h"
#include"tothemoon.h"

#include<QTime>

#include <vector>



class Map :QObject
{
    Q_OBJECT
public:
    guanqia_1 *guanqia;
    QTimer * m_pTimer ;    //-计时器
    int jiaohuan;      //-记录交换状态
    block *map[WIDTH_MAP][HEIGTH_MAP];
    int xiaochu[WIDTH_MAP][HEIGTH_MAP];
    cor cor1 , cor2;

    std::vector<QLabel*> v;

    Map();
    void show(QPainter &painter);    //显示
    void savemap(const char*str);     //保存地图
    void loadmap(const char *str);      //载入地图
    void cal(int x,int y,int &i,int &j);      //根据鼠标点击位置计算出地图块的二维编号地址
    void yidong(int x1,int y1,int x2, int y2,QLabel* l[WIDTH_MAP][HEIGTH_MAP]);
    int tianchong(QLabel* l[WIDTH_MAP][HEIGTH_MAP]);//填充
    int jianche();//-检测
    void xianchu(QLabel* l[WIDTH_MAP][HEIGTH_MAP]);//消除
    void swap(int x1,int y1,int x2, int y2,QLabel* l[WIDTH_MAP][HEIGTH_MAP]);
    void swap_xy(int x1,int y1,int x2,int y2);     //-仅交换位置
    void houzhi_swap();    //后置交换
    void jiance_xiaochu_tianchong();    //三位一体
    void xiaochu_tianchong();      //二位一体






    void countFrog(int x,int y);


public slots:
    void diaoyong_sanweiyiti();     //三位一体调用槽函数
    void swap_houzhi();    //为了不能交换时回换的槽函数
    void tianchong_slot();  //二位一体
    void shanchu_duoyu();


private slots:
    void handleTimeout();

};

QPixmap splitpixmap(QPixmap pix,int x,int y,int w,int h);



#endif // MAP

