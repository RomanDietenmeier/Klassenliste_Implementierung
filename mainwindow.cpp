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
#include "organisator_erstellen.h"
#include"orga_entsperren.h"


MainWindow::MainWindow(QWidget *parent,Verwaltung* v)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    if(v==NULL){
        kDAO=new KlassenkameradDAO("hohoho.db");
    }else{
        this->v=v;
        kDAO=v->m_KlassenkameradDAO;
    }

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


    /*//Test Datensatz
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
    kd->telefonnummer.push_back("+238000666");*/


    //DB ausgeben
    on_pushButton_3_clicked();

    if(v==NULL){
        string akteurID="0";
        for(unsigned long long i=0;i<Datensatze.size();i++){
            if(Datensatze[i]->typ==Hauptorganisator)
                akteurID=Datensatze[i]->klassenkameradID;
        }
        this->v = new Verwaltung(akteurID);
    }
    qDebug()<<"Akteur_id: "<<this->v->getAkteuerID().c_str();

}

MainWindow::~MainWindow()
{
    delete ui;
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
        //ui->tableWidget->setItem(i+1,5,new QTableWidgetItem(tr((Datensatze[i]->telefonnummer.size()>0)?Datensatze[i]->telefonnummer[0].c_str():"-")));
        std::string s="";
        for(unsigned long long j=0;j<Datensatze[i]->telefonnummer.size();j++){
            s+=Datensatze[i]->telefonnummer[j].c_str();
            if(j+1!=Datensatze[i]->telefonnummer.size())
                s+="\n";
        }
        ui->tableWidget->setItem(i+1,5,new QTableWidgetItem(tr(s.c_str())));
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
        //ui->tableWidget->setCol
        ui->tableWidget->resizeRowsToContents();
        ui->tableWidget->resizeColumnsToContents();
    }
}

vector<KlassenkameradDatensatz*> bubbleSort(vector<KlassenkameradDatensatz*> a)
{
    for(unsigned long long i = 0; i<a.size(); i++){
        int swaps = 0;
        for(unsigned long long j =0; j<a.size()-1;j++){
            if(std::stoi(a[j]->klassenkameradID) > std::stoi(a[j+1]->klassenkameradID)){
                KlassenkameradDatensatz* temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                swaps = 1;
            }
        }
        if(!swaps){
            break;
        }
    }
    return a;
}

void MainWindow::sortierenID(){
    Datensatze=bubbleSort(Datensatze);
    printDatensatze();
}

void MainWindow::on_pushButton_3_clicked() //aktualisieren der Einträge

{
    std::vector<KlassenkameradDatensatz*> ds;
    kDAO->klassenkameradenLaden(ds);
    Datensatze=ds;

    sortierenID();

}

/*
void MainWindow::on_pushButton_4_clicked() //cleanen der Einträge
{
    kDAO->clean();
    on_pushButton_3_clicked();
}


void MainWindow::on_pushButton_5_clicked() //Testeinträge einfügen
{
    kDAO->test();
    on_pushButton_3_clicked();
}
*/

void MainWindow::on_pushButton_6_clicked() //Ändern Button
{
    //kd->vorname+="ä";
    //kDAO->aktualisieren(kd,"0");

    qDebug()<<v->getAkteuerID().c_str();



    auto Items = ui->tableWidget->selectedItems();
    if(Items.at(0)->row() != 0 && (Datensatze[Items.at(0)->row()-1]->typ==Kamerad || Datensatze[Items.at(0)->row()-1]->klassenkameradID.compare(v->getAkteuerID())==0))
    {
        Aendern *aendernWin = new Aendern(NULL,kDAO,this, Datensatze[Items.at(0)->row()-1]);
        this->close();
        aendernWin->show();

        Datensatze[Items.at(0)->row()-1]->printToConsole();
        for(int i = 0; i<Items.size(); i++)
        {
            qDebug()<<Items.at(i)->row();
        }

    }else{
        qDebug() << "nicht änderbar!";
    }

}


