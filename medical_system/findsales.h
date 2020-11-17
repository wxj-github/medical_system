#ifndef FINDSALES_H
#define FINDSALES_H

#include <QDialog>

namespace Ui {
class findsales;
}

class findsales : public QDialog
{
    Q_OBJECT

public:
    explicit findsales(QWidget *parent = nullptr);
    ~findsales();

private slots:
    void on_pushButton_clicked();

private:
    Ui::findsales *ui;
};

#endif // FINDSALES_H
