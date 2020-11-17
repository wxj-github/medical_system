#include "changesales.h"
#include "ui_changesales.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
QString static num;
changesales::changesales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changesales)
{
    ui->setupUi(this);
    QRegExp re("[0-9]+$");                 //设置只能输入数字
    QValidator *xian = new QRegExpValidator(re, ui->le_num);
    ui->le_num->setValidator(xian);
    ui->le_num->setMaxLength(8);
    ui->le_name->setMaxLength(8);
    ui->le_phone->setMaxLength(12);
    ui->pushButton->setDisabled(true);               //不可点击，变灰
    ui->le_num->setFocus();
    setTabOrder(ui->le_num,ui->le_name);
    setTabOrder(ui->le_name,ui->le_phone);
    setTabOrder(ui->le_phone,ui->textEdit);
}

changesales::~changesales()
{
    delete ui;
}




void changesales::on_pushButton_3_clicked()    //获取信息按钮,查询是否存在该经办人编号
{
    num=ui->le_num->text();         //存储旧id
    QString name;
    QString sex;
    QString phone;
    QString mark;
    QString sq;
    sq=QString("select * from agency where ano ='%0'").arg(num);
    QSqlQuery jiancha;
    jiancha.exec(sq);
    QString number;
    while (jiancha.next())
    {
        number = jiancha.value(0).toString();
        name = jiancha.value(1).toString();
        sex = jiancha.value(2).toString();
        phone = jiancha.value(3).toString();
        mark = jiancha.value(4).toString();
    }

    if(QString(number).isEmpty())     //判断是否存在
    {
        QMessageBox::about(this,"错误","不存在该经办人编号");
        ui->le_name->clear();
        ui->le_phone->clear();
        ui->textEdit->clear();
        ui->pushButton->setDisabled(true);               //不可点击，变灰
    }
    else {
        QMessageBox::about(this,"成功","获取成功！");
        ui->le_name->setText(name);
        if(sex=="男")
        ui->radioButton->setChecked(true);
        else
        ui->radioButton_2->setChecked(true);
        ui->le_phone->setText(phone);
        ui->textEdit->setText(mark);
        ui->pushButton->setDisabled(false);               //可点击修改信息
    }

}


void changesales::on_pushButton_clicked()       //添加信息按钮
{
    QString newnum;
    newnum=ui->le_num->text();
    QString name=ui->le_name->text();
    QString sex=ui->sexGroup->checkedButton()->text();
    QString phone=ui->le_phone->text();
    QString mark=ui->textEdit->toPlainText();

    QString sq;
    sq=QString("select * from agency where ano ='%0'").arg(newnum);     //再次查询是否存在该新编号
    QSqlQuery jiancha;
    jiancha.exec(sq);
    QString number;
    while (jiancha.next())
    {
        number = jiancha.value(0).toString();
        number = number.simplified();
    }

    if(newnum.length()<1 || name.length()<1  || phone.length()<1 || mark.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查信息是否填写完整。");
    }
    else {

        if(!QString(number).isEmpty()&&number!=num)
        {
            QMessageBox::about(this,"失败","修改失败,已存在该编号,请重新修改");
            ui->le_num->setText(num);
        }

        else {
            newnum=ui->le_num->text();
            QString sql;
            QSqlQuery geng;   //更新数据

            geng.prepare("update agency set ano=?,aname=?,asex=?, aphone=?,aremark=? where ano=?");
            geng.addBindValue(newnum);
            geng.addBindValue(name);
            geng.addBindValue(sex);
            geng.addBindValue(phone);
            geng.addBindValue(mark);
            geng.addBindValue(num);
            bool ok= geng.exec();    //更新数据

            if(ok)
            {
                QMessageBox::about(this,"成功","修改成功");
                ui->le_num->clear();
                ui->le_name->clear();
                ui->le_phone->clear();
                ui->textEdit->clear();
                ui->pushButton->setDisabled(true);      //不可点击


                //判断老经办人是否存在顾客信息表
                QString sqll;
                sqll=QString("SELECT ano FROM client");              //检查编号是否存在
                QSqlQuery cha;
                cha.exec(sqll);
                QString numbe;

                 while (cha.next())
                 {
                       numbe=cha.value(0).toString();
                       numbe=numbe.simplified();

                       QSqlQuery geng;
                       geng.prepare("UPDATE client SET ano=? where ano = ?");
                       geng.addBindValue(newnum);
                       geng.addBindValue(num);
                       geng.exec();

                 }

            }
            else
            {
                QMessageBox::about(this,"失败","修改失败");
            }


        }


    }

}





void changesales::on_textEdit_textChanged()
{
    QString textContent = ui->textEdit->toPlainText();
    int length = textContent.count();
    int maxLength = 50; // 最大字符数
    if(length > maxLength) {
        int position = ui->textEdit->textCursor().position();
        QTextCursor textCursor = ui->textEdit->textCursor();
        textContent.remove(position-(length-maxLength), length-maxLength);
        ui->textEdit->setText(textContent);
        textCursor.setPosition(position-(length-maxLength));
        ui->textEdit->setTextCursor(textCursor);
    }
}



void changesales::on_pushButton_2_clicked()
{
    this->close();
    ui->le_num->clear();
    ui->le_name->clear();
    ui->le_phone->clear();
    ui->textEdit->clear();
}
