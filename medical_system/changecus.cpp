#include "changecus.h"
#include "ui_changecus.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QRegExp>
QString static danhao;
QString static num;
QString static name;
QString static sex;
changecus::changecus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changecus)
{
    ui->setupUi(this);
    ui->pb_ok->setDisabled(true);
    QRegExp re("[0-9]+$");                 //设置只能输入数字
    QValidator *validator = new QRegExpValidator(re, ui->le_num);
    ui->le_num->setValidator( validator );
    ui->le_sales->setValidator( validator);
    ui->le_age->setValidator(validator);
    ui->le_phone->setValidator(validator);
    ui->le_danhao->setValidator(validator);
    ui->le_num->setMaxLength(10);           //限制长度
    ui->le_danhao->setMaxLength(10);
    ui->le_name->setMaxLength(8);
    ui->le_age->setMaxLength(4);
    ui->le_phone->setMaxLength(12);
    ui->le_sales->setMaxLength(8);
    ui->le_gou->setMaxLength(20);
    QRegExp rer("[0-9,]+$");
    QValidator *yi = new QRegExpValidator(rer, ui->le_gou);
    ui->le_gou->setValidator( yi );
    ui->le_danhao->setFocus();

    setTabOrder(ui->le_danhao,ui->le_num);
    setTabOrder(ui->le_num,ui->le_name);
    setTabOrder(ui->le_name,ui->le_age);
    setTabOrder(ui->le_age,ui->le_phone);
    setTabOrder(ui->le_phone,ui->le_gou);
    setTabOrder(ui->le_gou,ui->le_sales);
    setTabOrder(ui->le_sales,ui->dateEdit);
    setTabOrder(ui->dateEdit,ui->text_address);
}

changecus::~changecus()
{
    delete ui;
}

void changecus::on_pb_cancel_clicked()
{
    this->close();
}

void changecus::on_pushButton_clicked()     //获取信息按钮
{
    danhao=ui->le_danhao->text();
    QString danhao2;
    QString num2;
    QString name2;
    QString sex2;

    QString age;
    QString address;
    QString phone;
    QString zhengzhuang;
    QString gou;
    QString sales;
    QString date;
    QString mark;

    QString sq;
    sq=QString("select * from client where danhao ='%0'").arg(danhao);
    QSqlQuery jiancha;
    jiancha.exec(sq);
    QString number;
    while (jiancha.next())
    {
        danhao2=jiancha.value(0).toString();
        num2=jiancha.value(1).toString();
        name2 = jiancha.value(2).toString();
        sex2 = jiancha.value(3).toString();
        age = jiancha.value(4).toString();
        address = jiancha.value(5).toString();
        phone =jiancha.value(6).toString();
        zhengzhuang =jiancha.value(7).toString();
        gou = jiancha.value(8).toString();
        sales = jiancha.value(9).toString();
        date = jiancha.value(10).toString();
        mark = jiancha.value(11).toString();
        danhao2=danhao2.simplified();
        num2=num2.simplified();
        name2=name2.simplified();
        sex2=sex2.simplified();
        age=age.simplified();
        phone=phone.simplified();
        gou=gou.simplified();
        sales=sales.simplified();


    }

    if(QString(danhao2).isEmpty())     //判断是否存在
    {
        QMessageBox::about(this,"错误","不存在该单号");

        ui->le_num->clear();
        ui->le_age->clear();
        ui->le_sales->clear();
        ui->le_name->clear();
        ui->le_phone->clear();
        ui->le_gou->clear();
        ui->text_mark->clear();
        ui->text_address->clear();
        ui->text_zhengzhuang->clear();
        ui->pb_ok->setDisabled(true);               //不可点击，变灰
    }
    else
    {
        QMessageBox::about(this,"成功","获取成功！");
        ui->le_num->setText(num2);
        ui->le_name->setText(name2);
        ui->le_age->setText(age);
        ui->le_phone->setText(phone);
        ui->le_gou->setText(gou);
        ui->le_sales->setText(sales);
        ui->text_mark->setText(mark);
        ui->text_address->setText(address);
        ui->text_zhengzhuang->setText(zhengzhuang);
        QDateTime time;
        time = QDateTime::fromString(date,"yyyy-MM-dd");        //转换成datetime类
        ui->dateEdit->setDateTime(time);
        if(sex2=="男")
            ui->radioButton->setChecked(true);
        else
            ui->radioButton_2->setChecked(true);
        ui->pb_ok->setDisabled(false);

        num=ui->le_num->text();
        name=ui->le_name->text();
        sex=sex2;
    }
    setTabOrder(ui->pushButton,ui->le_danhao);
    setTabOrder(ui->le_danhao,ui->le_num);
    setTabOrder(ui->le_num,ui->le_name);
    setTabOrder(ui->le_name,ui->le_age);
    setTabOrder(ui->le_age,ui->le_phone);
    setTabOrder(ui->le_phone,ui->le_gou);
    setTabOrder(ui->le_gou,ui->le_sales);
    setTabOrder(ui->le_sales,ui->dateEdit);
    setTabOrder(ui->dateEdit,ui->text_address);

}

