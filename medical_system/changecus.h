#ifndef CHANGECUS_H
#define CHANGECUS_H

#include <QDialog>

namespace Ui {
class changecus;
}

class changecus : public QDialog
{
    Q_OBJECT

public:
    explicit changecus(QWidget *parent = nullptr);
    ~changecus();

private slots:
    void on_pb_cancel_clicked();

    void on_pushButton_clicked();

    void on_pb_ok_clicked();

private:
    Ui::changecus *ui;
};

#endif // CHANGECUS_H
