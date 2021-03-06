#include "aendern.h"
#include "ui_aendern.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>

Aendern::Aendern(QWidget *parent, KlassenkameradDAO *dao, MainWindow *mw, KlassenkameradDatensatz *kd) :
    QMainWindow(parent),
    ui(new Ui::Aendern)
{
    ui->setupUi(this);
	this->dao= dao;
    this->mw= mw;
    this->kd= kd;

    //In unser Fenster werden die vorhandenen Daten eingelesen zum aendern
    ui->ho_vorname->setText(kd->vorname.c_str());
    ui->ho_nachname->setText(kd->nachname[0].c_str());
    ui->ho_nachname2->setText(kd->nachname[1].c_str());
    ui->ho_email->setText(kd->eMail.c_str());
    ui->ho_strasse->setText(kd->adresse.strasse.c_str());
    ui->ho_hausnr->setText(kd->adresse.hausnummer.c_str());
    ui->ho_ort->setText(kd->adresse.ort.c_str());
    ui->ho_plz->setText(kd->adresse.plz.c_str());

    for (unsigned long long i=0;i<kd->telefonnummer.size();i++ ) {

        ui->ho_telefonliste->addItem(kd->telefonnummer[i].c_str());
    }
}

Aendern::~Aendern()
{
    delete ui;
}
/**
 * @brief Aendern::on_ho_telefon_textChanged
 * Sobald in das Telefonfenster was geschrieben wird, wird der + Button aktivierbar
 * @param arg1
 */
void Aendern::on_ho_telefon_textChanged(const QString &arg1)
{
    ui->ho_plusTelefon->setEnabled(true);
}

/**
 * @brief Aendern::on_ho_plusTelefon_clicked
 * Telefonnummern werden in die Liste eingetragen
 */
void Aendern::on_ho_plusTelefon_clicked()
{
    ui->ho_telefonliste->addItem(ui->ho_telefon->text());

}

/**
 * @brief Aendern::on_ho_telefonliste_itemDoubleClicked
 * Doppelklick um eine Telefonnummer aus der Liste zu entfernen
 * @param item
 */
void Aendern::on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

/**
 * @brief Aendern::on_ho_anlegen_clicked
 * Geänderte Daten werden in den Datensatz gespeichert (hauptorganisator ist noch der Name von dem Ursprung der Funktion)
 * Anschließend wird das Hauptfenster wieder angezeigt
 */
void Aendern::on_ho_anlegen_clicked()
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
    hauptorganisator.klassenkameradID=kd->klassenkameradID;



    for (int i=0;i<ui->ho_telefonliste->count() ;i++ ) {
        hauptorganisator.telefonnummer.push_back(ui->ho_telefonliste->item(i)->text().toStdString());
    }

    dao->aktualisieren(&hauptorganisator, "0");
    hauptorganisator.printToConsole();

    this->close();
    mw->show();
    //Die Funktion aktualisiert die Einträge nach der Änderung (-> siehe mainwindow)
    mw->on_pushButton_3_clicked();


}

