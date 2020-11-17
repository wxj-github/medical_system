#include "findcus.h"
#include "ui_findcus.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>

findcus::findcus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findcus)
{
    ui->setupUi(this);
    ui->cb_fuhao->setVisible(false);
    ui->dateEdit->setVisible(false);
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
//    ui->tableView->verticalHeader()->hide();            //隐藏行序号
}

findcus::~findcus()
{
    delete ui;
}

void findcus::on_pushButton_clicked()
{
    int yaopin=0;        //测试
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =ui->lineEdit->text();             //获取搜索内容
    QSqlQueryModel *newmodel =new QSqlQueryModel;      //显示agency表内所有信息
    switch (index) {
    case 1:     //单号
    {
        QString sql=QString("select* from client where danhao= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 2:     //编号
    {
        QString sql=QString("select* from client where cno= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }

    case 3:     //姓名
    {
        QString sql=QString("select* from client where cname like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }

    case 4:     //性别
    {
        QString sql=QString("select* from client where csex= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }

    case 5:     //年龄
    {
        int fuhao =ui->cb_fuhao->currentIndex();        // 获取用户选择了什么查询条件
                switch(fuhao)
                {
                case 0:         //   =
                {
                    QString sql=QString("select* from client where cage= '%0' ").arg(tiaojian);
                    newmodel->setQuery(sql);
                    break;
                }
                case 1:          //   >
                {
                    QString sql=QString("select* from client where cage > '%0' ").arg(tiaojian);
                    newmodel->setQuery(sql);
                    break;
                }
                case 2:         //   <
                {
                    QString sql=QString("select* from client where cage < '%0' ").arg(tiaojian);
                    newmodel->setQuery(sql);
                    break;
                }
                case 3:         //  >=
                {
                    QString sql=QString("select* from client where cage >= '%0' ").arg(tiaojian);
                    newmodel->setQuery(sql);
                    break;
                }
                case 4:         //   <=
                {
                    QString sql=QString("select* from client where cage <= '%0' ").arg(tiaojian);
                    newmodel->setQuery(sql);
                    break;
                }
                default:
                    break;
                }
            break;
    }

    case 6:      //住址
    {
        QString sql=QString("select* from client where caddress like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 7:        //电话
    {
        QString sql=QString("select* from client where cphone like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 8:         //症状
    {
        QString sql=QString("select* from client where csymptom like '%%0%' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 9:         //已购药品!!!!!!!!!!!
    {
        QSqlQueryModel *yaomodel =new QSqlQueryModel;
        QString sql=QString("select *from client where mno ='%0' "
                            "UNION select* from client where CHARINDEX(',%0,',mno)>0 "
                            "UNION select* from client where  mno like '%0,%'"
                            "UNION select* from client where CHARINDEX(',%0 ',mno)>0").arg(tiaojian);



        yaomodel->setQuery(sql);

        yaomodel->setHeaderData(0,Qt::Horizontal,tr("单号"));
        yaomodel->setHeaderData(1,Qt::Horizontal,tr("编号"));
        yaomodel->setHeaderData(2,Qt::Horizontal,tr("姓名"));
        yaomodel->setHeaderData(3,Qt::Horizontal,tr("性别"));
       yaomodel->setHeaderData(4,Qt::Horizontal,tr("年龄"));
       yaomodel->setHeaderData(5,Qt::Horizontal,tr("住址"));
       yaomodel->setHeaderData(6,Qt::Horizontal,tr("电话"));
       yaomodel->setHeaderData(7,Qt::Horizontal,tr("症状"));
       yaomodel->setHeaderData(8,Qt::Horizontal,tr("已购药品"));
       yaomodel->setHeaderData(9,Qt::Horizontal,tr("经办人编号"));
       yaomodel->setHeaderData(10,Qt::Horizontal,tr("录入日期"));
       yaomodel->setHeaderData(11,Qt::Horizontal,tr("备注"));
        ui->tableView->setModel(yaomodel);
        yaopin=1;
        break;
    }
    case 10:        //经办人
    {
        QString sql=QString("select* from client where ano = '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 11:        //录入时间
    {
        QDateTime shijian;
        shijian=ui->dateEdit->dateTime();
        QString time=shijian.toString("yyyy-MM-dd");
        int fuhao =ui->cb_fuhao->currentIndex();        // 获取用户选择了什么查询条件
                switch(fuhao)
                {
                case 0:     //  =
                {
                    QString sql=QString("select* from client where cdate = '%0' ").arg(time);
                    newmodel->setQuery(sql);
                    break;
                }
                case 1:     //  >
                {
                    QString sql=QString("select* from client where cdate > '%0' ").arg(time);
                    newmodel->setQuery(sql);
                    break;
                }
                case 2:     //   <
                {
                    QString sql=QString("select* from client where cdate < '%0' ").arg(time);
                    newmodel->setQuery(sql);
                    break;
                }
                case 3:     //  >=
                {
                    QString sql=QString("select* from client where cdate >= '%0' ").arg(time);
                    newmodel->setQuery(sql);
                    break;
                }
                case 4:     //  <=
                {
                    QString sql=QString("select* from client where cdate <= '%0' ").arg(time);
                    newmodel->setQuery(sql);
                    break;
                }

                }

        break;
    }
    case 12:        //备注
    {
        QString sql=QString("select* from client where cremark like '%%0%' ").arg(tiaojian);
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
    if(yaopin==0)
    ui->tableView->setModel(newmodel);
}


void findcus::on_comboBox_activated(int index)
{
    if(index==5)        //年龄
    {
        ui->cb_fuhao->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->dateEdit->setVisible(false);
    }
    else if(index==11)      //时间
    {
        ui->cb_fuhao->setVisible(true);
        ui->dateEdit->setVisible(true);
        ui->lineEdit->setVisible(false);
    }
    else {
        ui->cb_fuhao->setVisible(false);
        ui->lineEdit->setVisible(true);
        ui->dateEdit->setVisible(false);
    }

}
