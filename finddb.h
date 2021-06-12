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
    bool test=false;
    bool clean=false;

public:
    explicit FindDB(QWidget *parent = nullptr, std::string argv="");
    ~FindDB();

private slots:

    void on_pushButton_2_Datei_clicked();

    void on_pushButton_1_DEFAULT_clicked();

private:
    Ui::FindDB *ui;
};

#endif // FINDDB_H
