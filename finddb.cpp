#include "finddb.h"
#include "ui_finddb.h"
#include<QFileDialog>
#include<QDebug>
#include <stdexcept>
#include"firststart.h"

FindDB::FindDB(QWidget *parent, std::string argv) :
    QMainWindow(parent),
    ui(new Ui::FindDB)
{
    ui->setupUi(this);
    qDebug()<<"argv: "<<argv.c_str();
    if(argv.compare("clean")==0){
        qDebug()<<"clean";
        clean=true;
    }else if(argv.compare("test")==0){
        qDebug()<<"test";
        test=true;
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
    v=new Verwaltung();
    v->m_KlassenkameradDAO=dao;

    if(test){
        dao->test();
    }
    bool showLogin=true;
    if(clean|| dao->initial){
        showLogin=false;
        dao->initial=false;
        dao->clean();

        firstStart* HOanlegen=new firstStart(nullptr,dao,new MainWindow(nullptr,v));
        HOanlegen->show();
    }

    if(showLogin){
        qt_loginview* loginview;
        loginview=new qt_loginview(NULL,v);
        this->close();
        loginview->show();
    }

}


void FindDB::on_pushButton_1_DEFAULT_clicked()
{
    if(dao!=NULL){
        delete dao;
        dao=NULL;
    }
    dao=new KlassenkameradDAO("./hohoho.db");
    v=new Verwaltung();
    v->m_KlassenkameradDAO=dao;
    if(test){
        dao->test();
    }
    bool showLogin=true;
    if(clean|| (dao->initial&& !test)){
        showLogin=false;
        dao->initial=false;
        dao->clean();
        firstStart* HOanlegen=new firstStart(nullptr,dao,new MainWindow(nullptr,v));
        HOanlegen->show();
    }

    if(showLogin){
        qt_loginview* loginview;
        loginview=new qt_loginview(NULL,v);
        this->close();
        loginview->show();
    }
}

