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
    void printDatensatze();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void init();
public slots:
    void on_pushButton_3_clicked();
private slots:

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_hist_clicked();

    void on_pushButton_8_db_clicked();

    void on_LoginView_clicked();

    void on_ho_anlegen_clicked();

    void on_einfuegen_clicked();

    void on_neuesPasswortButton_clicked();

    void on_loeschenButton_clicked();

    void on_pushButton_Organisatoren_clicked();

    void on_PushButtonRemoveOrganisator_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