void MainWindow::on_pushButton_8_hist_clicked() //Historie anzeigen
{
    std::vector<KlassenkameradDatensatz*> ds;
    std::string row;
    try {
        row=(ui->lineEdit_ID_hist->text().isEmpty())?ui->lineEdit_ID_hist->placeholderText().toLocal8Bit().constData():ui->lineEdit_ID_hist->text().toLocal8Bit().constData();
        qDebug()<<row.c_str()<<" "<<Datensatze.size();
        if(std::stoi(row)<2||(unsigned long long)std::stoi(row)>Datensatze.size()+1){
            return;
        }
    }  catch (std::invalid_argument e) {
        qDebug()<<e.what();
        return;
    }

    std::string id=ui->tableWidget->item(std::stoi(row)-1,0)->text().toLocal8Bit().constData();
    qDebug()<<id.c_str();
    kDAO->aenderungshistorieLaden(ds,id);
    ui->tableWidget->setRowCount(ds.size()+2);
    for(unsigned long long i=0;i<ds.size();i++){
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
    FindDB* w=new FindDB();
    this->close();
    w->show();
}


void MainWindow::on_LoginView_clicked()
{
    qt_loginview *loginview = new qt_loginview(NULL,v);
    this->close();
    loginview->show();
}

/*
void MainWindow::on_ho_anlegen_clicked()
{
    firstStart *firststart = new firstStart(NULL, kDAO, this);
    this->close();
    firststart->show();
}
*/

void MainWindow::on_einfuegen_clicked()
{
    klassenkamerad_einfuegen *view_einfuegen = new klassenkamerad_einfuegen(NULL, kDAO, this);
    this->close();
    view_einfuegen->show();
}


void MainWindow::on_neuesPasswortButton_clicked()
{    
    NewPasswort *newPasswort = new NewPasswort(NULL, v, this);

    this->close();
    newPasswort->show();
}


void MainWindow::on_loeschenButton_clicked()
{


    auto Items = ui->tableWidget->selectedItems();
    if(Items.size()<=0)
        return;
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
    //qDebug()<<Datensatze.size();
    Datensatze=KlassenkameradDatensatz::getOrganisatoren(Datensatze);
    //qDebug()<<Datensatze.size();
    printDatensatze();
}


void MainWindow::on_PushButtonRemoveOrganisator_clicked()
{
    auto Items = ui->tableWidget->selectedItems();
        if(Items.size()>0&&Items.at(0)->row() != 0 && Datensatze[Items.at(0)->row()-1]->typ==Oragnisator)
        {
            if(kDAO->removeOrganisator(Datensatze[Items.at(0)->row()-1]->klassenkameradID)){
                Datensatze.erase(Datensatze.begin()+Items.at(0)->row()-1);
                printDatensatze();
            }

        }else{
            qDebug() << "Organisator Status kann nicht entzogen werden!";
        }
}




void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if(row==0)
    {
        ui->pushButton_6->setEnabled(false);
    }else
    {
        ui->pushButton_6->setEnabled(true);
    }

}


void MainWindow::on_pushButton_clicked()
{
    Datensatze=KlassenkameradDatensatz::getGesperrte(Datensatze);
    printDatensatze();
}


void MainWindow::on_OrganisatorErteilenButton_clicked()
{

    auto Items = ui->tableWidget->selectedItems();
    if (Items.size()!=0 && Items.at(0)->row()>0 && Datensatze[Items.at(0)->row()-1]->typ == Kamerad){
        Organisator_erstellen *organisator_erstellen = new Organisator_erstellen(NULL, kDAO, this, Datensatze[Items.at(0)->row()-1]);
        this->close();
        organisator_erstellen->show();
    }

}


void MainWindow::on_pushButton_entsperren_clicked()
{
    auto Items = ui->tableWidget->selectedItems();
    if (Items.size()!=0 && Items.at(0)->row()>0&& Datensatze[Items.at(0)->row()-1]->gespert){
        Orga_entsperren* entsperrer=new Orga_entsperren(nullptr,v->m_KlassenkameradDAO,this,Datensatze[Items.at(0)->row()-1]);
        this->close();
        entsperrer->show();
    }
}

