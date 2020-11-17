#include "findmedi.h"
#include "ui_findmedi.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


findmedi::findmedi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findmedi)
{
    ui->setupUi(this);

    QSqlQueryModel *model =new QSqlQueryModel;      //显示medicine表内所有信息

    model->setQuery("select* from medicine order by mno");
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
    model->setHeaderData(3,Qt::Horizontal,tr("功效"));

//    ui->tableView->setSortingEnabled(true);
//    ui->tableView->horizontalHeader()->setSortIndicator(3,Qt::AscendingOrder);
    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0,100);       //要在setmodel后设置
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,350);
    ui->tableView->verticalHeader()->hide();            //隐藏行序号




}

findmedi::~findmedi()
{
    delete ui;
}

void findmedi::on_pushButton_clicked()
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =ui->lineEdit->text();             //获取搜索内容
    switch(index)
    {
    case 1:
    {            //编号
        QSqlQueryModel *nummodel =new QSqlQueryModel;
        QString sql=QString("select* from medicine where mno= '%0' ").arg(tiaojian);
        nummodel->setQuery(sql);
        nummodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        nummodel->setHeaderData(1,Qt::Horizontal,tr("名称"));
        nummodel->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
        nummodel->setHeaderData(3,Qt::Horizontal,tr("功效"));
        ui->tableView->setModel(nummodel);
        break;
    }
    case 2:
    {                   //名称
        QSqlQueryModel *nummodel =new QSqlQueryModel;
        QString sql=QString("select* from medicine where mname like '%%0%' ").arg(tiaojian);
        nummodel->setQuery(sql);
        nummodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        nummodel->setHeaderData(1,Qt::Horizontal,tr("名称"));
        nummodel->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
        nummodel->setHeaderData(3,Qt::Horizontal,tr("功效"));
        ui->tableView->setModel(nummodel);
        break;
    }
    case 3:
    {               //服用方法
        QSqlQueryModel *nummodel =new QSqlQueryModel;
        QString sql=QString("select* from medicine where mmode like '%%0%' ").arg(tiaojian);
        nummodel->setQuery(sql);
        nummodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        nummodel->setHeaderData(1,Qt::Horizontal,tr("名称"));
        nummodel->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
        nummodel->setHeaderData(3,Qt::Horizontal,tr("功效"));
        ui->tableView->setModel(nummodel);
        break;
    }
    case 4:
    {                               //功效
        QSqlQueryModel *nummodel =new QSqlQueryModel;
        QString sql=QString("select* from medicine where mefficacy like '%%0%' ").arg(tiaojian);
        nummodel->setQuery(sql);
        nummodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
        nummodel->setHeaderData(1,Qt::Horizontal,tr("名称"));
        nummodel->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
        nummodel->setHeaderData(3,Qt::Horizontal,tr("功效"));
        ui->tableView->setModel(nummodel);
        break;
    }
    default:
        break;
    }
}
