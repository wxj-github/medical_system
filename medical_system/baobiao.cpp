#include "baobiao.h"
#include "ui_baobiao.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringList>
#include <QScreen>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QPrintPreviewDialog>

baobiao::baobiao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baobiao)
{
    ui->setupUi(this);
//    ui->lineEdit->setFocus();
    ui->pushButton->setFocus();

    ui->progressBar->setVisible(false);
    QDate nowtime;                  //获取当前时间，并显示
    nowtime=QDate::currentDate();
    ui->dateEdit_2->setDate(nowtime);

    QRegExp re("[0-9]+$");
    QValidator *validator = new QRegExpValidator(re, ui->lineEdit);
    ui->lineEdit->setValidator( validator );        //限制只能输入数字
    QDate shijian;
    QDate shijian2;
    shijian=ui->dateEdit->date();
    shijian2=ui->dateEdit_2->date();
    QString time=shijian.toString("yyyy-MM-dd");
    QString time2=shijian2.toString("yyyy-MM-dd");

    QString sql=QString("select distinct cno from client where cdate >= '%0' and cdate <='%1' " ).arg(time).arg(time2);
    QSqlQuery jiancha;
    jiancha.exec(sql);
    int count=0;
    int count2=0;
    while(jiancha.next())
    {
        count++;
    }

    QString sqll=QString("select cno from client where cdate >= '%0' and cdate <='%1'").arg(time).arg(time2);
    jiancha.exec(sqll);

    while(jiancha.next())
    {
        count2++;
    }

    QString sqlll=QString("select * from agency ");
    jiancha.exec(sqlll);
    int salesnum=0;
    while(jiancha.next())
    {
        salesnum++;
    }
    ui->lcdNumber->display(count);
    ui->lcdNumber_2->display(count);
    ui->lcdNumber_3->display(count2);
    ui->lcdNumber_4->display(salesnum);


    //经办人信息报表
    QString s=QString("select distinct ano from client");
    jiancha.exec(s);
    QStringList a;
    int k=0;
    QString b;
    while(jiancha.next())
    {
        b=jiancha.value(0).toString();
        b=b.simplified();
        a.append(b);
        k++;
    }

    int largeren;       //最多次数的经办人
    int largenum;       //最多的次数
    int sum2=0;

    if(k!=0)
    {
        largeren=0;
        largenum=0;
         for(int i=0;i<a.size();i++)
         {
              QString ss=QString("select ano from client where ano ='%0' ").arg(a[i]);
              jiancha.exec(ss);
              while(jiancha.next())
              {
                  sum2++;
              }

              if(largenum<sum2)
              {
                  largenum=sum2;
                  largeren=i;
              }
              sum2=0;

         }
         QString sss=QString("select aname from agency where ano ='%0' ").arg(a[largeren]);
         jiancha.exec(sss);
         QString name;
         while(jiancha.next())
         {
             name=jiancha.value(0).toString();
         }
         ui->lineEdit_2->setText(a[largeren]);
         ui->lcdNumber_5->display(largenum);
         ui->lineEdit_3->setText(name);

    }


    //药品信息报表
    QString q=QString("select mno from medicine");
    jiancha.exec(q);
    QStringList aa;
    QString yaohao;
    int yaoshu=0; //药品数量
    while(jiancha.next())
    {
        yaohao=jiancha.value(0).toString();
        yaohao=yaohao.simplified();
        aa.append(yaohao);
        yaoshu++;
    }

    ui->lcdNumber_6->display(yaoshu);

    int largeyao;       //出售次数最多的药品
    int largeshu;           //最多的次数
    int jishu=0;        //计数
    int zongshu=0;      //总药品出售次数
    if(yaoshu!=0)
    {
        largeyao=0;
        largeshu=0;
        for(int i=0;i<aa.size();i++)
        {
            QString qq=QString(("select *from client where mno ='%0' "
                                "UNION select* from client where CHARINDEX(',%0,',mno)>0 "
                                "UNION select* from client where  mno like '%0,%'"
                                "UNION select* from client where CHARINDEX(',%0 ',mno)>0")).arg(aa[i]);
            jiancha.exec(qq);
            while(jiancha.next())
            {
                   jishu++;
                   zongshu++;
            }
            if(largeshu<jishu)
            {
                largeshu=jishu;
                largeyao=i;
            }
            jishu=0;
        }

        QString qqq=QString("select mname from medicine where mno = '%0'").arg(aa[largeyao]);
        jiancha.exec(qqq);
        QString yaoname;
        while(jiancha.next())
        {
            yaoname=jiancha.value(0).toString();
        }
        ui->lineEdit_4->setText(aa[largeyao]);
        ui->lineEdit_5->setText(yaoname);
        ui->lcdNumber_7->display(largeshu);
        ui->lcdNumber_8->display(zongshu);


    }

}

