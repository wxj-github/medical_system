#ifndef READSALES_H
#define READSALES_H

#include <QDialog>

namespace Ui {
class readsales;
}

class readsales : public QDialog
{
    Q_OBJECT

public:
    explicit readsales(QWidget *parent = nullptr);
    ~readsales();

private slots:
    void on_pushButton_clicked();

private:
    Ui::readsales *ui;
};

#endif // READSALES_H
