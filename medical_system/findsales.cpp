#include "findsales.h"
#include "ui_findsales.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


findsales::findsales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findsales)
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
    ui->tableView->setColumnWidth(0,100);       //要在setmodel后设置
    ui->tableView->setColumnWidth(1,130);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,150);
    ui->tableView->setColumnWidth(4,250);
     ui->tableView->verticalHeader()->hide();            //隐藏行序号

}

findsales::~findsales()
{
    delete ui;
}

void findsales::on_pushButton_clicked()
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =ui->lineEdit->text();             //获取搜索内容

    switch(index)
    {
    case 1:
    {           //编号
        QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
        QString sql=QString("select* from agency where ano= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        newmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        newmodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
        newmodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
        newmodel->setHeaderData(4,Qt::Horizontal,tr("备注"));
        ui->tableView->setModel(newmodel);
        break;
    }
    case 2:    //姓名
    {
        QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
        QString sql=QString("select* from agency where aname like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        newmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        newmodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
        newmodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
        newmodel->setHeaderData(4,Qt::Horizontal,tr("备注"));
        ui->tableView->setModel(newmodel);
        break;
    }
    case 3:         //性别
    {
        QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
        QString sql=QString("select* from agency where asex = '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        newmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        newmodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
        newmodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
        newmodel->setHeaderData(4,Qt::Horizontal,tr("备注"));
        ui->tableView->setModel(newmodel);
        break;
    }

    case 4:         //电话
    {
        QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
        QString sql=QString("select* from agency where aphone like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        newmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        newmodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
        newmodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
        newmodel->setHeaderData(4,Qt::Horizontal,tr("备注"));
        ui->tableView->setModel(newmodel);
        break;
    }

    case 5:      //备注
    {
        QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
        QString sql=QString("select* from agency where aremark like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        newmodel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        newmodel->setHeaderData(2,Qt::Horizontal,tr("性别"));
        newmodel->setHeaderData(3,Qt::Horizontal,tr("电话"));
        newmodel->setHeaderData(4,Qt::Horizontal,tr("备注"));
        ui->tableView->setModel(newmodel);
        break;
    }
    default:
        break;

    }
}
