#include "qt_loginview.h"
#include "ui_qt_loginview.h"
#include <QDebug>

qt_loginview::qt_loginview(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qt_loginview)
{
    ui->setupUi(this);
}

qt_loginview::~qt_loginview()
{
    delete ui;
}

void qt_loginview::on_loginbutton_clicked()
{
    //Hier in Loginbutton
    qDebug()<<"test";
}

