#ifndef KLASSENKAMERAD_EINFUEGEN_H
#define KLASSENKAMERAD_EINFUEGEN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "KlassenkameradDAO.h"
#include "mainwindow.h"

namespace Ui {
class klassenkamerad_einfuegen;
}

class klassenkamerad_einfuegen : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* dao;
    MainWindow* mw;

public:
    explicit klassenkamerad_einfuegen(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL);
    ~klassenkamerad_einfuegen();

private slots:
    /**
     * @brief klassenkamerad_einfuegen::on_ho_telefon_textChanged
     * Aktiviert plus Button nachdem eine Nummer ins Feld geschrieben wurde
     * @param arg1
     */
    void on_ho_telefon_textChanged(const QString &arg1);
    /**
     * @brief klassenkamerad_einfuegen::on_ho_plusTelefon_clicked
     * Fügt Telefonnummer der Liste hinzu
     */
    void on_ho_plusTelefon_clicked();
    /**
     * @brief klassenkamerad_einfuegen::on_ho_telefonliste_itemDoubleClicked
     * Löscht Nummer aus Liste durch einen Doppelklick
     * @param item
     */
    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);
    /**
     * @brief klassenkamerad_einfuegen::on_ho_anlegen_clicked
     * Speichert den geänderten Klassenkamerad in die Datenbank/in den Datensatz und aktualisiert
     * die Datenbank danach
     */
    void on_ho_anlegen_clicked();

private:
    Ui::klassenkamerad_einfuegen *ui;
};

#endif // KLASSENKAMERAD_EINFUEGEN_H
