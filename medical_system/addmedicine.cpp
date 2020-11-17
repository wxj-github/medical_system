#include "addmedicine.h"
#include "ui_addmedicine.h"
#include <QString>
#include <QMessageBox>
#include <QButtonGroup>
#include <QSqlQuery>
#include <QMessageBox>
#include <QRegExp>

addmedicine::addmedicine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmedicine)
{
    ui->setupUi(this);
    QRegExp re("[0-9]+$");                 //设置只能输入数字
    QValidator *validator = new QRegExpValidator(re, ui->le_num);
    ui->le_num->setValidator( validator );
    ui->le_num->setMaxLength(12);
    ui->le_name->setMaxLength(50);
    ui->le_num->setFocus();

    setTabOrder(ui->le_num,ui->le_name);
    setTabOrder(ui->le_name,ui->textEdit);


}



addmedicine::~addmedicine()
{
    delete ui;
}

void addmedicine::on_pbt_addmedi_cancel_clicked()   //点击取消，关闭添加药品信息窗口
{
    ui->le_num->clear();
    ui->le_name->clear();
    ui->textEdit->clear();
    this->close();

}

void addmedicine::on_pbt_addmedi_ok_clicked()       //添加信息按钮
{
    QString num = this->ui->le_num->text();
    QString name = this->ui->le_name->text();
    QString sex = this->ui->fangfaGroup->checkedButton()->text();    //获取按钮信息
    QString gongxiao = this->ui->textEdit->toPlainText();

    if(num.length()<1 || name.length()<1  || gongxiao.length()<1)
    {
        QMessageBox::critical(this,"错误","请检查信息是否填写完整。");
    }

    else {
        QString sqll;
        sqll=QString("select mno from medicine where mno ='%0'").arg(num);              //检查编号是否存在
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
            sql=QString("INSERT INTO medicine (mno,mname,mmode,mefficacy)" "VALUES ('%1','%2','%3','%4')").arg(num).arg(name).arg(sex).arg(gongxiao);
            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {
                QMessageBox::about(this,"成功","添加成功!");
                ui->le_num->clear();
                ui->le_name->clear();
                ui->textEdit->clear();
            }

        }
        else {
            QMessageBox::about(this,"失败","该编号已存在");
        }
    }
}

void addmedicine::on_textEdit_textChanged()        //限制最大字符数
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
