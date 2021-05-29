///////////////////////////////////////////////////////////
//  KlassenkameradDAO.cpp
//  Implementation of the Class KlassenkameradDAO
//  Created on:      26-Mai-2021 15:47:10
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "KlassenkameradDAO.h"
#include <QDebug>
#include <QSqlQuery>
#include<iostream>
#include <QString>
#include <QFile>
#include <QSqlError>


KlassenkameradDAO::KlassenkameradDAO(std::string pfad){
   QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(pfad.c_str());

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
      return;
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
   QSqlQuery query("SELECT name FROM sqlite_master");
   if(!query.exec()){
       qFatal("Can not do query on Database!");
       return;
   }
   int count=0;
   while(query.next()&&count==0){
       //qDebug()<<query.value(0).toString();
       count++;
   }
   //qDebug()<<count;
   if(count==0){
       QFile scriptFile("./make_Tables.txt");
       QSqlQuery query;
       if (scriptFile.open(QIODevice::ReadOnly))
       {
           // The SQLite driver executes only a single (the first) query in the QSqlQuery
           //  if the script contains more queries, it needs to be splitted.
           QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');

           foreach (QString queryTxt, scriptQueries)
           {
               //qDebug()<<queryTxt.toLocal8Bit().constData();
               if (queryTxt.trimmed().isEmpty()) {
                   continue;
               }
               if (!query.exec(queryTxt))
               {
                   qFatal(query.lastError().text().toLocal8Bit().constData());
               }
               query.finish();
           }
       }
   }
}



KlassenkameradDAO::~KlassenkameradDAO(){

}


bool KlassenkameradDAO::test(){
    //QString all=""
    QFile scriptFile("./test_Aufruf.txt");
    QSqlQuery query;
    if (scriptFile.open(QIODevice::ReadOnly))
    {
        // The SQLite driver executes only a single (the first) query in the QSqlQuery
        //  if the script contains more queries, it needs to be splitted.
        QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');

        foreach (QString queryTxt, scriptQueries)
        {
            //qDebug()<<queryTxt.toLocal8Bit().constData();
            if (queryTxt.trimmed().isEmpty()) {
                continue;
            }
            if (!query.exec(queryTxt))
            {
                qFatal(query.lastError().text().toLocal8Bit().constData());
            }
            query.finish();
        }
    }
    return true;
}



bool KlassenkameradDAO::aktualisieren(KlassenkameradDatensatz daten){
    return false;
}
KlassenkameradDatensatz* KlassenkameradDAO::aenderungshistorieLaden(string klassenkameradID){
    return NULL;
}
string KlassenkameradDAO::anmeldedatenPruefen(string eMail, string passwort){
    return NULL;
}
bool KlassenkameradDAO::einfuegen(KlassenkameradDatensatz &daten,string akteurID){
    QSqlQuery query;
    if(!query.exec("INSERT INTO Klassenkamerad DEFAULT VALUES") || !query.exec("SELECT MAX(ID) FROM Klassenkamerad")|| !query.next()){
        qFatal("Konnte keinen neuen Kameraden erstellen!");
        return false;
    }
    std::string id=query.value(0).toString().toLocal8Bit().constData();
    daten.klassenkameradID=id;
    //qDebug()<<id.c_str();
    query.prepare("INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,Nachname2,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES(:vorname,:nachname,:nachname2,:email,:strasse,:hnr,:ort,:plz,time('now'),date('now'),:organisator,:id)");
    query.bindValue(":vorname",daten.vorname.c_str());
    query.bindValue(":nachname",daten.nachname[0].c_str());
    query.bindValue(":nachname2",daten.nachname[1].c_str());
    query.bindValue(":email",daten.eMail.c_str());
    query.bindValue(":strasse",daten.adresse.strasse.c_str());
    query.bindValue(":hnr",daten.adresse.hausnummer.c_str());
    query.bindValue(":ort",daten.adresse.ort.c_str());
    query.bindValue(":plz",daten.adresse.plz.c_str());
    query.bindValue(":organisator",akteurID.c_str());
    query.bindValue(":id",id.c_str());
    if(!query.exec()){
        qFatal("Konnte keinen Datensatz anlegen!");
        return false;
    }
    qDebug()<<daten.telefonnummer.size();
    for(int i=0;i<daten.telefonnummer.size();i++){
        query.prepare("INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=:id),:tele)");
        query.bindValue(":id",id.c_str());
        query.bindValue(":tele",daten.telefonnummer[i].c_str());
        if(!query.exec()){
            qFatal("Konnte keine Telefonnummer hinterlegen!");
            return false;
        }
    }
    query.prepare("SELECT Zeit,Tag FROM Klassenkamerad_Datensatz WHERE Klassenkamerad_Datensatz.Kamerad_ID=:id");
    query.bindValue(":id",id.c_str());
    if(!query.exec() ||!query.next()){
        qFatal("Kann nicht den Zeitpunkt abrufen!");
        return false;
    }

    std::string zeit=query.value(0).toString().toLocal8Bit().constData();
    std::string tag=query.value(1).toString().toLocal8Bit().constData();
    if(zeit.length()==8&& tag.length()==10){
        zeitpunkt zp;
        zp.stunde=std::stoi(zeit.substr(0,2));
        zp.minute=std::stoi(zeit.substr(3,2));
        zp.sekunde=std::stoi(zeit.substr(6,2));

        zp.jahr=std::stoi(tag.substr(0,4));
        zp.monat=std::stoi(tag.substr(5,2));
        zp.tag=std::stoi(tag.substr(8,2));
        daten.zeitpunkt=zp;
    }
    //daten.printToConsole();
    return true;
}
bool KlassenkameradDAO::initialPasswortAendern(string passwort, string akteurID){
    return false;
}
/**
 * ToDo liest gerade noch alle Datensätze ein
 * @brief KlassenkameradDAO::klassenkameradenLaden
 * @param kd Vector zu dem die Klassenkameraden hinzugefügt werden sollen
 * @return true bei Erfolg, oder false bei Abbruch
 */
