#ifndef XIUGAIMIMA_H
#define XIUGAIMIMA_H

#include <QDialog>


namespace Ui {
class xiugaimima;
}

class xiugaimima : public QDialog
{
    Q_OBJECT

public:
    explicit xiugaimima(QWidget *parent = nullptr);
    ~xiugaimima();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::xiugaimima *ui;
};

#endif // XIUGAIMIMA_H
