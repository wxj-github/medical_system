#include "deletesales.h"
#include "ui_deletesales.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>

deletesales::deletesales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletesales)
{
    ui->setupUi(this);
    QSqlQueryModel *model =new QSqlQueryModel;      //显示agency表内所有信息
    model->setQuery("select* from agency order by ano");
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2,Qt::Horizontal,tr("性别"));
    model->setHeaderData(3,Qt::Horizontal,tr("电话"));
    model->setHeaderData(4,Qt::Horizontal,tr("备注"));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(4,200);
     ui->tableView->verticalHeader()->hide();            //隐藏行序号
}

deletesales::~deletesales()
{
    delete ui;
}

void deletesales::on_lineEdit_textChanged(const QString &arg1)
{
    QString tiaojian =arg1;
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QSqlQueryModel *newmodel =new QSqlQueryModel;
    switch (index) {
        case 1:         //编号
    {
        QString sql=QString("select* from agency where ano= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 2:     //名字
    {
        QString sql=QString("select* from agency where aname= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    }
    newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    newmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    newmodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
    newmodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
    newmodel->setHeaderData(4,Qt::Horizontal,tr("备注"));
    ui->tableView->setModel(newmodel);
}

void deletesales::on_pushButton_clicked()
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =ui->lineEdit->text();             //获取要删除的内容
    switch (index) {
        case 1:     //编号
    {
        QString cha=QString("select ano from agency where ano ='%0'").arg(tiaojian);
        QSqlQuery chaa;
        QString num;
        chaa.exec(cha);
        while(chaa.next())
        {
            num=chaa.value(0).toString();
        }

        if(!QString(num).isEmpty())
        {       //不为空，说明存在该经办人，检查是否存在与顾客信息表
               QString sql=QString("select *from client where ano ='%0' ").arg(tiaojian);
               QSqlQuery jiancha;
               jiancha.exec(sql);
               QString number;
               while (jiancha.next())
               {
                   number = jiancha.value(0).toString();
               }

               if(QString(number).isEmpty())     //为空，可以删除
               {
                   QString sqll=QString("delete from agency where ano ='%0'").arg(tiaojian);
                   QSqlQuery shanchu;
                   bool ok = shanchu.exec(sqll);
                   if(ok)
                   {
                       QString bucunzai="成功删除编号为"+tiaojian+"的经办人信息!";
                       QMessageBox::about(this,"成功",bucunzai);
                       ui->lineEdit->clear();
                       ui->tableView->clearSpans();

                   }
                   else {
                       QMessageBox::critical(this,"失败","删除失败");
                   }
                   break;
               }
               else {                  //顾客信息表里含有该编号，不能删除
                   QString cunzai="顾客信息表内含有该经办人编号"+tiaojian+"的信息！";
                   QMessageBox::critical(this,"删除失败",cunzai);
               }
        }

        else {
            QMessageBox::critical(this,"错误","不存在该药品信息！");
        }
            break;
        }

    case 2:         //名字
    {
        QString cha=QString("select ano from agency where aname ='%0'").arg(tiaojian);
        QSqlQuery jiancha;
        QString number;
        jiancha.exec(cha);
        QStringList list;
        while(jiancha.next())
        {
            number=jiancha.value(0).toString();
            number=number.simplified();
            list.append(number);            //把这个名字的经办人的编号全部收集起来
        }

        if(!QString(number).isEmpty())          //不为空，说明存在该经办人
        {

            for (int i=0;i<list.size();i++)
            {
                //判断该经办人编号是否存在于顾客信息表
                QString sql=QString("select *from client where mno ='%0' ").arg(list[i]);
                jiancha.exec(sql);      //执行
                QString num;
                while (jiancha.next())
                {
                    num = jiancha.value(0).toString();
                }

                if(QString(num).isEmpty())     //为空，可以删除
                {
                    QString sqll=QString("delete from agency where ano ='%0'").arg(list[i]);
                    QSqlQuery shanchu;
                    bool ok = shanchu.exec(sqll);
                    if(ok)
                    {
                        QString bucunzai="成功删除编号为"+list[i]+"的经办人信息!";
                        QMessageBox::about(this,"成功",bucunzai);
                        ui->lineEdit->clear();
                        ui->tableView->clearSpans();

                    }
                    else {
                        QMessageBox::critical(this,"失败","删除失败");
                    }
                    break;
                }
                else {                  //顾客信息表里含有该编号，不能删除
                    QString cunzai="顾客信息表内含有该经办人编号"+list[i]+"的信息！";
                    QMessageBox::critical(this,"删除失败",cunzai);
                }

            }


        }
        else {
            QMessageBox::critical(this,"错误","不存在该经办人信息！");
        }

        break;
    }

    }
}