baobiao::~baobiao()
{
    delete ui;
}



void baobiao::on_dateEdit_dateChanged(const QDate &date)
{
    QDate shijian=date;
    QDate shijian2=ui->dateEdit_2->date();
    QString time=shijian.toString("yyyy-MM-dd");
    QString time2=shijian2.toString("yyyy-MM-dd");
    QString chaonum=ui->lineEdit->text();
    int shumu=chaonum.toInt();

    QString sql=QString("select distinct cno from client where cdate >='%0' and cdate <='%1'").arg(time).arg(time2);

    QSqlQuery jiancha;
    QSqlQuery cha;
    jiancha.exec(sql);
    int count=0;
    int count2=0;
    int count3=0;   //超过x次的人数
    QString cno;
    while(jiancha.next())           //从超过这个时间的人里开始检查它的次数
    {
        count++;
        cno=jiancha.value(0).toString();
        cno=cno.simplified();       //把cno全部取出来，一个个检查
        QStringList a;
        a.append(cno);
        for(int i=0;i<a.size();i++)
        {
            QString sqll=QString("select * from client where cno ='%0' and cdate>= '%1' and cdate <='%2' ").arg(a[i]).arg(time).arg(time2);
            cha.exec(sqll);
            while(cha.next())
            {
                count2++;
            }
        }
        if(count2>=shumu){
            count3++;
        }
        count2=0;

    }

    int count4=0;
    QString sqlll=QString("select cno from client where cdate >= '%0' and cdate <='%1'").arg(time).arg(time2);
    jiancha.exec(sqlll);
    while(jiancha.next())
    {
        count4++;
    }
    ui->lcdNumber->display(count);
    ui->lcdNumber_2->display(count3);
    ui->lcdNumber_3->display(count4);


    QString s=QString("select distinct ano from client");
    jiancha.exec(s);
    QStringList a;
    int k=0;
    QString b;
    while(jiancha.next())
    {
        b=jiancha.value(0).toString();
        b=b.simplified();
        a.append(b);
        k++;
    }

    int largeren;       //最多次数的经办人
    int largenum;       //最多的次数
    int sum2=0;

    if(k!=0)
    {
        largeren=0;
        largenum=0;
         for(int i=0;i<a.size();i++)
         {
              QString ss=QString("select ano from client where ano ='%0' ").arg(a[i]);
              jiancha.exec(ss);
              while(jiancha.next())
              {
                  sum2++;
              }

              if(largenum<sum2)
              {
                  largenum=sum2;
                  largeren=i;
              }
              sum2=0;

         }
         QString sss=QString("select aname from agency where ano ='%0' ").arg(a[largeren]);
         jiancha.exec(sss);
         QString name;
         while(jiancha.next())
         {
             name=jiancha.value(0).toString();
         }

         ui->lineEdit_2->setText(a[largeren]);
         ui->lineEdit_3->setText(name);
         ui->lcdNumber_5->display(largenum);

    }


    //药品信息报表
    QString q=QString("select mno from medicine");
    jiancha.exec(q);
    QStringList aa;
    QString yaohao;
    int yaoshu=0; //药品数量
    while(jiancha.next())
    {
        yaohao=jiancha.value(0).toString();
        yaohao=yaohao.simplified();
        aa.append(yaohao);
        yaoshu++;
    }

    ui->lcdNumber_6->display(yaoshu);

    int largeyao;       //出售次数最多的药品
    int largeshu;           //最多的次数
    int jishu=0;        //计数
    if(yaoshu!=0)
    {
        largeyao=0;
        largeshu=0;
        for(int i=0;i<aa.size();i++)
        {
            QString qq=QString(("select *from client where mno ='%0' "
                                "UNION select* from client where CHARINDEX(',%0,',mno)>0 "
                                "UNION select* from client where  mno like '%0,%'"
                                "UNION select* from client where CHARINDEX(',%0 ',mno)>0")).arg(aa[i]);
            jiancha.exec(qq);
            while(jiancha.next())
            {
                   jishu++;
            }
            if(largeshu<jishu)
            {
                largeshu=jishu;
                largeyao=i;
            }
            jishu=0;
        }

        QString qqq=QString("select mname from medicine where mno = '%0'").arg(aa[largeyao]);
        jiancha.exec(qqq);
        QString yaoname;
        while(jiancha.next())
        {
            yaoname=jiancha.value(0).toString();
        }
        ui->lineEdit_4->setText(aa[largeyao]);
        ui->lineEdit_5->setText(yaoname);
        ui->lcdNumber_7->display(largeshu);


    }


}

