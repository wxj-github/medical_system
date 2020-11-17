#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmedicine.h"

#include <QMovie>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_3->setScaledContents(true);
    QMovie *movie = new QMovie("C:\\Users\\Administrator\\Desktop\\医药管理图片\\timg (1).gif");
    ui->label_3->setMovie(movie);
    movie->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_addmedi_triggered()
{
//    addmedicine h;     //创建一个添加药品信息类，打开就是一个新窗口，不用clear
    h.show();      //弹出添加药品信息界面
}

void MainWindow::on_action_addsales_triggered()
{
    j.show();      //弹出添加经办人信息界面
}

void MainWindow::on_action_addcus_triggered()
{
    k.show();   //弹出添加顾客信息界面
}

void MainWindow::on_action_readsales_triggered()
{
    l.show();   //弹出浏览经办人信息界面
}

void MainWindow::on_action_readcus_triggered()
{
    m.show();   //弹出浏览顾客信息界面
}

void MainWindow::on_action_readmedi_triggered()
{
    n.show();   //弹出浏览药品信息界面
}

void MainWindow::on_action_xiugaimedi_triggered()
{
    o.show();   //弹出修改药品信息界面
}

void MainWindow::on_action_xiugaisales_triggered()
{
    p.show();   //弹出修改经办人信息界面
}

void MainWindow::on_action_xiugaicus_triggered()
{
    q.show();   //弹出修改顾客信息界面
}

void MainWindow::on_action_findmedi_triggered()
{
    r.show();   //弹出查询药品信息界面
}

void MainWindow::on_action_findsales_triggered()
{
    s.show();   //弹出查询经办人信息界面
}

void MainWindow::on_action_findcus_triggered()
{
    t.show();   //弹出查询顾客信息界面
}


void MainWindow::on_action_delectcus_triggered()
{
    u.show();       //弹出删除顾客信息界面
}

void MainWindow::on_action_delectmedi_triggered()
{
    v.show();       //弹出删除药品信息界面
}

void MainWindow::on_action_delectsales_triggered()
{
    w.show();       //弹出删除经办人信息界面
}

void MainWindow::on_action_gaimima_triggered()
{
    x.show();       //弹出修改密码界面

}

void MainWindow::on_action_baobiao_triggered()
{
    z.show();       //弹出报表界面
}

void MainWindow::on_action_tianjia_triggered()
{
    aa.show();      //弹出添加账户
}

void MainWindow::on_action_shanaccount_triggered()
{
    bb.show();      //弹出删除账户
}

void MainWindow::on_action_2_triggered()
{
    cc.show();      //弹出帮助
}
