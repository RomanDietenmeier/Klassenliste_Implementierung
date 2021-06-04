#include "finddb.h"
#include "ui_finddb.h"
#include<QFileDialog>
#include<QDebug>

FindDB::FindDB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindDB)
{
    ui->setupUi(this);
}

FindDB::~FindDB()
{
    delete ui;
}



void FindDB::on_pushButton_2_Datei_clicked()
{

    QFileDialog dialog;
    QString s=dialog.getOpenFileName();
    qDebug()<<s;
}

