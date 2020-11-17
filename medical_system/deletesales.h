#ifndef DELETESALES_H
#define DELETESALES_H

#include <QDialog>

namespace Ui {
class deletesales;
}

class deletesales : public QDialog
{
    Q_OBJECT

public:
    explicit deletesales(QWidget *parent = nullptr);
    ~deletesales();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::deletesales *ui;
};

#endif // DELETESALES_H
