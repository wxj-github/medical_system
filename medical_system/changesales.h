#ifndef CHANGESALES_H
#define CHANGESALES_H

#include <QDialog>

namespace Ui {
class changesales;
}

class changesales : public QDialog
{
    Q_OBJECT

public:
    explicit changesales(QWidget *parent = nullptr);
    ~changesales();

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::changesales *ui;
};

#endif // CHANGESALES_H
