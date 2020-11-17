#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"mainwindow.h"
#include<QString>
#include"youke.h"

 QString static account;

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();




private slots:
    void on_btn_login_cancel_clicked();

    void on_btn_login_ok_clicked();


    void on_pushButton_4_clicked();

private:
    Ui::login *ui;
    MainWindow j;
    youke y;
};

#endif // LOGIN_H
