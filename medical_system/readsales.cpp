#include "readsales.h"
#include "ui_readsales.h"
#include <QSqlQueryModel>

readsales::readsales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readsales)
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
     ui->tableView->verticalHeader()->hide();            //隐藏行序号
}

readsales::~readsales()
{
    delete ui;
}

void readsales::on_pushButton_clicked()         //刷新按钮
{
    QSqlQueryModel *model =new QSqlQueryModel;      //显示agency表内所有信息
    model->setQuery("select* from agency");
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2,Qt::Horizontal,tr("性别"));
    model->setHeaderData(3,Qt::Horizontal,tr("电话"));
    model->setHeaderData(4,Qt::Horizontal,tr("备注"));
    ui->tableView->setModel(model);
     ui->tableView->verticalHeader()->hide();            //隐藏行序号
}