void baobiao::on_lineEdit_textChanged(const QString &arg1)
{
    QDate shijian=ui->dateEdit->date();
    QDate shijian2=ui->dateEdit_2->date();
    QString time=shijian.toString("yyyy-MM-dd");
    QString time2=shijian2.toString("yyyy-MM-dd");
    QString chaonum=arg1;
    int shumu=chaonum.toInt();

    QString sql=QString("select distinct cno from client where cdate >='%0' and cdate <='%1'").arg(time).arg(time2);

    QSqlQuery jiancha;
    QSqlQuery cha;
    jiancha.exec(sql);
    int count=0;
    int count2=0;
    int count3=0;   //超过x次的人数
    QString cno;
    while(jiancha.next())           //从超过这个时间的人里开始检查它的次数
    {
        count++;
        cno=jiancha.value(0).toString();
        cno=cno.simplified();       //把cno全部取出来，一个个检查
        QStringList a;
        a.append(cno);
        for(int i=0;i<a.size();i++)
        {
            QString sqll=QString("select * from client where cno ='%0' and cdate>= '%1' and cdate <='%2' ").arg(a[i]).arg(time).arg(time2);
            cha.exec(sqll);
            while(cha.next())
            {
                count2++;
            }
        }
        if(count2>=shumu){
            count3++;
        }
        count2=0;

    }

    int count4=0;
    QString sqlll=QString("select cno from client where cdate >= '%0' and cdate <='%1'").arg(time).arg(time2);
    jiancha.exec(sqlll);
    while(jiancha.next())
    {
        count4++;
    }
    ui->lcdNumber->display(count);
    ui->lcdNumber_2->display(count3);
    ui->lcdNumber_3->display(count4);
}

void baobiao::on_dateEdit_2_dateChanged(const QDate &date)
{
    QDate shijian=ui->dateEdit->date();
    QDate shijian2=date;
    QString time=shijian.toString("yyyy-MM-dd");
    QString time2=shijian2.toString("yyyy-MM-dd");
    QString chaonum=ui->lineEdit->text();
    int shumu=chaonum.toInt();

    QString sql=QString("select distinct cno from client where cdate >='%0' and cdate <='%1'").arg(time).arg(time2);

    QSqlQuery jiancha;
    QSqlQuery cha;
    jiancha.exec(sql);
    int count=0;
    int count2=0;
    int count3=0;   //超过x次的人数
    QString cno;
    while(jiancha.next())           //从超过这个时间的人里开始检查它的次数
    {
        count++;
        cno=jiancha.value(0).toString();
        cno=cno.simplified();       //把cno全部取出来，一个个检查
        QStringList a;
        a.append(cno);
        for(int i=0;i<a.size();i++)
        {
            QString sqll=QString("select * from client where cno ='%0' and cdate>= '%1' and cdate <='%2' ").arg(a[i]).arg(time).arg(time2);
            cha.exec(sqll);
            while(cha.next())
            {
                count2++;
            }
        }
        if(count2>=shumu){
            count3++;
        }
        count2=0;

    }

    int count4=0;
    QString sqlll=QString("select cno from client where cdate >= '%0' and cdate <='%1'").arg(time).arg(time2);
    jiancha.exec(sqlll);
    while(jiancha.next())
    {
        count4++;
    }
    ui->lcdNumber->display(count);
    ui->lcdNumber_2->display(count3);
    ui->lcdNumber_3->display(count4);
}

void baobiao::on_pushButton_clicked()
{
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
        for(int i=0;i<101;i++)
          {
            for(int j=0;j<666666;j++)
              ui->progressBar->setValue(i);
          }
    ui->progressBar->setVisible(false);


        QPrinter printer_pixmap;
        QFileDialog fileDialog;
        QString str = QFileDialog::getSaveFileName(this,tr("Save Text"),"/",tr("Text Files (*.pdf)"));
//        printer_pixmap.setOutputFormat(QPrinter::PdfFormat);
        if( str.isEmpty() )
            return;
        printer_pixmap.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf
        printer_pixmap.setPageSize(QPrinter::A4);  //设置纸张大小为A4
        printer_pixmap.setOutputFileName(str);

//        printer_pixmap.setOutputFileName("E:\\test_pixmap.pdf");   //设置输出路径

        QPixmap pixmap = QPixmap::grabWidget(this, 0,0,740,940);  //获取界面的图片


        QPainter painter_pixmap;
        painter_pixmap.begin(&printer_pixmap);
        QRect rect = painter_pixmap.viewport();
        int multiple = rect.width()/pixmap.width();
        painter_pixmap.scale(multiple, multiple); //将图像(所有要画的东西)在pdf上放大multiple-1倍
        painter_pixmap.drawPixmap(110, 230, pixmap);  //画图
        painter_pixmap.end();

//        QPixmap pixmap = QPixmap::grabWidget(this);
//        pixmap.save("E:/myScreen2.png", "png");    //生成图片并保存


}
