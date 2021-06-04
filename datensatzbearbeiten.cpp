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

}
