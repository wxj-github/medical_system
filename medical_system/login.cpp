#include "login.h"
#include "ui_login.h"
#include <QString>
#include "mainwindow.h"
#include <QMessageBox>
#include <QRegExp>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QSqlQuery>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QRegExp rer("[0-9a-zA-z]+$");
    QValidator *yi = new QRegExpValidator(rer, ui->line_account);
    ui->line_account->setValidator( yi );

}

login::~login()
{
    delete ui;
}

void login::on_btn_login_cancel_clicked()  //取消，退出程序
{
    this->close();
}

void login::on_btn_login_ok_clicked()
{
    account = ui->line_account->text();
    QString passwd = ui->line_password->text();


    QString cha=QString("select password from account where account ='%0' collate chinese_prc_cs_as").arg(account);
    QSqlQuery jiancha;
    QString number;
    jiancha.exec(cha);
    while(jiancha.next())
    {
        number=jiancha.value(0).toString();
        number=number.simplified();
    }
    if(QString(number).isEmpty())       //为空说明账号不存在
    {
        QMessageBox::critical(this,"错误","不存在该账号！");
    }
    else        //存在该账户，然后判断密码是否正确
    {
        if(passwd==number)
        {
            QMessageBox::about(this,"成功","登录成功！");
            j.show();           //打开主窗口，主窗口没有继承qdialog，没有exec函数
            this->close();      //关闭登录窗口
        }
        else {
            QMessageBox::critical(this,"登录失败","密码输入有误！请重新输入！","确定");     //弹出失败窗口
        }
    }



}

void login::on_pushButton_4_clicked()
{
        y.exec();

}
