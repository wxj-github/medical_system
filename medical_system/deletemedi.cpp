#include "deletemedi.h"
#include "ui_deletemedi.h"


#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>



deletemedi::deletemedi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletemedi)
{
    ui->setupUi(this);
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
    ui->tableView->setColumnWidth(3,300);
    ui->tableView->verticalHeader()->hide();            //隐藏行序号

}

deletemedi::~deletemedi()
{
    delete ui;
}

void deletemedi::on_lineEdit_textChanged(const QString &arg1)
{
    QString tiaojian =arg1;
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QSqlQueryModel *newmodel =new QSqlQueryModel;
    switch (index) {
        case 1:     //编号
    {
        QString sql=QString("select* from medicine where mno= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    case 2:         //名称
    {
        QString sql=QString("select* from medicine where mname= '%0' ").arg(tiaojian);
        newmodel->setQuery(sql);
        break;
    }
    }

    newmodel->setHeaderData(0,Qt::Horizontal,tr("编号"));
    newmodel->setHeaderData(1,Qt::Horizontal,tr("名称"));
    newmodel->setHeaderData(2,Qt::Horizontal,tr("服用方法"));
    newmodel->setHeaderData(3,Qt::Horizontal,tr("功效"));
    ui->tableView->setModel(newmodel);
}

void deletemedi::on_pushButton_clicked()
{
    int index =ui->comboBox->currentIndex();        // 获取用户选择了什么查询条件
    QString tiaojian =ui->lineEdit->text();             //获取要删除的内容
    switch (index) {
        case 1:     //编号
    {

        QString cha=QString("select mno from medicine where mno ='%0'").arg(tiaojian);
        QSqlQuery chaa;
        QString num;
        chaa.exec(cha);
        while(chaa.next())
        {
            num=chaa.value(0).toString();
        }

        if(!QString(num).isEmpty())          //不为空，说明存在该药品
        {
            //先判断这个编号是否存在于顾客信息表，如果存在，不能删除
            QString sql=QString("select *from client where mno ='%0' "
                                "UNION select* from client where CHARINDEX(',%0,',mno)>0 "
                                "UNION select* from client where  mno like '%0,%'"
                                "UNION select* from client where CHARINDEX(',%0 ',mno)>0").arg(tiaojian);

            QSqlQuery jiancha;
            jiancha.exec(sql);
            QString number;
            while (jiancha.next())
            {
                number = jiancha.value(0).toString();
            }

            if(QString(number).isEmpty())     //为空，可以删除
            {
                QString sqll=QString("delete from medicine where mno ='%0'").arg(tiaojian);
                QSqlQuery shanchu;
                bool ok = shanchu.exec(sqll);
                if(ok)
                {
                    QString bucunzai="成功删除编号为"+tiaojian+"的药品信息!";
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
                QString cunzai="顾客信息表内含有该药品编号"+tiaojian+"的信息！";
                QMessageBox::critical(this,"删除失败",cunzai);
            }
        }

        else {
            QMessageBox::critical(this,"错误","不存在该药品信息！");
        }


        break;
    }

    case 2:         //名称
    {
            QString cha=QString("select mno from medicine where mname ='%0'").arg(tiaojian);
            QSqlQuery jiancha;
            QString number;
            jiancha.exec(cha);
            QStringList list;
            while(jiancha.next())
            {
                number=jiancha.value(0).toString();
                number=number.simplified();
                list.append(number);

            }
            if(!QString(number).isEmpty())          //不为空，说明存在该药品
            {
                for(int i=0;i<list.size();i++)
                {
                    //判断该药品编号是否存在于顾客信息表
                    QString sql=QString("select *from client where mno ='%0' "
                                        "UNION select* from client where CHARINDEX(',%0,',mno)>0 "
                                        "UNION select* from client where  mno like '%0,%'"
                                        "UNION select* from client where CHARINDEX(',%0 ',mno)>0").arg(list[i]);
                    jiancha.exec(sql);      //执行
                    QString num;
                    while (jiancha.next())
                    {
                        num = jiancha.value(0).toString();
                    }

                    if(QString(num).isEmpty())     //为空，可以删除
                    {
                        QString sqll=QString("delete from medicine where mno ='%0'").arg(list[i]);
                        QSqlQuery shanchu;
                        bool ok = shanchu.exec(sqll);
                        if(ok)
                        {
                            QString bucunzai="成功删除编号为"+list[i]+"的药品信息!";
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
                        QString cunzai="顾客信息表内含有该药品编号"+list[i]+"的信息！";
                        QMessageBox::critical(this,"删除失败",cunzai);
                    }
                }


            }

            else {
                QMessageBox::critical(this,"错误","不存在该药品信息！");
            }

            break;
    }


    }
}
