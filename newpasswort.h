#ifndef NEWPASSWORT_H
#define NEWPASSWORT_H

#include <QMainWindow>
#include "KlassenkameradDAO.h"
#include "mainwindow.h"

namespace Ui {
class NewPasswort;
}

class NewPasswort : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* dao;
    MainWindow* mw;

public:
    explicit NewPasswort(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL);
    ~NewPasswort();

private slots:
    void on_np_speichernButton_clicked();

    void on_np_neuespasswort_textChanged(const QString &arg1);

private:
    Ui::NewPasswort *ui;
};

#endif // NEWPASSWORT_H