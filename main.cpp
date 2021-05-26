#include "mainwindow.h"

#include <QApplication>
#include<string>
#include<iostream>
#include<fstream>

int main(int argc, char *argv[])
{    
    std::cout<<"Hello World!\n";
    //auf test oder clean aufruf ueberpruefen
    if(argc>1){
        std::string arg1=argv[1];
        if(arg1.compare("clean")==0){
            std::cout<<"ToDo\talle verwendeten Datenbanktabellen in den „Auslieferungszustand“ zurückversetzen"<<std::endl;
        }else if(arg1.compare("test")==0){
           std::cout<<"ToDo\tDatenbanktabellen mit Testdaten"<<std::endl;
        }
    }
    std::cout.flush();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();        
    return a.exec();
}

