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
    void on_ho_telefon_textChanged(const QString &arg1);

    void on_ho_plusTelefon_clicked();

    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);

    void on_ho_anlegen_clicked();

private:
    Ui::klassenkamerad_einfuegen *ui;
};

#endif // KLASSENKAMERAD_EINFUEGEN_H