void changecus::on_pb_ok_clicked()      //确认修改信息按钮
{
    QString newdan;
    newdan=ui->le_danhao->text();
    QString newnum=ui->le_num->text();
    QString newname=ui->le_name->text();
    QString age=ui->le_age->text();
    QString newsex=ui->sexGroup->checkedButton()->text();
    QString phone=ui->le_phone->text();
    QString gou=ui->le_gou->text();
    QString sales=ui->le_sales->text();
    QString address=ui->text_address->toPlainText();
    QString zhengzhuang=ui->text_zhengzhuang->toPlainText();
    QString mark=ui->text_mark->toPlainText();
    QDateTime time =ui->dateEdit->dateTime();
//    QString date=time.toString("yyyy-MM--dd");

    bool flag1=true;
    bool flag2=true;


    QStringList a;
    QString test =ui->le_gou->text();
    a = test.split(",");    //分解字符串

    QString sqllll;
    sqllll=QString("select mno from medicine");     //先把全部药品编号选出来
    QSqlQuery jiancha;
    jiancha.exec(sqllll);
    QString numbe;
    QStringList list;
    int flag=1;

    while(jiancha.next())
    {
        numbe=jiancha.value(0).toString();             //转到int去掉他的空格，再转会string进行对比
        numbe=numbe.simplified();       //去除多余空格
        list.append(numbe);              //叠在一起
    }

    for(int i=0;i<a.size();i++)
    {
        if(!list.contains(a[i],Qt::CaseSensitive)){             //如果有不存在的编号，flag变为0
            flag=0;
        }
    }

    QString salesnum;
    int salesflag=1;
    QSqlQuery jiansales;
    QString chasales;       //检查是否存在此经办人
    chasales=QString("select ano from agency where ano='%0' ").arg(sales);
    jiansales.exec(chasales);
    while(jiansales.next())
    {
        salesnum=jiansales.value(0).toString();
        salesnum=salesnum.simplified();
    }
    if(QString(salesnum).isEmpty())
    {
        salesflag=0;    //为空，说明不存在该经办人
    }

    if(danhao.length()<1 ||num.length()<1 || name.length()<1 || age.length()<1 || phone.length()<1 || sales.length()<1 || gou.length()<1 || address.length()<1 || zhengzhuang.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查信息是否填写完整。");
    }

    else if(flag==0)
    {
        QMessageBox::about(this,"错误","有不存在的药品编号");
    }
    else if (salesflag==0) {
        QMessageBox::about(this,"错误","不存在该经办人编号");
    }

    else {
    //判断新单号是否存在

    if(newdan!=danhao)          //单号更改的情况      判断新单号是否存在
    {
//        QMessageBox::about(this,"a","不一样噢");
        QString sq;
        sq=QString("select * from client where danhao ='%0'").arg(newdan);     //查询是否存在该单号
        QSqlQuery jiancha;
        jiancha.exec(sq);
        QString number;
        while (jiancha.next())
        {
            number = jiancha.value(0).toString();
        }
        if(!QString(number).isEmpty())     //判断是否存在
        {
            QMessageBox::about(this,"错误","已存在该单号，请重新输入");
            ui->le_danhao->setText(danhao);
            flag1=false;
        }
        else {
            flag1=true;//不存在新单号，可以修改
        }


        if(newnum!=num)         //如果新编号不等于老编号，即是顾客换编号，其他订单也需要一并更改,这里是判断新编号是否存在
        {
            QString sq;
            sq=QString("select * from client where cno ='%0'").arg(newnum);
            QSqlQuery jiancha;
            jiancha.exec(sq);
            QString number;
            while (jiancha.next())
            {
                number = jiancha.value(1).toString();
            }

            if(!QString(number).isEmpty())     //不为空，
            {
                QMessageBox::critical(this,"失败","该编号已存在，请重新输入","OK");
                ui->le_num->setText(num);
                flag2=false;
            }
            else {
                flag2=true;
            }

        }

        if(flag1&&flag2)        //单号和编号都没问题,单号没变，编号姓名性别不管变不变，开始更新数据
        {
            QString sql;
            QSqlQuery geng;
            geng.prepare("update client set danhao=?,cno=?,cname=?,csex=?,cage=?,caddress=?,cphone=?,csymptom=?,mno=?,ano=?,cdate=?,cremark=? where danhao=?");
            geng.addBindValue(newdan);
            geng.addBindValue(newnum);
            geng.addBindValue(newname);
            geng.addBindValue(newsex);
            geng.addBindValue(age);
            geng.addBindValue(address);
            geng.addBindValue(phone);
            geng.addBindValue(zhengzhuang);
            geng.addBindValue(gou);
            geng.addBindValue(sales);
            geng.addBindValue(time);
            geng.addBindValue(mark);
            geng.addBindValue(danhao);
            bool ok=geng.exec();       //更新数据

            if(ok)
            {
                QMessageBox::about(this,"成功","修改成功");
                ui->le_age->clear();
                ui->le_gou->clear();
                ui->le_num->clear();
                ui->le_name->clear();
                ui->le_phone->clear();
                ui->le_sales->clear();
                ui->le_danhao->clear();
                ui->text_mark->clear();
                ui->text_address->clear();
                ui->text_zhengzhuang->clear();
            }

            if(newnum!=num||newname!=name||newsex!=sex)     //改完当前单号，如果编号，名字，性别修改了，其他单号的也要修改
            {
                QString sql;
                QSqlQuery geng;
                geng.prepare("update client set cno=?,cname=?,csex=? where cno=?");
                geng.addBindValue(newnum);
                geng.addBindValue(newname);
                geng.addBindValue(newsex);
                geng.addBindValue(num);
                geng.exec();
            }
        }


    }

    else {                      //单号没改的情况

        if(newnum!=num)         //如果新编号不等于老编号，即是顾客换编号，其他订单也需要一并更改
        {
            QString sq;
            sq=QString("select * from client where cno ='%0'").arg(newnum);
            QSqlQuery jiancha;
            jiancha.exec(sq);
            QString number;
            while (jiancha.next())
            {
                number = jiancha.value(1).toString();
            }

            if(!QString(number).isEmpty())     //不为空，
            {
                QMessageBox::critical(this,"失败","该编号已存在，请重新输入","OK");
                ui->le_num->setText(num);
                flag2=false;
            }
            else {
                flag2=true;
            }

        }
        if(flag1&&flag2)        //单号和编号都没问题,单号没变，编号姓名性别不管变不变，开始更新数据
        {
            QString sql;
            QSqlQuery geng;
            geng.prepare("update client set danhao=?,cno=?,cname=?,csex=?,cage=?,caddress=?,cphone=?,csymptom=?,mno=?,ano=?,cdate=?,cremark=? where danhao=?");
            geng.addBindValue(newdan);
            geng.addBindValue(newnum);
            geng.addBindValue(newname);
            geng.addBindValue(newsex);
            geng.addBindValue(age);
            geng.addBindValue(address);
            geng.addBindValue(phone);
            geng.addBindValue(zhengzhuang);
            geng.addBindValue(gou);
            geng.addBindValue(sales);
            geng.addBindValue(time);
            geng.addBindValue(mark);
            geng.addBindValue(danhao);
            bool ok=geng.exec();       //更新数据

            if(ok)
            {
                QMessageBox::about(this,"成功","修改成功");
                ui->le_age->clear();
                ui->le_gou->clear();
                ui->le_num->clear();
                ui->le_name->clear();
                ui->le_phone->clear();
                ui->le_sales->clear();
                ui->le_danhao->clear();
                ui->text_mark->clear();
                ui->text_address->clear();
                ui->text_zhengzhuang->clear();
            }

            if(newnum!=num||newname!=name||newsex!=sex)     //改完当前单号，如果编号，名字，性别修改了，其他单号的也要修改
            {
                QString sql;
                QSqlQuery geng;
                geng.prepare("update client set cno=?,cname=?,csex=? where cno=?");
                geng.addBindValue(newnum);
                geng.addBindValue(newname);
                geng.addBindValue(newsex);
                geng.addBindValue(num);
                geng.exec();
            }
        }

        //已购药品和经办人信息的修改没有做限制



    }


    }

}
