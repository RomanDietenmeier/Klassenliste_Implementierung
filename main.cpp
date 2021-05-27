#include "mainwindow.h"

#include <QApplication>
#include<string>
#include<iostream>
#include<fstream>
#include"KlassenkameradDAO.h"


int main(int argc, char *argv[])
{    
    std::cout<<"Hello World!\n";
    KlassenkameradDAO* kDAO=new KlassenkameradDAO("lol.db");
    //auf test oder clean aufruf ueberpruefen
    if(argc>1){
        std::string arg1=argv[1];
        if(arg1.compare("clean")==0){
            std::cout<<"ToDo\talle verwendeten Datenbanktabellen in den „Auslieferungszustand“ zurückversetzen"<<std::endl;
        }else if(arg1.compare("test")==0){
           kDAO->test();
        }
    }
    //std::cout.flush();

    /*
     * Test der Datenbank

    std::vector<KlassenkameradDatensatz*> ds;
    kDAO->klassenkameradenLaden(ds);    
    for(int i=0;i<ds.size();i++){
        ds[i]->printToConsole();
        std::cout<<std::endl;
    }*/


    QApplication a(argc, argv);
    MainWindow w;
    w.show();        
    return a.exec();
}

