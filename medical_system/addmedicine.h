#ifndef ADDMEDICINE_H
#define ADDMEDICINE_H

#include <QDialog>

namespace Ui {
class addmedicine;
}

class addmedicine : public QDialog
{
    Q_OBJECT

public:
    explicit addmedicine(QWidget *parent = nullptr);
    ~addmedicine();


private slots:
    void on_pbt_addmedi_cancel_clicked();

    void on_pbt_addmedi_ok_clicked();

    void on_textEdit_textChanged();

private:
    Ui::addmedicine *ui;
};

#endif // ADDMEDICINE_H
