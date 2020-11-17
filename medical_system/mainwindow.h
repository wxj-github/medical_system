#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addmedicine.h"
#include "addsales.h"
#include "addcus.h"
#include "readsales.h"
#include "readcus.h"
#include "readmedi.h"
#include "changemedi.h"
#include "changesales.h"
#include "changecus.h"
#include "findmedi.h"
#include "findsales.h"
#include "findcus.h"
#include "deletecus.h"
#include "deletemedi.h"
#include "deletesales.h"
#include "xiugaimima.h"
#include "baobiao.h"
#include "tianjiayonghu.h"
#include "shanchuyonghu.h"
#include "bangzhu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_addmedi_triggered();

    void on_action_addsales_triggered();

    void on_action_addcus_triggered();

    void on_action_readsales_triggered();

    void on_action_readcus_triggered();

    void on_action_readmedi_triggered();

    void on_action_xiugaimedi_triggered();

    void on_action_xiugaisales_triggered();

    void on_action_xiugaicus_triggered();

    void on_action_findmedi_triggered();

    void on_action_findsales_triggered();

    void on_action_findcus_triggered();

    void on_action_delectcus_triggered();

    void on_action_delectmedi_triggered();

    void on_action_delectsales_triggered();

    void on_action_gaimima_triggered();

    void on_action_baobiao_triggered();

    void on_action_tianjia_triggered();

    void on_action_shanaccount_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    addsales j;     //添加经办人信息窗口类
    addcus k;       //添加顾客信息窗口类
    addmedicine h;   //添加药品信息类
    readsales l;    //添加阅读经办人信息窗口类
    readcus m;      //添加阅读顾客信息窗口类
    readmedi n;     //添加阅读药品信息窗口类
    changemedi o;   //添加修改药品信息窗口类
    changesales p;   //添加修改经办人信息窗口类
    changecus q;    //添加修改顾客信息窗口类
    findmedi r;     //添加查询药品信息窗口类
    findsales s;      //添加查询经办人信息窗口类
    findcus t;      //添加查询顾客信息窗口类
    deletecus u;    //添加删除顾客信息窗口类
    deletemedi v;   //添加删除药品信息窗口类
    deletesales w;  //添加删除经办人信息窗口类
    xiugaimima x;   //添加修改密码类
    baobiao z;      //添加报表类
    tianjiayonghu aa;   //添加账户类
    shanchuyonghu bb;   //添加删除类
    bangzhu cc;     //添加帮助
};

#endif // MAINWINDOW_H
