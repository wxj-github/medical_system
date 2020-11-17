#include "xiugaimima.h"
#include "ui_xiugaimima.h"


#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QRegExp>

xiugaimima::xiugaimima(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xiugaimima)
{
    ui->setupUi(this);
    QRegExp rer("[0-9a-zA-z]+$");
    QValidator *yi = new QRegExpValidator(rer, ui->le_account);
    ui->le_account->setValidator( yi );
    ui->le_account->setMaxLength(10);
    ui->le_newpass->setMaxLength(10);
    ui->le_oldpass->setMaxLength(10);
    ui->le_newpass2->setMaxLength(10);


}

xiugaimima::~xiugaimima()
{
    delete ui;
}

void xiugaimima::on_pushButton_clicked()
{
    QString acc=ui->le_account->text();
    QString pas=ui->le_oldpass->text();
    QString newpas=ui->le_newpass->text();
    QString newpas2=ui->le_newpass2->text();

    if(acc.length()<1||pas.length()<1||newpas.length()<1||newpas2.length()<1)
    {
        QMessageBox::critical(this,"失败","请检查账号、原密码、新密码是否填写完整");
    }
    else {
        QString cha=QString("select password from account where account ='%0'").arg(acc);
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
            if(pas==number)     //成功配对账号密码
            {
                if(newpas==newpas2)     //新密码两个都相同,进行修改密码
                {
                    QSqlQuery geng;   //更新数据
                    geng.prepare("update account set password=? where account=?");
                    geng.addBindValue(newpas);
                    geng.addBindValue(acc);
                    bool ok= geng.exec();    //更新数据
                    if(ok)
                    {
                        QMessageBox::about(this,"成功","修改成功");
                        ui->le_newpass->clear();
                        ui->le_newpass2->clear();
                        ui->le_newpass2->clear();
                    }
                    else {
                        QMessageBox::about(this,"失败","修改失败");
                    }
                }
                else {
                    QMessageBox::critical(this,"失败","两次输入的新密码不相同，请重新输入!");
                    ui->le_newpass->clear();
                    ui->le_newpass2->clear();
                }
            }
            else {
                QMessageBox::critical(this,"错误","密码输入有误！请重新输入！","确定");     //弹出失败窗口
                ui->le_oldpass->clear();
            }
        }
    }



}

void xiugaimima::on_pushButton_2_clicked()
{
    this->close();
    ui->le_account->clear();
    ui->le_newpass->clear();
    ui->le_newpass2->clear();
    ui->le_newpass2->clear();
}
