#include "firststart.h"
#include "ui_firststart.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>
#include<QDebug>

firstStart::firstStart(QWidget *parent, KlassenkameradDAO *dao, MainWindow *mw) :
    QMainWindow(parent),
    ui(new Ui::firstStart)
{
    ui->setupUi(this);
    this->dao= dao;
    this->mw= mw;
}

firstStart::~firstStart()
{
    delete ui;
}

void firstStart::on_ho_telefon_textChanged(const QString &arg1)
{
    ui->ho_plusTelefon->setEnabled(true);
}


void firstStart::on_ho_plusTelefon_clicked()
{
    ui->ho_telefonliste->addItem(ui->ho_telefon->text());

}


void firstStart::on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}


void firstStart::on_ho_anlegen_clicked()
{
    KlassenkameradDatensatz hauptorganisator;
    hauptorganisator.vorname = ui->ho_vorname->text().toStdString();
    hauptorganisator.nachname[0] = ui->ho_nachname->text().toStdString();
    hauptorganisator.nachname[1] = ui->ho_nachname2->text().toStdString();
    hauptorganisator.eMail = ui->ho_email->text().toStdString();
    hauptorganisator.adresse.strasse = ui->ho_strasse->text().toStdString();
    hauptorganisator.adresse.hausnummer = ui->ho_hausnr->text().toStdString();
    hauptorganisator.adresse.ort = ui->ho_ort->text().toStdString();
    hauptorganisator.adresse.plz = ui->ho_plz->text().toStdString();
//    PASSWORT ABSPEICHERN HIER HIN = ui->ho_passwort->text().toStdString();
//    MASTERPASSWORT ABSPEICHERN HIER HIN = ui->ho_masterpasswort->text().toStdString();


    for (int i=0;i<ui->ho_telefonliste->count() ;i++ ) {
        hauptorganisator.telefonnummer.push_back(ui->ho_telefonliste->item(i)->text().toStdString());
    }


    //dao->einfuegen(&hauptorganisator, "0");
    if(dao->einfuegen_HauptO(&hauptorganisator,ui->ho_passwort->text().toStdString(),ui->ho_masterpasswort->text().toStdString())){
        qDebug()<<"HO erfolg";
    }else{
        qDebug()<<"HO misslungen";
    }
    hauptorganisator.printToConsole();

    this->close();
    mw->show();
    mw->on_pushButton_3_clicked();


}




