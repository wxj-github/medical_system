#ifndef DELETEMEDI_H
#define DELETEMEDI_H

#include <QDialog>

namespace Ui {
class deletemedi;
}

class deletemedi : public QDialog
{
    Q_OBJECT

public:
    explicit deletemedi(QWidget *parent = nullptr);
    ~deletemedi();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::deletemedi *ui;
};

#endif // DELETEMEDI_H
