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
    if(dao!=NULL){
        delete dao;
        dao=NULL;
    }

    QFileDialog dialog;
    QString s=dialog.getOpenFileName();
    dao=new KlassenkameradDAO(s.toLocal8Bit().constData());
    qt_loginview* loginview;
    loginview=new qt_loginview(NULL,dao);
    this->close();
    loginview->show();
}


void FindDB::on_pushButton_1_DEFAULT_clicked()
{
    if(dao!=NULL){
        delete dao;
        dao=NULL;
    }
    dao=new KlassenkameradDAO("./hohoho.db");
    qt_loginview* loginview;
    loginview=new qt_loginview(NULL,dao);
    this->close();
    loginview->show();
}

