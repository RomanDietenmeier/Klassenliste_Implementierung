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
    Verwaltung *v;
    MainWindow *mw;
    std::string id;

public:
    explicit NewPasswort(QWidget *parent = nullptr, Verwaltung* v=NULL, MainWindow *mw=NULL,string pw=NULL, string mail=NULL);
    ~NewPasswort();

private slots:
    void on_np_speichernButton_clicked();

    void on_np_neuespasswort_textChanged(const QString &arg1);

private:
    Ui::NewPasswort *ui;
};

#endif // NEWPASSWORT_H