bool KlassenkameradDAO::klassenkameradenLaden(std::vector<KlassenkameradDatensatz*> &kd){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz ON (Klassenkamerad.ID=Klassenkamerad_Datensatz.Kamerad_ID)")){
        return false;
    }
    while(query.next()){
        KlassenkameradDatensatz* z_kd=new KlassenkameradDatensatz();
        z_kd->klassenkameradID=query.value(0).toString().toLocal8Bit().constData();
        z_kd->vorname=query.value(2).toString().toLocal8Bit().constData();
        z_kd->nachname[0]=query.value(3).toString().toLocal8Bit().constData();
        z_kd->nachname[1]=query.value(4).toString().toLocal8Bit().constData();
        z_kd->eMail=query.value(5).toString().toLocal8Bit().constData();
        adresse ad;
        ad.strasse=query.value(6).toString().toLocal8Bit().constData();
        ad.hausnummer=query.value(7).toString().toLocal8Bit().constData();
        ad.ort=query.value(8).toString().toLocal8Bit().constData();
        ad.plz=query.value(9).toString().toLocal8Bit().constData();
        z_kd->adresse=ad;

        std::string zeit=query.value(10).toString().toLocal8Bit().constData();
        std::string tag=query.value(11).toString().toLocal8Bit().constData();
        if(zeit.length()==8&& tag.length()==10){
            zeitpunkt zp;
            zp.stunde=std::stoi(zeit.substr(0,2));
            zp.minute=std::stoi(zeit.substr(3,2));
            zp.sekunde=std::stoi(zeit.substr(6,2));

            zp.jahr=std::stoi(tag.substr(0,4));
            zp.monat=std::stoi(tag.substr(5,2));
            zp.tag=std::stoi(tag.substr(8,2));
            z_kd->zeitpunkt=zp;
        }
        QSqlQuery queryTele;
        queryTele.prepare("SELECT * FROM Telefonnummer WHERE Telefonnummer.Datensatz_ID=:id");
        queryTele.bindValue(":id",query.value(1));
        if(!queryTele.exec()){
            return false;
        }
        std::vector<std::string> ztele;
        while(queryTele.next()){
            ztele.push_back(queryTele.value(0).toString().toLocal8Bit().constData());
        }
        z_kd->telefonnummer=ztele;
        queryTele.finish();
        kd.push_back(z_kd);
    }
    query.finish();
    return true;
}
bool KlassenkameradDAO::loeschen(KlassenkameradDatensatz k){
    return false;
}
bool KlassenkameradDAO::organisatorSperren(string eMail){
    return false;
}
bool KlassenkameradDAO::removeOrganisator(string ID){
    return false;
}
bool KlassenkameradDAO::setOrganisator(string ID){
    return false;
}
