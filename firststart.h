#ifndef FIRSTSTART_H
#define FIRSTSTART_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "KlassenkameradDAO.h"
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
    void on_ho_telefon_textChanged(const QString &arg1);

    void on_ho_plusTelefon_clicked();

    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);

    void on_ho_anlegen_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_ho_passwort_textChanged(const QString &arg1);

private:
    Ui::firstStart *ui;
};

#endif // FIRSTSTART_H
