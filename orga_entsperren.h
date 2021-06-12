#ifndef ORGA_ENTSPERREN_H
#define ORGA_ENTSPERREN_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QTime>

namespace Ui {
class Orga_entsperren;
}

class Orga_entsperren : public QMainWindow
{
    Q_OBJECT
	KlassenkameradDAO* dao;
    MainWindow* mw;
    KlassenkameradDatensatz* ds;

public:
    explicit Orga_entsperren(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL, KlassenkameradDatensatz *ds=NULL);
    ~Orga_entsperren();
private slots:
    void on_organisator_verteilen_clicked();

private:
    Ui::Orga_entsperren *ui;
};

#endif // ORGA_ENTSPERREN_H
