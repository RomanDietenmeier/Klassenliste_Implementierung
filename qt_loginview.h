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
    /**
     * @brief qt_loginview::qt_loginview
     * öffnet loginview
     * @param parent
     * @param v
     */
   explicit qt_loginview(QWidget *parent = nullptr, Verwaltung *v=NULL);
    ~qt_loginview();

private slots:
    /**
     * @brief qt_loginview::on_loginbutton_clicked
     * überprüft eingegebene Logindaten und meldet sich entsprechend erfolgreich oder nicht erfolgreich oder, bei zu vielen Falschversuchen wird der Benutzer gespert.
     */
    void on_loginbutton_clicked();
    /**
     * @brief qt_loginview::on_emailEingabe_textChanged
     * ermöglicht nach eingabe in Email_Textfeld den Loginbutton
     * @param arg1
     */
    void on_emailEingabe_textChanged(const QString &arg1);
    /**
     * @brief qt_loginview::on_passwortEingabe_textChanged
     * ermöglicht nach eingabe in PW-Textfeld den Loginbutton
     * @param arg1
     */
    void on_passwortEingabe_textChanged(const QString &arg1);

private:
    Ui::qt_loginview *ui;
};

#endif // QT_LOGINVIEW_H
