#include "mainwindow.h"
#include "datensatzbearbeiten.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<iostream>
#include "qt_loginview.h"
#include "firststart.h"
#include "klassenkamerad_einfuegen.h"
#include "aendern.h"
#include "newpasswort.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    v = new Verwaltung();
    ui->setupUi(this);
    kDAO=new KlassenkameradDAO("hohoho.db");
    ui->tableWidget->setColumnCount(11);
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
    ui->tableWidget->setItem(0,10,new QTableWidgetItem(tr("TYP")));
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

void MainWindow::init(){

    v = new Verwaltung();

}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"click";
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Hallo mein Name ist Eric Johansen";
}


void MainWindow::printDatensatze(){
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setRowCount(Datensatze.size()+1);
    for(unsigned long long i=0;i<Datensatze.size();i++){
        ui->tableWidget->setItem(i+1,0,new QTableWidgetItem(tr(Datensatze[i]->klassenkameradID.c_str())));
        ui->tableWidget->setItem(i+1,1,new QTableWidgetItem(tr(Datensatze[i]->vorname.c_str())));
        ui->tableWidget->setItem(i+1,2,new QTableWidgetItem(tr(Datensatze[i]->nachname[0].c_str())));
        ui->tableWidget->setItem(i+1,3,new QTableWidgetItem(tr(Datensatze[i]->nachname[1].c_str())));
        ui->tableWidget->setItem(i+1,4,new QTableWidgetItem(tr(Datensatze[i]->eMail.c_str())));
        ui->tableWidget->setItem(i+1,5,new QTableWidgetItem(tr((Datensatze[i]->telefonnummer.size()>0)?Datensatze[i]->telefonnummer[0].c_str():"-")));
        ui->tableWidget->setItem(i+1,6,new QTableWidgetItem(tr(Datensatze[i]->adresse.strasse.c_str())));
        ui->tableWidget->setItem(i+1,7,new QTableWidgetItem(tr(Datensatze[i]->adresse.hausnummer.c_str())));
        ui->tableWidget->setItem(i+1,8,new QTableWidgetItem(tr(Datensatze[i]->adresse.ort.c_str())));
        ui->tableWidget->setItem(i+1,9,new QTableWidgetItem(tr(Datensatze[i]->adresse.plz.c_str())));
        std::string typ="Kamerad";
        switch(Datensatze[i]->typ){
            default:
                break;
        case Oragnisator:
            typ="Organisator";
            break;
        case Hauptorganisator:
            typ="Hauptorganisator";
            break;
        }

        ui->tableWidget->setItem(i+1,10,new QTableWidgetItem(tr(typ.c_str())));
        //ds[i]->printToConsole();
        //std::cout<<std::endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    std::vector<KlassenkameradDatensatz*> ds;
    kDAO->klassenkameradenLaden(ds);
    Datensatze=ds;

    printDatensatze();
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

    this->close();

    auto Items = ui->tableWidget->selectedItems();
    Aendern *aendernWin = new Aendern(NULL,kDAO,this, Datensatze[Items.at(0)->row()-1]);
    aendernWin->show();

    //DatensatzBearbeiten *bearbeitenWin = new DatensatzBearbeiten();
    //bearbeitenWin->show();

    Datensatze[Items.at(0)->row()-1]->printToConsole();
    for(int i = 0; i<Items.size(); i++)
    {
        qDebug()<<Items.at(i)->row();
    }


}


void MainWindow::on_pushButton_7_clicked()
{
    cout << "Sensual Boy by Klaus" << endl;
}


void MainWindow::on_pushButton_8_hist_clicked()
{
    std::vector<KlassenkameradDatensatz*> ds;
    std::string row;
    try {
        row=(ui->lineEdit_ID_hist->text().isEmpty())?ui->lineEdit_ID_hist->placeholderText().toLocal8Bit().constData():ui->lineEdit_ID_hist->text().toLocal8Bit().constData();
        qDebug()<<row.c_str()<<" "<<Datensatze.size();
        if(std::stoi(row)<2||std::stoi(row)>Datensatze.size()+1){
            return;
        }
    }  catch (std::invalid_argument e) {
        return;
    }

    std::string id=ui->tableWidget->item(std::stoi(row)-1,0)->text().toLocal8Bit().constData();
    qDebug()<<id.c_str();
    kDAO->aenderungshistorieLaden(ds,id);
    ui->tableWidget->setRowCount(ds.size()+2);
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
    int i=std::stoi(row)-2;
    //aktuellen Datensatz ausgeben
    ui->tableWidget->setItem(ds.size()+1,0,new QTableWidgetItem(tr(Datensatze[i]->klassenkameradID.c_str())));
    ui->tableWidget->setItem(ds.size()+1,1,new QTableWidgetItem(tr(Datensatze[i]->vorname.c_str())));
    ui->tableWidget->setItem(ds.size()+1,2,new QTableWidgetItem(tr(Datensatze[i]->nachname[0].c_str())));
    ui->tableWidget->setItem(ds.size()+1,3,new QTableWidgetItem(tr(Datensatze[i]->nachname[1].c_str())));
    ui->tableWidget->setItem(ds.size()+1,4,new QTableWidgetItem(tr(Datensatze[i]->eMail.c_str())));
    ui->tableWidget->setItem(ds.size()+1,5,new QTableWidgetItem(tr((Datensatze[i]->telefonnummer.size()>0)?Datensatze[i]->telefonnummer[0].c_str():"-")));
    ui->tableWidget->setItem(ds.size()+1,6,new QTableWidgetItem(tr(Datensatze[i]->adresse.strasse.c_str())));
    ui->tableWidget->setItem(ds.size()+1,7,new QTableWidgetItem(tr(Datensatze[i]->adresse.hausnummer.c_str())));
    ui->tableWidget->setItem(ds.size()+1,8,new QTableWidgetItem(tr(Datensatze[i]->adresse.ort.c_str())));
    ui->tableWidget->setItem(ds.size()+1,9,new QTableWidgetItem(tr(Datensatze[i]->adresse.plz.c_str())));
    Datensatze=ds;
}




void MainWindow::on_pushButton_8_db_clicked()
{
    FindDB* w=new FindDB(NULL, v);
    this->close();
    w->show();
}


void MainWindow::on_LoginView_clicked()
{
    qt_loginview *loginview = new qt_loginview(NULL,v);
    this->close();
    loginview->show();
}


void MainWindow::on_ho_anlegen_clicked()
{
    firstStart *firststart = new firstStart(NULL, kDAO, this);
    this->close();
    firststart->show();
}


void MainWindow::on_einfuegen_clicked()
{
    klassenkamerad_einfuegen *view_einfuegen = new klassenkamerad_einfuegen(NULL, kDAO, this);
    this->close();
    view_einfuegen->show();
}


void MainWindow::on_neuesPasswortButton_clicked()
{
    this->init();
    NewPasswort *newPasswort = new NewPasswort(NULL, v, this);
    this->close();
    newPasswort->show();
}


void MainWindow::on_loeschenButton_clicked()
{


    auto Items = ui->tableWidget->selectedItems();
    if(Items.at(0)->row() != 0)
    {
        kDAO->loeschen(Datensatze[Items.at(0)->row()-1]->klassenkameradID);
        on_pushButton_3_clicked();
    }else{
        qDebug() << "nicht löschbar";
    }

}


void MainWindow::on_pushButton_Organisatoren_clicked()
{
    qDebug()<<Datensatze.size();
    Datensatze=KlassenkameradDatensatz::getOrganisatoren(Datensatze);
    qDebug()<<Datensatze.size();
    printDatensatze();
}

