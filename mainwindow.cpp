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
    for(int i=0;i<ds.size();i++){
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

