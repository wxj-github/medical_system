#include "addsales.h"
#include "ui_addsales.h"
#include <QRegExp>
#include <QButtonGroup>
#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
addsales::addsales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsales)
{
    ui->setupUi(this);
    ui->le_num->setFocus();
    QRegExp re("[0-9]+$");                 //设置只能输入数字
    QValidator *validator = new QRegExpValidator(re, ui->le_num);
    ui->le_num->setValidator(validator);
    ui->le_phone->setValidator(validator);
    ui->le_num->setMaxLength(8);            //设置限定长度
    ui->le_name->setMaxLength(8);
    ui->le_phone->setMaxLength(12);


}

addsales::~addsales()
{
    delete ui;
}

void addsales::on_pushButton_2_clicked()       //点击取消，关闭添加经办人信息窗口
{
    this->close();
    ui->le_num->clear();
    ui->le_name->clear();
    ui->le_phone->clear();
    ui->textEdit->clear();
}




void addsales::on_pushButton_clicked()        //添加信息按钮
{
    QString num = this->ui->le_num->text();         //获取文本框信息
    QString name = this->ui->le_name->text();
    QString sex = this->ui->sexgroup->checkedButton()->text();
    QString phone = this->ui->le_phone->text();
    QString mark = this->ui->textEdit->toPlainText();

    if(num.length()<1 ||name.length()<1 || phone.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查信息是否填写完整。");
    }
    else {
        QString sqll;
        sqll=QString("select ano from agency where ano ='%0'").arg(num);              //检查编号是否存在
        QSqlQuery cha;
        cha.exec(sqll);
        QString number;
        while (cha.next())
        {
            number = cha.value(0).toString();
        }

        if(QString(number).isEmpty())
        {
            QString sql;
            sql=QString("INSERT INTO agency (ano,aname,asex,aphone,aremark)" "VALUES ('%1','%2','%3','%4','%5')").arg(num).arg(name).arg(sex).arg(phone).arg(mark);
            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                QMessageBox::about(this,"成功","添加成功!");
                ui->le_num->clear();
                ui->le_name->clear();
                ui->le_phone->clear();
                ui->textEdit->clear();
            }
        }

        else {
            QMessageBox::about(this,"失败","该编号已存在");
        }
    }
}

void addsales::on_textEdit_textChanged()            //限定文本框字符数
{
    QString textContent = ui->textEdit->toPlainText();
        int length = textContent.count();
        int maxLength = 50; // 最大字符数
        if(length > maxLength) {
            int position = ui->textEdit->textCursor().position();
            QTextCursor textCursor = ui->textEdit->textCursor();
            textContent.remove(position-(length-maxLength), length-maxLength);
            ui->textEdit->setText(textContent);
            textCursor.setPosition(position-(length-maxLength));
            ui->textEdit->setTextCursor(textCursor);
        }
}
