#ifndef READCUS_H
#define READCUS_H

#include <QDialog>

namespace Ui {
class readcus;
}

class readcus : public QDialog
{
    Q_OBJECT

public:
    explicit readcus(QWidget *parent = nullptr);
    ~readcus();

private slots:
    void on_pushButton_clicked();

private:
    Ui::readcus *ui;
};

#endif // READCUS_H
