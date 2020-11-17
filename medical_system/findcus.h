#ifndef FINDCUS_H
#define FINDCUS_H

#include <QDialog>

namespace Ui {
class findcus;
}

class findcus : public QDialog
{
    Q_OBJECT

public:
    explicit findcus(QWidget *parent = nullptr);
    ~findcus();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::findcus *ui;
};

#endif // FINDCUS_H
