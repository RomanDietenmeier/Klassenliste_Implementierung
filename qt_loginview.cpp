#include "qt_loginview.h"
#include "ui_qt_loginview.h"
#include <QDebug>
#include "mainwindow.h"
#include "newpasswort.h"
#include "ui_newpasswort.h"
/*boolean wait_for_init(){


}*/



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



void qt_loginview::on_emailEingabe_textChanged(const QString &arg1)
{
    //Hier ist die Email die eingegeben wird
    emailBoolean = true;
    if (emailBoolean && passwortBoolean){
        ui->loginbutton->setEnabled(true);
    }
}


void qt_loginview::on_passwortEingabe_textChanged(const QString &arg1)
{
    passwortBoolean = true;
    if (emailBoolean && passwortBoolean){
        ui->loginbutton->setEnabled(true);
    }
}

void qt_loginview::on_loginbutton_clicked()
{
    //Hier in Loginbutton
    QString loginEmail = ui->emailEingabe->text();
    QString loginPasswort = ui->passwortEingabe->text();

    qDebug()<< "Login mit Email: "+loginEmail+ " und Passwort: " +loginPasswort;

    int login = v->anmelden(loginEmail.toStdString(),loginPasswort.toStdString());
    if (login==0){
        qDebug()<<"Erfolgreich";
        //MainWindow aufrufen
        MainWindow *mainwindow = new MainWindow();
        this->close();
        mainwindow->show();
    }else if(login==-1){
        qDebug()<<"nicht Erfolgreich";
    }else if(login==-2){
        qDebug()<<"Benutzer gesperrt";
    }else if(login==-3){
        NewPasswort *newPW = new NewPasswort(NULL,v, NULL);
        newPW->show();
    }



}
