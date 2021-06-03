#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    kDAO=new KlassenkameradDAO("hohoho.db");
    ui->tableWidget->setColumnCount(9);
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
    //Test Datensatz
    kd=new KlassenkameradDatensatz();
    kd->vorname="Thomas";
    kd->nachname[0]="Der";
    kd->nachname[1]="Tester";
    kd->eMail="test@gmx.de";
    kd->adresse.hausnummer="42";
    kd->adresse.ort="Testhausen";
    kd->adresse.plz="4288";
    kd->adresse.strasse="gibt es nicht";
    kd->telefonnummer.push_back("7363/4555");
    kDAO->einfuegen(kd,"0");
    kd->nachname[0]="The";
    kd->nachname[1]="TankEngine";
    kd->telefonnummer.push_back("+238000666");


    //DB ausgeben
    on_pushButton_3_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"click";
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Hallo mein Name ist Eric Johansen";
}


void MainWindow::on_pushButton_3_clicked()
{
    std::vector<KlassenkameradDatensatz*> ds;
    kDAO->klassenkameradenLaden(ds);
    ui->tableWidget->setRowCount(ds.size()+1);
    for(int i=0;i<ds.size();i++){
        ui->tableWidget->setItem(i+1,0,new QTableWidgetItem(tr(ds[i]->klassenkameradID.c_str())));
        ui->tableWidget->setItem(i+1,1,new QTableWidgetItem(tr(ds[i]->vorname.c_str())));
        ui->tableWidget->setItem(i+1,2,new QTableWidgetItem(tr(ds[i]->nachname[0].c_str())));
        ui->tableWidget->setItem(i+1,3,new QTableWidgetItem(tr(ds[i]->nachname[1].c_str())));
        ui->tableWidget->setItem(i+1,4,new QTableWidgetItem(tr(ds[i]->eMail.c_str())));
        ui->tableWidget->setItem(i+1,5,new QTableWidgetItem(tr((ds[i]->telefonnummer.size()>0)?ds[i]->telefonnummer[0].c_str():"-")));
        ui->tableWidget->setItem(i+1,6,new QTableWidgetItem(tr(ds[i]->adresse.strasse.c_str())));
        ui->tableWidget->setItem(i+1,7,new QTableWidgetItem(tr(ds[i]->adresse.hausnummer.c_str())));
        ui->tableWidget->setItem(i+1,8,new QTableWidgetItem(tr(ds[i]->adresse.ort.c_str())));
        ui->tableWidget->setItem(i+1,9,new QTableWidgetItem(tr(ds[i]->adresse.plz.c_str())));
        ds[i]->printToConsole();
        std::cout<<std::endl;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    kDAO->clean();
}


void MainWindow::on_pushButton_5_clicked()
{
    kDAO->test();
}


void MainWindow::on_pushButton_6_clicked()
{
    kd->vorname+="ä";
    kDAO->aktualisieren(kd,"0");
}


void MainWindow::on_pushButton_7_clicked()
{
    cout << "Sensual Boy by Klaus" << endl;
}

