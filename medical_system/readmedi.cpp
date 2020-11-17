#include "readmedi.h"
#include "ui_readmedi.h"
#include <QSqlQueryModel>
readmedi::readmedi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readmedi)
{
    ui->setupUi(this);
    QSqlQueryModel *model =new QSqlQueryModel;      //显示medicine表内所有信息
    model->setQuery("select* from medicine order by mno");
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
    model->setHeaderData(3,Qt::Horizontal,tr("功效"));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(3,250);
     ui->tableView->verticalHeader()->hide();            //隐藏行序号

}

readmedi::~readmedi()
{
    delete ui;
}

void readmedi::on_pushButton_clicked()          //刷新按钮，可更新数据，没有的话数据库修改后重新进入界面不会显示新数据
{
    QSqlQueryModel *model =new QSqlQueryModel;      //显示medicine表内所有信息
    model->setQuery("select* from medicine");
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
    model->setHeaderData(3,Qt::Horizontal,tr("功效"));
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();            //隐藏行序号
}
