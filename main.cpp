#include "mainwindow.h"
#include"finddb.h"
#include <QApplication>
#include<string>
#include<iostream>
#include<fstream>
//#include"KlassenkameradDAO.h"
#include "windows.h"
#include<QMainWindow>


int main(int argc, char *argv[])
{    
    std::cout<<"Hello World!\n";
    /*KlassenkameradDAO* kDAO=new KlassenkameradDAO("hohoho.db");
    //auf test oder clean aufruf ueberpruefen
    if(argc>1){
        std::string arg1=argv[1];
        if(arg1.compare("clean")==0){
            std::cout<<"ToDo\talle verwendeten Datenbanktabellen in den „Auslieferungszustand“ zurückversetzen"<<std::endl;
            kDAO->clean();
        }else if(arg1.compare("test")==0){
            kDAO->test();
        }
    }
    //std::cout.flush();


     // Test der Datenbank

    KlassenkameradDatensatz kd;
    kd.vorname="Thomas";
    kd.nachname[0]="Der";
    kd.nachname[1]="Tester";
    kd.eMail="test@gmx.de";
    kd.adresse.hausnummer="42";
    kd.adresse.ort="Testhausen";
    kd.adresse.plz="4288";
    kd.adresse.strasse="gibt es nicht";
    kd.telefonnummer.push_back("7363/4555");
    kDAO->einfuegen(kd,"0");
    kd.nachname[0]="The";
    kd.nachname[1]="TankEngine";
    kd.telefonnummer.push_back("+238000666");
    Sleep(1000);
    kDAO->aktualisieren(kd,"0");
    //kDAO->loeschen(kd.klassenkameradID);

    std::vector<KlassenkameradDatensatz*> ds;
    kDAO->klassenkameradenLaden(ds);    
    for(int i=0;i<ds.size();i++){
        ds[i]->printToConsole();
        std::cout<<std::endl;
    }
    kd.printToConsole();*/

    std::string argv1=(argc>1)?argv[1]:"";

    QApplication a(argc, argv);
    if(argv1.compare("run")==0){
        MainWindow* w=new MainWindow();
        w->show();
    }else{
        FindDB* dieFindDBGUI=new FindDB(nullptr,(argc>1)?argv[1]:"");
        dieFindDBGUI->show();
    }
    return a.exec();
}

