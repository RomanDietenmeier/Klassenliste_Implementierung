#include "newpasswort.h"
#include "ui_newpasswort.h"
#include "KlassenkameradDatensatz.h"
#include <QListWidgetItem>

NewPasswort::NewPasswort(QWidget *parent, KlassenkameradDAO *dao, MainWindow *mw,std::string id) :
    QMainWindow(parent),
    ui(new Ui::NewPasswort)
{
    ui->setupUi(this);
    this->dao= dao;
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
    dao->passwortAendern(ui->np_neuespasswort->text().toStdString(),id);

    this->close();


}


