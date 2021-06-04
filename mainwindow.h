#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"KlassenkameradDAO.h"
#include"KlassenkameradDatensatz.h"
#include <QColumnView>
#include"datensatzbearbeiten.h"
#include"finddb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* kDAO;
    KlassenkameradDatensatz* kd;
    std::vector<KlassenkameradDatensatz*> Datensatze;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_hist_clicked();

    void on_pushButton_8_db_clicked();

    void on_LoginView_clicked();

    void on_ho_anlegen_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
