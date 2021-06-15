#ifndef ORGANISATOR_ERSTELLEN_H
#define ORGANISATOR_ERSTELLEN_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QTime>

namespace Ui {
class Organisator_erstellen;
}

class Organisator_erstellen : public QMainWindow
{
    Q_OBJECT
    KlassenkameradDAO* dao;
    MainWindow* mw;
    KlassenkameradDatensatz* ds;

public:
    /**
     * @brief Organisator_erstellen::Organisator_erstellen
     * @param parent
     * @param dao
     * @param mw
     * @param ds
     */
    explicit Organisator_erstellen(QWidget *parent = nullptr, KlassenkameradDAO* dao=NULL, MainWindow *mw=NULL, KlassenkameradDatensatz *ds=NULL);
    /**
     * @brief Organisator_erstellen::~Organisator_erstellen
     */
    ~Organisator_erstellen();


private slots:
    /**
     * @brief Organisator_erstellen::on_organisator_verteilen_clicked
     * verteilt organisator typ
     */
    void on_organisator_verteilen_clicked();


private:
    Ui::Organisator_erstellen *ui;
};

#endif // ORGANISATOR_ERSTELLEN_H
