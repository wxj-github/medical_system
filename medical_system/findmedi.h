#ifndef FINDMEDI_H
#define FINDMEDI_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class findmedi;
}

class findmedi : public QDialog
{
    Q_OBJECT

public:
    explicit findmedi(QWidget *parent = nullptr);
    ~findmedi();


private slots:
    void on_pushButton_clicked();

private:
    Ui::findmedi *ui;

};

#endif // FINDMEDI_H
