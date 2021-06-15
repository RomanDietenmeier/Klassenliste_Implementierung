#include "firststart.h"
#include "ui_firststart.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>
#include<QDebug>

firstStart::firstStart(QWidget *parent, Verwaltung* p_v) :
    QMainWindow(parent),
    ui(new Ui::firstStart)
{
    ui->setupUi(this);
    this->dao= p_v->m_KlassenkameradDAO;
    this->v=p_v;
}

firstStart::~firstStart()
{
    delete ui;
}
/**
 * @brief firstStart::on_ho_telefon_textChanged
 * Aktiviert plus Button nachdem eine Nummer ins Feld geschrieben wurde
 * @param arg1
 */
void firstStart::on_ho_telefon_textChanged(const QString &arg1)
{
    ui->ho_plusTelefon->setEnabled(true);
}

/**
 * @brief firstStart::on_ho_plusTelefon_clicked
 * Fügt Telefonnummer der Liste hinzu
 */
void firstStart::on_ho_plusTelefon_clicked()
{
    ui->ho_telefonliste->addItem(ui->ho_telefon->text());

}

/**
 * @brief firstStart::on_ho_telefonliste_itemDoubleClicked
 * Löscht Nummer aus Liste durch einen Doppelklick
 * @param item
 */
void firstStart::on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

/**
 * @brief firstStart::on_ho_anlegen_clicked
 * Speichert den Hauptorganisator in die Datenbank/in den Datensatz und aktualisiert
 * die Datenbank danach
 */
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
    v->akteurID=hauptorganisator.klassenkameradID;

    this->close();
    MainWindow* mw=new MainWindow(nullptr,v);
    mw->show();
    mw->on_pushButton_3_clicked();
    delete this;


}




