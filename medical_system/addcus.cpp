#include "addcus.h"
#include "ui_addcus.h"
#include <QRegExp>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
#include <QStringList>
addcus::addcus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcus)
{
    ui->setupUi(this);
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

    QDate nowtime;                  //获取当前时间，并显示
    nowtime=QDate::currentDate();
    ui->dateEdit->setDate(nowtime);

    setTabOrder(ui->le_danhao,ui->le_num);
    setTabOrder(ui->le_num,ui->le_name);
    setTabOrder(ui->le_name,ui->le_age);
    setTabOrder(ui->le_age,ui->le_phone);
    setTabOrder(ui->le_phone,ui->le_gou);
    setTabOrder(ui->le_gou,ui->le_sales);
    setTabOrder(ui->le_sales,ui->dateEdit);
    setTabOrder(ui->dateEdit,ui->text_address);




}

addcus::~addcus()
{
    delete ui;
}

void addcus::on_text_zhengzhuang_textChanged()              //设置文本框最大限度
{
    QString textContent = ui->text_zhengzhuang->toPlainText();
        int length = textContent.count();
        int maxLength = 50; // 最大字符数
        if(length > maxLength) {
            int position = ui->text_zhengzhuang->textCursor().position();
            QTextCursor textCursor = ui->text_zhengzhuang->textCursor();
            textContent.remove(position-(length-maxLength), length-maxLength);
            ui->text_zhengzhuang->setText(textContent);
            textCursor.setPosition(position-(length-maxLength));
            ui->text_zhengzhuang->setTextCursor(textCursor);
        }
}

void addcus::on_text_address_textChanged()          //设置文本框最大限度
{
    QString textContent = ui->text_address->toPlainText();
        int length = textContent.count();
        int maxLength = 50; // 最大字符数
        if(length > maxLength) {
            int position = ui->text_address->textCursor().position();
            QTextCursor textCursor = ui->text_address->textCursor();
            textContent.remove(position-(length-maxLength), length-maxLength);
            ui->text_address->setText(textContent);
            textCursor.setPosition(position-(length-maxLength));
            ui->text_address->setTextCursor(textCursor);
        }
}

void addcus::on_text_mark_textChanged()             //设置文本框最大限度
{
    QString textContent = ui->text_mark->toPlainText();
        int length = textContent.count();
        int maxLength = 50; // 最大字符数
        if(length > maxLength) {
            int position = ui->text_mark->textCursor().position();
            QTextCursor textCursor = ui->text_mark->textCursor();
            textContent.remove(position-(length-maxLength), length-maxLength);
            ui->text_mark->setText(textContent);
            textCursor.setPosition(position-(length-maxLength));
            ui->text_mark->setTextCursor(textCursor);
        }
}

void addcus::on_pb_cancel_clicked()
{
    this->close();
    ui->le_danhao->clear();
    ui->le_age->clear();
    ui->le_gou->clear();
    ui->le_num->clear();
    ui->le_name->clear();
    ui->le_phone->clear();
    ui->le_sales->clear();
    ui->text_mark->clear();
    ui->text_address->clear();
    ui->text_zhengzhuang->clear();

}

