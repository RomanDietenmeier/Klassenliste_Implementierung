#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"KlassenkameradDatensatz.h"
#include"KlassenkameradDAO.h"
#include <QColumnView>
#include"finddb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Verwaltung* v;
    KlassenkameradDAO* kDAO;
    KlassenkameradDatensatz* kd;
    std::vector<KlassenkameradDatensatz*> Datensatze;

public:
    MainWindow(QWidget *parent = nullptr,Verwaltung* v=NULL);
    ~MainWindow();

    /**
     * @brief MainWindow::printDatensatze
     * Gibt die Datensätze aus
     */
     void printDatensatze();
public slots:

     /**
      * @brief on_pushButton_3_clicked
      * Gibt die Datenbank aus
      */
    void on_pushButton_3_clicked();

    /**
     * @brief MainWindow::sortierenID
     * Sortiert zuvor angelegte Datensätze nach der ID
     */
    void sortierenID();

    /**
     * @brief MainWindow::on_pushButton_clicked
     * Gesperrte Organisatoren anzeigen
     */
    void on_pushButton_clicked();

private slots:

    //void on_pushButton_4_clicked();

    //void on_pushButton_5_clicked();

    /**
     * @brief MainWindow::on_pushButton_6_clicked
     * Ändert einen zuvor ausgewählten Eintrag. Es MUSS ein Klassenkamerad ausgewählt werden um einen Eintrag zu ändern.
     * Wenn der ausgewählte Eintrag nicht änderbar ist, bekommt man die Mitteilung "nicht änderbar"
     */
    void on_pushButton_6_clicked();

    /**
     * @brief MainWindow::on_pushButton_8_hist_clicked
     * Zeigt die Änderungshistorie eines zuvor ausgewählten Klassenkameraden an.
     */
    void on_pushButton_8_hist_clicked();

    /**
     * @brief MainWindow::on_pushButton_8_db_clicked
     * Ausloggen aus der derzeitigen Datenbank
     */
    void on_pushButton_8_db_clicked();

    void on_LoginView_clicked();

    //void on_ho_anlegen_clicked();

    /**
     * @brief MainWindow::on_einfuegen_clicked
     * Erstellt einen neuen Klassenkameraden und öffnet dazu ein neues Fenster wo alle Einträge angegeben werden
     */
    void on_einfuegen_clicked();

    /**
     * @brief MainWindow::on_neuesPasswortButton_clicked
     * Vergibt ein neues Passwort
     */
    void on_neuesPasswortButton_clicked();

    /**
     * @brief MainWindow::on_loeschenButton_clicked
     * Löscht einen bereits existierenden Eintrag.
     * Eintrag nur löschbar, wenn zuvor ein gültiger Eintrag ausgewählt wurde.
     */
    void on_loeschenButton_clicked();

    /**
     * @brief MainWindow::on_pushButton_Organisatoren_clicked
     * Zeigt alle Klassenkameraden an, die derzeit einen Organisatorenstatus besitzen
     */
    void on_pushButton_Organisatoren_clicked();

    /**
     * @brief MainWindow::on_PushButtonRemoveOrganisator_clicked
     * Entnimmt einem Klassenkameraden die Organisatorrechte.
     * Nur möglich, wenn Klassenkamerad zuvor Organisatorrechte besitzt.
     */
    void on_PushButtonRemoveOrganisator_clicked();

    /**
     * @brief MainWindow::on_tableWidget_cellClicked
     * Aktiviert den Button_6 wenn die ausgewählte Reihe nicht die Reihe 0 ist.
     * @param row
     * @param column
     */
    void on_tableWidget_cellClicked(int row, int column);

    /**
     * @brief MainWindow::on_OrganisatorErteilenButton_clicked
     * Zuvor ausgewählter Klassenkamerad bekommt Organisatorrechte.
     * Nur möglich, wenn der Klassenkamerad nicht bereits Organisator ist.
     */
    void on_OrganisatorErteilenButton_clicked();

    /**
     * @brief MainWindow::on_pushButton_entsperren_clicked
     * Organisatoren entsperren.
     * Nur möglich, wenn Organisator bereits gesperrt ist.
     */
    void on_pushButton_entsperren_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
