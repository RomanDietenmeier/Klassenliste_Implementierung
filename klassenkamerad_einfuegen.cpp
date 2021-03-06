#include "klassenkamerad_einfuegen.h"
#include "ui_klassenkamerad_einfuegen.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>

klassenkamerad_einfuegen::klassenkamerad_einfuegen(QWidget *parent, KlassenkameradDAO *dao, MainWindow *mw) :
    QMainWindow(parent),
    ui(new Ui::klassenkamerad_einfuegen)
{
    ui->setupUi(this);
    this->dao= dao;
    this->mw= mw;
}

klassenkamerad_einfuegen::~klassenkamerad_einfuegen()
{
    delete ui;
}
/**
 * @brief klassenkamerad_einfuegen::on_ho_telefon_textChanged
 * Aktiviert plus Button nachdem eine Nummer ins Feld geschrieben wurde
 * @param arg1
 */
void klassenkamerad_einfuegen::on_ho_telefon_textChanged(const QString &arg1)
{
    ui->ho_plusTelefon->setEnabled(true);
}

/**
 * @brief klassenkamerad_einfuegen::on_ho_plusTelefon_clicked
 * Fügt Telefonnummer der Liste hinzu
 */
void klassenkamerad_einfuegen::on_ho_plusTelefon_clicked()
{
    ui->ho_telefonliste->addItem(ui->ho_telefon->text());

}

/**
 * @brief klassenkamerad_einfuegen::on_ho_telefonliste_itemDoubleClicked
 * Löscht Nummer aus Liste durch einen Doppelklick
 * @param item
 */
void klassenkamerad_einfuegen::on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

/**
 * @brief klassenkamerad_einfuegen::on_ho_anlegen_clicked
 * Speichert den geänderten Klassenkamerad in die Datenbank/in den Datensatz und aktualisiert
 * die Datenbank danach
 */
void klassenkamerad_einfuegen::on_ho_anlegen_clicked()
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


    for (int i=0;i<ui->ho_telefonliste->count() ;i++ ) {
        hauptorganisator.telefonnummer.push_back(ui->ho_telefonliste->item(i)->text().toStdString());
    }


    dao->einfuegen(&hauptorganisator, "0");
    hauptorganisator.printToConsole();

    this->close();
    mw->show();
    mw->on_pushButton_3_clicked();
}
