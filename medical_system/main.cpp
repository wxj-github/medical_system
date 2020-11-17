#include "mainwindow.h"
#include <QApplication>
#include "login.h"

#include <QSql>                     //数据库所需
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>





bool OpenDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
     //    qDebug()<<"ODBC driver?"<<db.isValid();      //不知道有什么用？？
    QString dsn = QString::fromLocal8Bit("medi");      //数据源名称
    db.setHostName("10.85.5.32");                        //选择本地主机
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("xinjian");                               //登录用户
    db.setPassword("xinjian");                              //密码

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库
//    db.setDatabaseName("note.db"); //创建一个note.db的文件存储数据

    if(!db.open())                                      //打开数据库
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    else    {
        qDebug()<<"database open success!";
    }
    return true;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!OpenDatabase())
    {
        return false;
    }
    login q;
    q.exec();
//    MainWindow w;
//    w.show();

    qApp->exit(0);       //不添加，不会真正关闭进程
    return a.exec();
}
