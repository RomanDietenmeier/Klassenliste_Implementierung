#include "mainwindow.h"

#include <QApplication>
#include<string>
#include<iostream>
#include<fstream>

int main(int argc, char *argv[])
{    
    //auf test oder clean aufruf ueberpruefen
    if(argc>1){
        std::ofstream ofs("out.txt",std::ofstream::out);
        std::string arg1=argv[1];
        if(arg1.compare("clean")==0){
            ofs<<"alle verwendeten Datenbanktabellen in den „Auslieferungszustand“ zurückversetzen"<<std::endl;
        }else if(arg1.compare("test")==0){
           ofs<<"Datenbanktabellen mit Testdaten"<<std::endl;
        }
        ofs.close();
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

