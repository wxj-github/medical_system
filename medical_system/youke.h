#ifndef YOUKE_H
#define YOUKE_H

#include <QDialog>

namespace Ui {
class youke;
}

class youke : public QDialog
{
    Q_OBJECT

public:
    explicit youke(QWidget *parent = nullptr);
    ~youke();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::youke *ui;
};

#endif // YOUKE_H
