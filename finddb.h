#ifndef FINDDB_H
#define FINDDB_H

#include <QMainWindow>
#include"KlassenkameradDAO.h"
#include"qt_loginview.h"

namespace Ui {
class FindDB;
}

class FindDB : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* dao=NULL;
    Verwaltung *v;
    bool test=false;
    bool clean=false;

public:
    explicit FindDB(QWidget *parent = nullptr, std::string argv="");
    ~FindDB();

private slots:
    /**
     * @brief FindDB::on_pushButton_2_Datei_clicked
     * Versucht Datenbank Datei einzulesen und geht dann weiter zum Loginfenster oder je nach Parameter
     * löscht sie die Datenbank oder füllt sie mit Testeinträgen
     */
    void on_pushButton_2_Datei_clicked();
    /**
     * @brief FindDB::on_pushButton_1_DEFAULT_clicked
     * Gleich wie die andere Funktion, zusätzlich legt sie eine Datei an wenn keine existiert
     */
    void on_pushButton_1_DEFAULT_clicked();

private:
    Ui::FindDB *ui;
};

#endif // FINDDB_H
