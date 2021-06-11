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

public:
    explicit FindDB(QWidget *parent = nullptr, Verwaltung *v=NULL);
    ~FindDB();

private slots:

    void on_pushButton_2_Datei_clicked();

    void on_pushButton_1_DEFAULT_clicked();

private:
    Ui::FindDB *ui;
};

#endif // FINDDB_H
