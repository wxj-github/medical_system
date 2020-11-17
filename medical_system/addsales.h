#ifndef ADDSALES_H
#define ADDSALES_H

#include <QDialog>

namespace Ui {
class addsales;
}

class addsales : public QDialog
{
    Q_OBJECT

public:
    explicit addsales(QWidget *parent = nullptr);
    ~addsales();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_textEdit_textChanged();

private:
    Ui::addsales *ui;
};

#endif // ADDSALES_H
