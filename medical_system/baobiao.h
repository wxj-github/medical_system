#ifndef BAOBIAO_H
#define BAOBIAO_H

#include <QDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
namespace Ui {
class baobiao;
}

class baobiao : public QDialog
{
    Q_OBJECT

public:
    explicit baobiao(QWidget *parent = nullptr);
    ~baobiao();

private slots:


    void on_dateEdit_dateChanged(const QDate &date);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_dateEdit_2_dateChanged(const QDate &date);

    void on_pushButton_clicked();

private:
    Ui::baobiao *ui;
};

#endif // BAOBIAO_H
