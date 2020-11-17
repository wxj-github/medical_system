#ifndef BANGZHU_H
#define BANGZHU_H

#include <QDialog>

namespace Ui {
class bangzhu;
}

class bangzhu : public QDialog
{
    Q_OBJECT

public:
    explicit bangzhu(QWidget *parent = nullptr);
    ~bangzhu();

private:
    Ui::bangzhu *ui;
};

#endif // BANGZHU_H
