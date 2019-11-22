#ifndef M_INSTRUCTION_H
#define M_INSTRUCTION_H

#include <QWidget>

namespace Ui {
class m_instruction;
}

class m_instruction : public QWidget
{
    Q_OBJECT

public:
    explicit m_instruction(QWidget *parent = 0);
    ~m_instruction();


private slots:
    void on_returnButton_clicked();

private:
    Ui::m_instruction *ui;
};

#endif // M_INSTRUCTION_H
