#ifndef QT_LOGINVIEW_H
#define QT_LOGINVIEW_H

#include <QMainWindow>

namespace Ui {
class qt_loginview;
}

class qt_loginview : public QMainWindow
{
    Q_OBJECT
    std::string probe_email = "Max@Mustermann.de";
    std::string probe_passwort = "123";
    bool emailBoolean = false;
    bool passwortBoolean = false;

public:
    explicit qt_loginview(QWidget *parent = nullptr);
    ~qt_loginview();

private slots:
    void on_loginbutton_clicked();

    void on_emailEingabe_textChanged(const QString &arg1);

    void on_passwortEingabe_textChanged(const QString &arg1);

private:
    Ui::qt_loginview *ui;
};

#endif // QT_LOGINVIEW_H
