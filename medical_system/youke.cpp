#include "youke.h"
#include "ui_youke.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>

youke::youke(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::youke)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    QSqlQueryModel *model =new QSqlQueryModel;      //显示medicine表内所有信息
    model->setQuery("select* from medicine order by mno");
    model->setHeaderData(0,Qt::Horizontal,tr("编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
    model->setHeaderData(3,Qt::Horizontal,tr("功效"));
    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0,100);       //要在setmodel后设置
    ui->tableView->setColumnWidth(1,160);
    ui->tableView->setColumnWidth(2,90);
    ui->tableView->setColumnWidth(3,390);
    ui->tableView->verticalHeader()->hide();            //隐藏行序号





}

youke::~youke()
{
    delete ui;
}

void youke::on_lineEdit_textChanged(const QString &arg1)
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =arg1;             //获取搜索内容
    QSqlQueryModel *nummodel =new QSqlQueryModel;
    switch(index){
    case 1:
    {
        QString sql=QString("select* from medicine where mno= '%0' ").arg(tiaojian);
        nummodel->setQuery(sql);
        break;
    }
    case 2:
    {
        QString sql=QString("select* from medicine where mname like '%%0%' ").arg(tiaojian);
        nummodel->setQuery(sql);
        break;
    }
    case 3:
    {
        QString sql=QString("select* from medicine where mmode like '%%0%' ").arg(tiaojian);
        nummodel->setQuery(sql);
        break;
    }
    case 4:
    {
        QString sql=QString("select* from medicine where mefficacy like '%%0%' ").arg(tiaojian);
        nummodel->setQuery(sql);
        break;
    }
    }

    nummodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    nummodel->setHeaderData(1,Qt::Horizontal,tr("名称"));
    nummodel->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
    nummodel->setHeaderData(3,Qt::Horizontal,tr("功效"));
    ui->tableView->setModel(nummodel);


}

void youke::on_comboBox_currentIndexChanged(int index)
{
    int i =index;        // 获取用户选择了什么查询条件
        switch (i) {
            case 0:
        {
            ui->lineEdit->clear();
            ui->lineEdit->setEnabled(false);
            QSqlQueryModel *model =new QSqlQueryModel;
            model->setQuery("select* from medicine order by mno");
            model->setHeaderData(0,Qt::Horizontal,tr("编号"));
            model->setHeaderData(1,Qt::Horizontal,tr("名称"));
            model->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
            model->setHeaderData(3,Qt::Horizontal,tr("功效"));
            ui->tableView->setModel(model);
            ui->tableView->setColumnWidth(0,100);       //要在setmodel后设置
            ui->tableView->setColumnWidth(1,160);
            ui->tableView->setColumnWidth(2,90);
            ui->tableView->setColumnWidth(3,390);
            ui->tableView->verticalHeader()->hide();            //隐藏行序号
            break;
        }
        case 1:
            ui->lineEdit->setEnabled(true);
            break;
        case 2:
            ui->lineEdit->setEnabled(true);
            break;
        case 3:
            ui->lineEdit->setEnabled(true);
            break;
        case 4:
            ui->lineEdit->setEnabled(true);
            break;
        }
}
