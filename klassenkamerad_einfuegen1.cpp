#include "klassenkamerad_einfuegen.h"
#include "ui_klassenkamerad_einfuegen.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>

klassenkamerad_einfuegen::klassenkamerad_einfuegen(QWidget *parent, KlassenkameradDAO *dao) :
    QMainWindow(parent),
    ui(new Ui::klassenkamerad_einfuegen)
{
    ui->setupUi(this);
    this->dao= dao;
}

klassenkamerad_einfuegen::~klassenkamerad_einfuegen()
{
    delete ui;
}

void klassenkamerad_einfuegen::on_ho_telefon_textChanged(const QString &arg1)
{
    ui->ho_plusTelefon->setEnabled(true);
}


void klassenkamerad_einfuegen::on_ho_plusTelefon_clicked()
{
    ui->ho_telefonliste->addItem(ui->ho_telefon->text());

}


void klassenkamerad_einfuegen::on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}


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


}

