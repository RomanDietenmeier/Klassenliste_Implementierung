#ifndef QT_LOGINVIEW_H
#define QT_LOGINVIEW_H

#include"mainwindow.h"
#include <QMainWindow>
#include"KlassenkameradDAO.h"
#include"Verwaltung.h"


namespace Ui {
class qt_loginview;
}

class qt_loginview : public QMainWindow
{
    Q_OBJECT
    bool emailBoolean = false;
    bool passwortBoolean = false;
    KlassenkameradDAO *dao;
    Verwaltung* v;

public:
   explicit qt_loginview(QWidget *parent = nullptr, Verwaltung *v=NULL);
    ~qt_loginview();

private slots:
    void on_loginbutton_clicked();

    void on_emailEingabe_textChanged(const QString &arg1);

    void on_passwortEingabe_textChanged(const QString &arg1);

private:
    Ui::qt_loginview *ui;
};

#endif // QT_LOGINVIEW_H
