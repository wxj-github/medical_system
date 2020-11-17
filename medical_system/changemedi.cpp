#include "changemedi.h"
#include "ui_changemedi.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
QString static num;
changemedi::changemedi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changemedi)
{
    ui->setupUi(this);
    QRegExp re("[0-9]+$");                 //设置只能输入数字
    QValidator *xian = new QRegExpValidator(re, ui->le_num);
    ui->le_num->setValidator(xian);
    ui->le_num->setMaxLength(12);
    ui->le_name->setMaxLength(50);
    ui->pb_change->setDisabled(true);               //不可点击，变灰
//    ui->le_name->setEnabled(false);                 //不可点击，变灰
//    ui->le_num->setFocusPolicy(Qt::NoFocus);     //不可点击，不变灰
    //        name =name.simplified();   //去除空格
    ui->le_num->setFocus();
    setTabOrder(ui->le_num,ui->le_name);
    setTabOrder(ui->le_name,ui->textEdit);
}

changemedi::~changemedi()
{
    delete ui;
}

void changemedi::on_pushButton_clicked()         //查询是否存在该编号，存在则显示该编号的所有信息
{
    num = ui->le_num->text();    //num记录旧id用于查询顾客信息是否有旧id,newnum记录新id
    QString name;
    QString fangfa;
    QString gongxiao;
    QString sq;
    sq=QString("select * from medicine where mno ='%0'").arg(num);     //查询是否存在该编号
    QSqlQuery jiancha;
    jiancha.exec(sq);
    QString number;
    while (jiancha.next())
    {
        number = jiancha.value(0).toString();
        name = jiancha.value(1).toString();
        fangfa = jiancha.value(2).toString();
        gongxiao = jiancha.value(3).toString();
    }

    if(QString(number).isEmpty())     //判断是否存在
    {
        QMessageBox::about(this,"错误","不存在该药品编号");
        ui->le_name->clear();
        ui->textEdit->clear();
        ui->pb_change->setDisabled(true);               //不可点击，变灰
    }
    else {
        QMessageBox::about(this,"成功","获取成功！");
        ui->le_name->setText(name);
        if(fangfa=="内服")
        ui->radioButton->setChecked(true);
        else
        ui->radioButton_2->setChecked(true);
        ui->textEdit->setText(gongxiao);
        ui->pb_change->setDisabled(false);               //可点击修改信息
    }
}

void changemedi::on_pb_change_clicked()
{
    //开始重新获取要修改的信息
    QString newnum;
    newnum=ui->le_num->text();          //获取新编号

    QString sq;
    sq=QString("select * from medicine where mno ='%0'").arg(newnum);     //再次查询是否存在该新编号
    QSqlQuery jiancha;
    jiancha.exec(sq);
    QString number;
    while (jiancha.next())
    {
        number = jiancha.value(0).toString();
        number = number.simplified();
    }

    QString name=ui->le_name->text();
    QString fangfa=ui->fangfaGroup->checkedButton()->text();
    QString gongxiao=ui->textEdit->toPlainText();

    if(newnum.length()<1 || name.length()<1  || gongxiao.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查信息是否填写完整。");
    }

    else {

        if(!QString(number).isEmpty()&&number!=num)
        {
            QMessageBox::about(this,"失败","修改失败,已存在该编号,请重新修改");
            ui->le_num->setText(num);
        }

        else
        {
            newnum=ui->le_num->text();
            QString sql;
            QSqlQuery geng;   //更新数据

            geng.prepare("update medicine set mno=?,mname=?,mmode=?, mefficacy=? where mno=?");
            geng.addBindValue(newnum);
            geng.addBindValue(name);
            geng.addBindValue(fangfa);
            geng.addBindValue(gongxiao);
            geng.addBindValue(num);
            bool ok= geng.exec();    //更新数据

            if(ok)
            {
                QMessageBox::about(this,"成功","修改成功");
                ui->le_num->clear();
                ui->le_name->clear();
                ui->textEdit->clear();
                ui->pb_change->setDisabled(true);               //不可点击，变灰
                                                        //至此，药品信息修改完成，开始去搜寻顾客信息中的药品信息

                //判断老编号是否存在顾客信息表
                QString sqll;
                sqll=QString("SELECT mno FROM client");              //检查编号是否存在
                QSqlQuery cha;
                cha.exec(sqll);
                QString numbe;

                while (cha.next())      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                {
                    numbe = cha.value(0).toString();
                    numbe=numbe.simplified();


                    QStringList a;
                    a=numbe.split(",");             //先拆分
                    for(int i=0;i<a.size();i++)
                    {
                        if(num==a[i])
                        {
                            a[i]=newnum;
                        }
                    }
                    QString newnumbe=a.join(',');      //再组装，newnumbe存储最新数据
                    QSqlQuery geng;
                    geng.prepare("UPDATE client SET mno=? where mno = ?");
                    geng.addBindValue(newnumbe);
                    geng.addBindValue(numbe);
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

void changemedi::on_pushButton_3_clicked()
{
    this->close();
    ui->le_num->clear();
    ui->le_name->clear();
    ui->textEdit->clear();
}

void changemedi::on_textEdit_destroyed()
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


