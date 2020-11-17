#ifndef DELETECUS_H
#define DELETECUS_H

#include <QDialog>

namespace Ui {
class deletecus;
}

class deletecus : public QDialog
{
    Q_OBJECT

public:
    explicit deletecus(QWidget *parent = nullptr);
    ~deletecus();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::deletecus *ui;
};

#endif // DELETECUS_H
