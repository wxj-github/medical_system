#include "shanchuyonghu.h"
#include "ui_shanchuyonghu.h"


#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QRegExp>

shanchuyonghu::shanchuyonghu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shanchuyonghu)
{
    ui->setupUi(this);
    QRegExp rer("[0-9a-zA-z]+$");
    QValidator *yi = new QRegExpValidator(rer,ui->le_account );
    ui->le_account->setValidator( yi );
    ui->lineEdit->setValidator(yi);
    ui->le_account->setMaxLength(10);
    ui->lineEdit->setMaxLength(10);
}

shanchuyonghu::~shanchuyonghu()
{
    delete ui;
}

void shanchuyonghu::on_pushButton_2_clicked()
{
    this->close();
    ui->le_account->clear();
    ui->lineEdit->clear();
}

void shanchuyonghu::on_pushButton_clicked()
{
    QString hao=ui->le_account->text();
    QString mima=ui->lineEdit->text();

    if(hao.length()<1||mima.length()<1)
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
             number=number.simplified();
        }
        if(QString(number).isEmpty())       //为空，不存在
        {
            QMessageBox::critical(this,"错误","不存在该账号！");
        }
        else {
            if(mima==number)    //密码匹配,去删除
            {
               QString sql;
               sql=QString("delete from account where account='%0' collate chinese_prc_cs_as").arg(hao);
               bool ok=jiancha.exec(sql);
               if(ok)
               {
                   QMessageBox::about(this,"成功","成功删除该账号!");
                   ui->le_account->clear();
                   ui->lineEdit->clear();
               }
               else
               {
                   QMessageBox::about(this,"失败","删除失败!");
               }
            }
            else {
                QMessageBox::critical(this,"错误","密码有误请重新输入！");
                ui->lineEdit->clear();
            }
        }


    }
}
