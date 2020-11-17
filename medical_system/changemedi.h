#ifndef CHANGEMEDI_H
#define CHANGEMEDI_H

#include <QDialog>


namespace Ui {
class changemedi;
}

class changemedi : public QDialog
{
    Q_OBJECT

public:
    explicit changemedi(QWidget *parent = nullptr);
    ~changemedi();

private slots:
    void on_pushButton_clicked();

    void on_pb_change_clicked();

    void on_pushButton_3_clicked();

    void on_textEdit_destroyed();

private:
    Ui::changemedi *ui;
};

#endif // CHANGEMEDI_H
