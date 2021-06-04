#include "datensatzbearbeiten.h"
#include "ui_datensatzbearbeiten.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<iostream>



DatensatzBearbeiten::DatensatzBearbeiten(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatensatzBearbeiten)
{
    ui->setupUi(this);
    kDAO=new KlassenkameradDAO("hohoho.db");
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("ID")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(tr("Vorname")));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tr("Nachname")));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(tr("2. Nachname")));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem(tr("E-Mail")));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(tr("Telefon")));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem(tr("Straße")));
    ui->tableWidget->setItem(0,7,new QTableWidgetItem(tr("Hausnummer")));
    ui->tableWidget->setItem(0,8,new QTableWidgetItem(tr("Ort")));
    ui->tableWidget->setItem(0,9,new QTableWidgetItem(tr("PLZ")));
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 100);
    ui->tableWidget->setColumnWidth(3, 100);
    ui->tableWidget->setColumnWidth(4, 200);
    ui->tableWidget->setColumnWidth(5, 100);
    ui->tableWidget->setColumnWidth(6, 150);
    ui->tableWidget->setColumnWidth(7, 100);
    ui->tableWidget->setColumnWidth(8, 100);
    ui->tableWidget->setColumnWidth(9, 100);





}

DatensatzBearbeiten::~DatensatzBearbeiten()
{
    delete ui;
}


void DatensatzBearbeiten::on_pushButton_clicked()
{
    this->close();
}


void DatensatzBearbeiten::on_pushButton_2_clicked()
{
    this->close();
}


void DatensatzBearbeiten::on_pushButton_3_clicked()
{
    std::vector<KlassenkameradDatensatz*> ds;
        kDAO->klassenkameradenLaden(ds);
        Datensatze=ds;
        ui->tableWidget->setRowCount(ds.size()+1);



        auto Items = ui->tableWidget->selectedItems();
        for(int i = 0; i<Items.size(); i++)
        {
            qDebug()<<Items.at(i)->row();
        }







        for(int i = 0; i < ds.size(); i++)
        {
            ui->tableWidget->setItem(1,0,new QTableWidgetItem(tr(ds[i]->klassenkameradID.c_str())));
            ui->tableWidget->setItem(1,1,new QTableWidgetItem(tr(ds[i]->vorname.c_str())));
            ui->tableWidget->setItem(1,2,new QTableWidgetItem(tr(ds[i]->nachname[0].c_str())));
            ui->tableWidget->setItem(1,3,new QTableWidgetItem(tr(ds[i]->nachname[1].c_str())));
            ui->tableWidget->setItem(1,4,new QTableWidgetItem(tr(ds[i]->eMail.c_str())));
            ui->tableWidget->setItem(1,5,new QTableWidgetItem(tr((ds[i]->telefonnummer.size()>0)?ds[i]->telefonnummer[0].c_str():"-")));
            ui->tableWidget->setItem(1,6,new QTableWidgetItem(tr(ds[i]->adresse.strasse.c_str())));
            ui->tableWidget->setItem(1,7,new QTableWidgetItem(tr(ds[i]->adresse.hausnummer.c_str())));
            ui->tableWidget->setItem(1,8,new QTableWidgetItem(tr(ds[i]->adresse.ort.c_str())));
            ui->tableWidget->setItem(1,9,new QTableWidgetItem(tr(ds[i]->adresse.plz.c_str())));
        }

        /*
        ui->tableWidget->setItem(1,0,new QTableWidgetItem(tr(ds[1]->klassenkameradID.c_str())));
        ui->tableWidget->setItem(1,1,new QTableWidgetItem(tr(ds[1]->vorname.c_str())));
        ui->tableWidget->setItem(1,2,new QTableWidgetItem(tr(ds[1]->nachname[0].c_str())));
        ui->tableWidget->setItem(1,3,new QTableWidgetItem(tr(ds[1]->nachname[1].c_str())));
        ui->tableWidget->setItem(1,4,new QTableWidgetItem(tr(ds[1]->eMail.c_str())));
        ui->tableWidget->setItem(1,5,new QTableWidgetItem(tr((ds[1]->telefonnummer.size()>0)?ds[1]->telefonnummer[0].c_str():"-")));
        ui->tableWidget->setItem(1,6,new QTableWidgetItem(tr(ds[1]->adresse.strasse.c_str())));
        ui->tableWidget->setItem(1,7,new QTableWidgetItem(tr(ds[1]->adresse.hausnummer.c_str())));
        ui->tableWidget->setItem(1,8,new QTableWidgetItem(tr(ds[1]->adresse.ort.c_str())));
        ui->tableWidget->setItem(1,9,new QTableWidgetItem(tr(ds[1]->adresse.plz.c_str())));
        */




}
