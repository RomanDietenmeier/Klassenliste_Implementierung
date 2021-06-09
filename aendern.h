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
    void on_ho_telefon_textChanged(const QString &arg1);

    void on_ho_plusTelefon_clicked();

    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);

    void on_ho_anlegen_clicked();




private:
    Ui::Aendern *ui;
};

#endif // AENDERN_H
