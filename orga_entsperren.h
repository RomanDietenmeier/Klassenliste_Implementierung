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
    /**
     * @brief Orga_entsperren::Orga_entsperren
     * @param parent
     * @param dao
     * @param mw
     * @param ds
     */
    explicit Orga_entsperren(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL, KlassenkameradDatensatz *ds=NULL);
    /**
     * @brief Orga_entsperren::~Orga_entsperren schliessen
     */
    ~Orga_entsperren();
private slots:
    /**
     * @brief Orga_entsperren::on_organisator_verteilen_clicked
     * entsperrt Organisator oder meldet falls nicht möglich
     */
    void on_organisator_verteilen_clicked();

private:
    Ui::Orga_entsperren *ui;
};

#endif // ORGA_ENTSPERREN_H
