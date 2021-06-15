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


/**
 * @brief FindDB::on_pushButton_2_Datei_clicked
 * Versucht Datenbank Datei einzulesen und geht dann weiter zum Loginfenster oder je nach Parameter
 * löscht sie die Datenbank oder füllt sie mit Testeinträgen
 */
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
        ui->label_error->setText("Datenbank Datei auswählen oder Standard auswählen!");
        return;
    }
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
        this->close();
        firstStart* HOanlegen=new firstStart(nullptr,dao,new MainWindow(nullptr,v));
        HOanlegen->show();
        delete this;
    }

    if(showLogin){
        qt_loginview* loginview;
        loginview=new qt_loginview(NULL,v);
        this->close();
        loginview->show();
        delete this;
    }

}

/**
 * @brief FindDB::on_pushButton_1_DEFAULT_clicked
 * Gleich wie die andere Funktion, zusätzlich legt sie eine Datei an wenn keine existiert
 */
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
        this->close();
        firstStart* HOanlegen=new firstStart(nullptr,dao,new MainWindow(nullptr,v));
        HOanlegen->show();
        delete this;
    }

    if(showLogin){
        qt_loginview* loginview;
        loginview=new qt_loginview(NULL,v);
        this->close();
        loginview->show();
        delete this;
    }
}

