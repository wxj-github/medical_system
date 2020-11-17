#include "deletecus.h"
#include "ui_deletecus.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>


deletecus::deletecus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletecus)
{
    ui->setupUi(this);
    QSqlQueryModel *model =new QSqlQueryModel;      //显示agency表内所有信息
    model->setQuery("select* from client order by danhao");
    model->setHeaderData(0,Qt::Horizontal,tr("单号"));
    model->setHeaderData(1,Qt::Horizontal,tr("编号"));
    model->setHeaderData(2,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(3,Qt::Horizontal,tr("性别"));
    model->setHeaderData(4,Qt::Horizontal,tr("年龄"));
    model->setHeaderData(5,Qt::Horizontal,tr("住址"));
    model->setHeaderData(6,Qt::Horizontal,tr("电话"));
    model->setHeaderData(7,Qt::Horizontal,tr("症状"));
    model->setHeaderData(8,Qt::Horizontal,tr("已购药品"));
    model->setHeaderData(9,Qt::Horizontal,tr("经办人编号"));
    model->setHeaderData(10,Qt::Horizontal,tr("录入日期"));
    model->setHeaderData(11,Qt::Horizontal,tr("备注"));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);       //要在setmodel后设置
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,130);
    ui->tableView->setColumnWidth(3,50);
    ui->tableView->setColumnWidth(4,50);
    ui->tableView->setColumnWidth(5,150);
    ui->tableView->setColumnWidth(6,150);
    ui->tableView->setColumnWidth(7,200);
    ui->tableView->setColumnWidth(8,150);
    ui->tableView->setColumnWidth(9,90);
    ui->tableView->setColumnWidth(10,100);
    ui->tableView->setColumnWidth(11,200);
}

deletecus::~deletecus()
{
    delete ui;
}

void deletecus::on_lineEdit_textChanged(const QString &arg1)    //一输入东西马上查询
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =arg1;   //ui->lineEdit->text();             //获取搜索内容
    QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
    switch (index) {
    case 1:     //单号
    {
        QString sql=QString("select* from client where danhao= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 2:       //编号
    {
        QString sql=QString("select* from client where cno= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 3:     //姓名
    {
        QString sql=QString("select* from client where cname = '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }


    }


    newmodel->setHeaderData(0,Qt::Horizontal,tr("单号"));
    newmodel->setHeaderData(1,Qt::Horizontal,tr("编号"));
    newmodel->setHeaderData(2,Qt::Horizontal,tr("姓名"));
    newmodel->setHeaderData(3,Qt::Horizontal,tr("性别"));
    newmodel->setHeaderData(4,Qt::Horizontal,tr("年龄"));
    newmodel->setHeaderData(5,Qt::Horizontal,tr("住址"));
    newmodel->setHeaderData(6,Qt::Horizontal,tr("电话"));
    newmodel->setHeaderData(7,Qt::Horizontal,tr("症状"));
    newmodel->setHeaderData(8,Qt::Horizontal,tr("已购药品"));
    newmodel->setHeaderData(9,Qt::Horizontal,tr("经办人编号"));
    newmodel->setHeaderData(10,Qt::Horizontal,tr("录入日期"));
    newmodel->setHeaderData(11,Qt::Horizontal,tr("备注"));

    ui->tableView->setModel(newmodel);
}

void deletecus::on_pushButton_clicked()
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =ui->lineEdit->text();             //获取要删除的内容
    switch (index) {
    case 1:         //单号
    {
        QString cha=QString("select ano from client where danhao ='%0'").arg(tiaojian);
        QSqlQuery chaa;
        QString num;
        chaa.exec(cha);
        while(chaa.next())
        {
            num=chaa.value(0).toString();
        }
        if(!QString(num).isEmpty())     //不为空，说明存在，可以删除
        {
            QString sql;
            sql=QString("delete from client where danhao ='%0'").arg(tiaojian);
            QSqlQuery shanchu;
            bool ok = shanchu.exec(sql);
            if(ok)
            {
                QString bucunzai="成功删除单号为"+tiaojian+"的顾客信息!";
                QMessageBox::about(this,"成功",bucunzai);
                ui->lineEdit->clear();
                ui->tableView->clearSpans();

            }
            else {
                QMessageBox::about(this,"失败","删除失败");
            }
        }
        else {
            QMessageBox::critical(this,"错误","不存在该顾客信息！");
        }

        break;
    }
    case 2:         //编号
    {
        QString sql=QString("select *from client where cno ='%0' ").arg(tiaojian);
        QSqlQuery jiancha;
        jiancha.exec(sql);
        QString num;
        while (jiancha.next())
        {
            num = jiancha.value(0).toString();
        }
        if(!QString(num).isEmpty())//不为空，说明存在，可以删除
        {
            QString sql;
            sql=QString("delete from client where cno ='%0'").arg(tiaojian);
            QSqlQuery shanchu;
            bool ok = shanchu.exec(sql);
            if(ok)
            {
                QString bucunzai="成功删除编号为"+tiaojian+"的顾客信息!";
                QMessageBox::about(this,"成功",bucunzai);
                ui->lineEdit->clear();
                ui->tableView->clearSpans();

            }
            else {
                QMessageBox::about(this,"失败","删除失败");
            }
        }
        else {
            QMessageBox::critical(this,"错误","不存在该顾客信息！");
        }

        break;
    }
    case 3:         //姓名
    {
        QString cha=QString("select cno from client where cname ='%0'").arg(tiaojian);
        QSqlQuery jiancha;
        QString number;
        jiancha.exec(cha);

        while(jiancha.next())
        {
            number=jiancha.value(0).toString();
            number=number.simplified();
        }
        if(!QString(number).isEmpty())          //不为空，说明存在该顾客
        {
                QString sql;
                sql=QString("delete from client where cname ='%0'").arg(tiaojian);
                QSqlQuery shanchu;
                bool ok = shanchu.exec(sql);
                if(ok)
                {
                    QMessageBox::about(this,"成功","删除成功");
                    ui->lineEdit->clear();
                    ui->tableView->clearSpans();

                }
                else {
                    QMessageBox::about(this,"失败","删除失败");
                }

        }
        else {
            QMessageBox::critical(this,"错误","不存在该顾客信息！");
        }
        break;
    }


    }

}
