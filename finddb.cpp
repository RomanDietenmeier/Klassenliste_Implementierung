#include "finddb.h"
#include "ui_finddb.h"
#include<QFileDialog>
#include<QDebug>
#include <stdexcept>

FindDB::FindDB(QWidget *parent, std::string argv) :
    QMainWindow(parent),
    ui(new Ui::FindDB)
{
    ui->setupUi(this);
    qDebug()<<"argv: "<<argv.c_str();
    if(argv.compare("clean")){
        qDebug()<<"clean";
    }else if(argv.compare("test")){
        qDebug()<<"test";
    }
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
    try {
        dao=new KlassenkameradDAO(s.toLocal8Bit().constData());
    }  catch (const std::invalid_argument& e ) {
        qDebug()<<e.what();
        return;
    }

    qt_loginview* loginview;
    loginview=new qt_loginview(NULL,v);
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
    loginview=new qt_loginview(NULL,v);
    this->close();
    loginview->show();
}

