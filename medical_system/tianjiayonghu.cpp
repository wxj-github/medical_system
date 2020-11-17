#include "tianjiayonghu.h"
#include "ui_tianjiayonghu.h"


#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QRegExp>

tianjiayonghu::tianjiayonghu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tianjiayonghu)
{
    ui->setupUi(this);
    QRegExp rer("[0-9a-zA-z]+$");
    QValidator *yi = new QRegExpValidator(rer,ui->le_account );
    ui->le_account->setValidator( yi );
    ui->le_mima->setValidator(yi);
    ui->le_mima->setValidator(yi);
    ui->le_account->setMaxLength(10);
    ui->le_mima->setMaxLength(10);
    ui->le_mima2->setMaxLength(10);
}

tianjiayonghu::~tianjiayonghu()
{
    delete ui;
}

void tianjiayonghu::on_pushButton_2_clicked()
{
    this->close();
    ui->le_mima->clear();
    ui->le_mima2->clear();
    ui->le_account->clear();
}

void tianjiayonghu::on_pushButton_clicked() //添加信息账户
{
    QString hao=ui->le_account->text();
    QString passwd=ui->le_mima->text();
    QString passwd2=ui->le_mima2->text();

    if(hao.length()<1||passwd.length()<1||passwd2.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查账号密码是否填写完整。");
    }

    else {
        QString cha=QString("select password from account where account ='%0' collate chinese_prc_cs_as").arg(hao);
        QSqlQuery jiancha;
        QString number;
        jiancha.exec(cha);
        while(jiancha.next())
        {
            number=jiancha.value(0).toString();
        }
        if(!QString(number).isEmpty())//不为空，说明账号存在
        {
            QMessageBox::critical(this,"错误","已存在该账号！请重新输入！");
        }
        else    //不存在，可以创建该账号
        {
            if(passwd!=passwd2)
            {
                QMessageBox::critical(this,"错误","两次密码不一样！请重新输入！");
                ui->le_mima->clear();
                ui->le_mima2->clear();
            }
            else {
                QString sql;
                sql=QString("insert into account (account,password)"
                            "values ('%1','%2')").arg(hao).arg(passwd);
                bool ok=jiancha.exec(sql);
                if(ok)
                {
                    QMessageBox::about(this,"成功","成功添加账号!");
                    ui->le_mima->clear();
                    ui->le_mima2->clear();
                    ui->le_account->clear();
                }
                else {
                    QMessageBox::about(this,"失败","添加失败!");
                }
            }
        }
    }

}
