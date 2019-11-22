#ifndef DAILYREMOVAL_H
#define DAILYREMOVAL_H
#include"m_widget.h"
#include"m_instruction.h"
#include <QMainWindow>
#include<QMediaPlayer>
#include<QMediaPlaylist>

namespace Ui {
class DailyRemoval;
}

class DailyRemoval : public QMainWindow
{
    Q_OBJECT

public:
    explicit DailyRemoval(QWidget *parent = 0);
    ~DailyRemoval();

private slots:
    void onQuitButton();     //退出
    void onPlayButton();     //开始游戏
    void onInstructionButton();       //游戏规则说明
    void onMusicPlayButton();       //音乐播放

protected:
    m_widget *myWidget;
    m_instruction*myInstruction;

private:
    Ui::DailyRemoval *ui;
    QMediaPlayer *myPlayer;
    QMediaPlaylist *myPlayList;
    QMediaPlayer*tempPlayer;
    QMediaPlaylist*tempPlayList;
    static int musicFlag;
};

#endif // DAILYREMOVAL_H
