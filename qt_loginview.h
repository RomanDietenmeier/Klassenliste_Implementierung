#ifndef QT_LOGINVIEW_H
#define QT_LOGINVIEW_H

#include <QMainWindow>

namespace Ui {
class qt_loginview;
}

class qt_loginview : public QMainWindow
{
    Q_OBJECT

public:
    explicit qt_loginview(QWidget *parent = nullptr);
    ~qt_loginview();

private slots:
    void on_loginbutton_clicked();

private:
    Ui::qt_loginview *ui;
};

#endif // QT_LOGINVIEW_H
