#ifndef KLASSENKAMERAD_EINFUEGEN1_H
#define KLASSENKAMERAD_EINFUEGEN1_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "KlassenkameradDAO.h"

namespace Ui {
class klassenkamerad_einfuegen;
}

class klassenkamerad_einfuegen : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* dao;

public:
    explicit klassenkamerad_einfuegen(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL);
    ~klassenkamerad_einfuegen();

private slots:
    void on_ho_telefon_textChanged(const QString &arg1);

    void on_ho_plusTelefon_clicked();

    void on_ho_telefonliste_itemDoubleClicked(QListWidgetItem *item);

    void on_ho_anlegen_clicked();

private:
    Ui::klassenkamerad_einfuegen *ui;
};

#endif // FIRSTSTART_H
