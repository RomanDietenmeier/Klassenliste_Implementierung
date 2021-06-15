#ifndef FIRSTSTART_H
#define FIRSTSTART_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"



namespace Ui {
class firstStart;
}

class firstStart : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* dao;
    MainWindow* mw;

public:
    explicit firstStart(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL);
    ~firstStart();

private slots:
    /**
     * @brief firstStart::on_ho_telefon_textChanged
     * Aktiviert plus Button nachdem eine Nummer ins Feld geschrieben wurde
     * @param arg1
     */
    void on_ho_telefon_textChanged(const QString &arg1);
    /**
     * @brief firstStart::on_ho_plusTelefon_clicked
     * Fügt Telefonnummer der Liste hinzu
     */
    void on_ho_plusTelefon_clicked();
    /**
     * @brief firstStart::on_ho_telefonliste_itemDoubleClicked
     * Löscht Nummer aus Liste durch einen Doppelklick
     * @param item
     */
    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);
    /**
     * @brief firstStart::on_ho_anlegen_clicked
     * Speichert den Hauptorganisator in die Datenbank/in den Datensatz und aktualisiert
     * die Datenbank danach
     */
    void on_ho_anlegen_clicked();

private:
    Ui::firstStart *ui;
};

#endif // FIRSTSTART_H
