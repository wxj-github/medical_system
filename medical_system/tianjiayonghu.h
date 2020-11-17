#ifndef TIANJIAYONGHU_H
#define TIANJIAYONGHU_H

#include <QDialog>

namespace Ui {
class tianjiayonghu;
}

class tianjiayonghu : public QDialog
{
    Q_OBJECT

public:
    explicit tianjiayonghu(QWidget *parent = nullptr);
    ~tianjiayonghu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::tianjiayonghu *ui;
};

#endif // TIANJIAYONGHU_H
