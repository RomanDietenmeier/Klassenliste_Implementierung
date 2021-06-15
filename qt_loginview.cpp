#include "qt_loginview.h"
#include "ui_qt_loginview.h"
#include <QDebug>
#include "mainwindow.h"
#include "newpasswort.h"
#include "ui_newpasswort.h"
/*boolean wait_for_init(){


}*/


/**
 * @brief qt_loginview::qt_loginview
 * öffnet loginview
 * @param parent
 * @param v
 */
qt_loginview::qt_loginview(QWidget *parent, Verwaltung *v) :
    QMainWindow(parent),
    ui(new Ui::qt_loginview)
{
    ui->setupUi(this);
    this->v = v;

}



/**
 * @brief qt_loginview::~qt_loginview
 * schließt ui
 */
qt_loginview::~qt_loginview()
{
    delete ui;
}


/**
 * @brief qt_loginview::on_emailEingabe_textChanged
 * ermöglicht nach eingabe in Email_Textfeld den Loginbutton
 * @param arg1
 */
void qt_loginview::on_emailEingabe_textChanged(const QString &arg1)
{
    //Hier ist die Email die eingegeben wird
    emailBoolean = true;
    if (emailBoolean && passwortBoolean){
        ui->loginbutton->setEnabled(true);
    }
}

/**
 * @brief qt_loginview::on_passwortEingabe_textChanged
 * ermöglicht nach eingabe in PW-Textfeld den Loginbutton
 * @param arg1
 */
void qt_loginview::on_passwortEingabe_textChanged(const QString &arg1)
{
    passwortBoolean = true;
    if (emailBoolean && passwortBoolean){
        ui->loginbutton->setEnabled(true);
    }
}

/**
 * @brief qt_loginview::on_loginbutton_clicked
 * überprüft eingegebene Logindaten und meldet sich entsprechend erfolgreich oder nicht erfolgreich oder, bei zu vielen Falschversuchen wird der Benutzer gespert.
 */
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
        MainWindow *mainwindow = new MainWindow(nullptr,v);
        this->close();
        mainwindow->show();
    }else if(login==-1){
        qDebug()<<"nicht Erfolgreich";
    }else if(login==-2){
        qDebug()<<"Benutzer gesperrt";
    }else if(login==-3){
        NewPasswort *newPW = new NewPasswort(NULL,v, NULL,loginPasswort.toStdString(),loginEmail.toStdString());
        newPW->show();
        this->close();
    }




}