void addcus::on_pb_ok_clicked()         //添加信息按钮
{
    QString danhao=ui->le_danhao->text();
    QString num=ui->le_num->text();
    QString name=ui->le_name->text();
    QString sex = this->ui->sexGroup->checkedButton()->text();
    QString age=ui->le_age->text();
    QString phone=ui->le_phone->text();
    QString sales=ui->le_sales->text();
    QString gou=ui->le_gou->text();
    QString address=ui->text_address->toPlainText();
    QString zhengzhuang=ui->text_zhengzhuang->toPlainText();
    QString mark=ui->text_mark->toPlainText();
    QDateTime shijian;
    shijian=ui->dateEdit->dateTime();
    QString time=shijian.toString("yyyy-MM-dd");   //获取时间并转换为string格式


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
//          QMessageBox::critical(this,"错误","不存在药品编号"+a[i]);
            flag=0;
        }
    }


    if(danhao.length()<1 ||num.length()<1 || name.length()<1 || age.length()<1 || phone.length()<1 || sales.length()<1 || gou.length()<1 || address.length()<1 || zhengzhuang.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查信息是否填写完整。");
    }
    else {
//        QString sqll;
//        sqll=QString("select cno from client where cno ='%0'").arg(num);              //检查顾客编号是否存在
        QSqlQuery cha;
//        cha.exec(sqll);
//        QString number;
//        while (cha.next())
//        {
//            number = cha.value(0).toString();
//        }

        QString sqlll;
        sqlll=QString("select ano from agency where ano='%0'").arg(sales);      //检查经办人编号是否存在
        cha.exec(sqlll);
        QString numberr;
        while(cha.next())
        {
            numberr = cha.value(0).toString();
        }




        if((!QString(numberr).isEmpty()) && flag==1)   //判断是否存在顾客编号和经办人编号
        {
            QString sql;
            sql=QString("insert into client (danhao,cno,cname,csex,cage,caddress,cphone,csymptom,mno,ano,cdate,cremark)"
                        "VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12')")
                    .arg(danhao).arg(num).arg(name).arg(sex).arg(age).arg(address).arg(phone).arg(zhengzhuang).arg(gou).arg(sales).arg(time).arg(mark);

            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                QMessageBox::about(this,"成功","添加成功!");
                ui->le_danhao->clear();
                ui->le_age->clear();
                ui->le_gou->clear();
                ui->le_num->clear();
                ui->le_name->clear();
                ui->le_phone->clear();
                ui->le_sales->clear();
                ui->text_mark->clear();
                ui->text_address->clear();
                ui->text_zhengzhuang->clear();
            }
        }
        else {

            if(QString(numberr).isEmpty()){
                QMessageBox::about(this,"失败","该经办人编号不存在");}
             else if(flag==0){
                QMessageBox::critical(this,"失败","有不存在的药品编号噢");}
        }
    }
}



void addcus::on_le_danhao_editingFinished()
{
    QString danhao=ui->le_danhao->text();                        //获取单号，判断单号是否存在，存在则跳出警告

    QString sqll;
    sqll=QString("select danhao from client where danhao ='%0'").arg(danhao);              //检查单号是否存在
    QSqlQuery cha;
    cha.exec(sqll);
    QString number;
    while (cha.next())
    {
        number = cha.value(0).toString();
    }

    if(!QString(number).isEmpty())          //不为空，单号存在
    {
        QMessageBox::critical(this,"错误","该单号已存在！请重新输入！","确定");
        ui->le_danhao->setFocus();
        ui->pb_ok->setDisabled(true);               //不可点击，变灰
    }
    else {
        ui->pb_ok->setDisabled(false);
    }
}

void addcus::on_le_num_editingFinished()
{
    QString num=ui->le_num->text();                 //获取编号，若存在，自动补充其他信息，不存在着不操作
    QString name;
    QString sex;
    QString age;
    QString address;
    QString phone;
    QString sqll;
    sqll=QString("select cno,cname,csex,cage,caddress,cphone from client where cno ='%0'").arg(num);              //检查单号是否存在
    QSqlQuery cha;
    cha.exec(sqll);


    QString number;
    while (cha.next())
    {
        number = cha.value(0).toString();
        name = cha.value(1).toString();
        sex = cha.value(2).toString();
        age = cha.value(3).toString();
        address = cha.value(4).toString();
        phone = cha.value(5).toString();
    }

    if(!QString(number).isEmpty())          //不为空，编号号存在
    {
        QMessageBox::about(this," ","检测到该顾客，已为您自动补齐个人信息");
        ui->le_name->setText(name);
        ui->le_name->setDisabled(true);    //锁定不给更改
        ui->le_age->setText(age);
        if(sex=="男"){
            ui->radioButton->setChecked(true);

            ui->radioButton_2->setCheckable(false);     //性别不可更改

        }

        else
        {
            ui->radioButton_2->setChecked(true);
            ui->radioButton->setCheckable(false);
        }


        ui->text_address->setText(address);
        ui->le_phone->setText(phone);
//        ui->pb_ok->setDisabled(true);               //不可点击，变灰
    }
    else {
         ui->radioButton->setCheckable(true);
         ui->radioButton_2->setCheckable(true);
        ui->le_name->setDisabled(false);
        ui->le_name->clear();
        ui->le_age->clear();
        ui->text_address->clear();
        ui->le_phone->clear();
    }


}
