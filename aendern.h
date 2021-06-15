#ifndef AENDERN_H
#define AENDERN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "KlassenkameradDAO.h"
#include "mainwindow.h"
#include "KlassenkameradDatensatz.h"

namespace Ui {
class Aendern;
}

class Aendern : public QMainWindow
{
    Q_OBJECT
	KlassenkameradDAO* dao;
    MainWindow* mw;
    KlassenkameradDatensatz* kd;

public:
    explicit Aendern(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL, KlassenkameradDatensatz* kd=NULL);
    ~Aendern();

private slots:
    /**
     * @brief Aendern::on_ho_telefon_textChanged
     * Sobald in das Telefonfenster was geschrieben wird, wird der + Button aktivierbar
     * @param arg1
     */
    void on_ho_telefon_textChanged(const QString &arg1);
    /**
     * @brief Aendern::on_ho_plusTelefon_clicked
     * Telefonnummern werden in die Liste eingetragen
     */
    void on_ho_plusTelefon_clicked();
    /**
     * @brief Aendern::on_ho_telefonliste_itemDoubleClicked
     * Doppelklick um eine Telefonnummer aus der Liste zu entfernen
     * @param item
     */
    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);
    /**
     * @brief Aendern::on_ho_anlegen_clicked
     * Geänderte Daten werden in den Datensatz gespeichert (hauptorganisator ist noch der Name von dem Ursprung der Funktion)
     * Anschließend wird das Hauptfenster wieder angezeigt
     */
    void on_ho_anlegen_clicked();




private:
    Ui::Aendern *ui;
};

#endif // AENDERN_H
