#include "newpasswort.h"
#include "ui_newpasswort.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>
#include <QDebug>


NewPasswort::NewPasswort(QWidget *parent, Verwaltung *v, MainWindow *mw) :

    QMainWindow(parent),
    ui(new Ui::NewPasswort)
{
    ui->setupUi(this);
    this->v = v;
    this->mw= mw;
    this->id=id;
}

NewPasswort::~NewPasswort()
{
    delete ui;
}

void NewPasswort::on_np_neuespasswort_textChanged(const QString &arg1)
{
    ui->np_speichernButton->setEnabled(true);
}

void NewPasswort::on_np_speichernButton_clicked()
{
    //wo wird pw gespeichert
    if(!v->passwortAendern(ui->np_neuespasswort->text().toStdString())){
        qDebug()<<"Fehler bei Passwortänderung";
    }else {
        MainWindow *mainwindow = new MainWindow();
        this->close();
        mainwindow->show();
        this->close();
    }
}


