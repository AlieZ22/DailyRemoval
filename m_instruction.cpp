#include "m_instruction.h"
#include "ui_m_instruction.h"

m_instruction::m_instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::m_instruction)
{
    ui->setupUi(this);

}

m_instruction::~m_instruction()
{
    delete ui;
}


void m_instruction::on_returnButton_clicked()
{
    //关闭当前窗口，返回到父窗口界面
    this->close();
}
