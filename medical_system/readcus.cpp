#include "readcus.h"
#include "ui_readcus.h"
#include <QSqlQueryModel>
readcus::readcus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readcus)
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
     ui->tableView->verticalHeader()->hide();            //隐藏行序号
}

readcus::~readcus()
{
    delete ui;
}

void readcus::on_pushButton_clicked()       //刷新按钮
{
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
     ui->tableView->verticalHeader()->hide();            //隐藏行序号
}
