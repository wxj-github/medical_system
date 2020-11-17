#ifndef READMEDI_H
#define READMEDI_H

#include <QDialog>

namespace Ui {
class readmedi;
}

class readmedi : public QDialog
{
    Q_OBJECT

public:
    explicit readmedi(QWidget *parent = nullptr);
    ~readmedi();

private slots:
    void on_pushButton_clicked();

private:
    Ui::readmedi *ui;
};

#endif // READMEDI_H
