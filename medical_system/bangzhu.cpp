#include "bangzhu.h"
#include "ui_bangzhu.h"

bangzhu::bangzhu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bangzhu)
{
    ui->setupUi(this);
}

bangzhu::~bangzhu()
{
    delete ui;
}
