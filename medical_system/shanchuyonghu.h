#ifndef SHANCHUYONGHU_H
#define SHANCHUYONGHU_H

#include <QDialog>

namespace Ui {
class shanchuyonghu;
}

class shanchuyonghu : public QDialog
{
    Q_OBJECT

public:
    explicit shanchuyonghu(QWidget *parent = nullptr);
    ~shanchuyonghu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::shanchuyonghu *ui;
};

#endif // SHANCHUYONGHU_H
