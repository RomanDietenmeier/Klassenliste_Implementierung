#include "mainwindow.h"

#include <QApplication>
#include<string>
#include<iostream>

int main(int argc, char *argv[])
{
    //auf test oder clean aufruf ueberpruefen
    if(argc>1){
        std::string arg1=argv[1];
        if(arg1.compare("clean")){
            std::cout<<"alle verwendeten Datenbanktabellen in den „Auslieferungszustand“ zurückversetzen"<<std::endl;
        }else if(arg1.compare("test")){
            std::cout<<"Datenbanktabellen mit Testdaten"<<std::endl;
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

