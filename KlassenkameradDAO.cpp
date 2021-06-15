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

/**
 * @brief KlassenkameradDAO::KlassenkameradDAO öffnet die Datenbank falls vorhanden, oder baut die Struktur in einer neuen Datei auf
 * @param pfad Pfad zur SQLite Datei. Sollte keine existieren, so ist der Pfad der Ort an dem die Datei angelegt wird.
 */
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
   if(!query.exec() ){
       throw std::invalid_argument( "Can not do query on Database!" );
       //qFatal("Can not do query on Database!");
       return;
   }
   int count=0;
   while(query.next()&&count==0){
       //qDebug()<<query.value(0).toString();
       count++;
   }
   //qDebug()<<count;
   if(count==0){
       initial=true;
       //QFile scriptFile("./make_Tables.txt");
       QSqlQuery query;
       /*
       if (scriptFile.open(QIODevice::ReadOnly))
       {

       }
*/
       QString string="\
       PRAGMA foreign_keys = ON;\
       CREATE TABLE Klassenkamerad(ID INTEGER PRIMARY KEY AUTOINCREMENT);\
       CREATE TABLE Klassenkamerad_Datensatz(ID INTEGER PRIMARY KEY AUTOINCREMENT,Vorname TEXT NOT NULL,Nachname TEXT NOT NULL,Nachname2 TEXT,EMail TEXT NOT NULL,Strasse Text NOT NULL,Hausnummer Text NOT NULL,Ort Text NOT NULL,PLZ Text NOT NULL,Zeit TIMESTAMP NOT NULL,Tag Date NOT NULL,Organisator INTEGER NOT NULL,Kamerad_ID INTEGER NOT NULL,FOREIGN KEY(Kamerad_ID) REFERENCES Klassenkamerad(ID) ON DELETE CASCADE);\
       CREATE TABLE Telefonnummer(Telefonnummer TEXT,Datensatz_ID INTEGER NOT NULL,FOREIGN KEY(Datensatz_ID) REFERENCES Klassenkamerad_Datensatz(ID) ON DELETE CASCADE,PRIMARY KEY(Telefonnummer,Datensatz_ID));\
       CREATE TABLE Organisator(Passwort TEXT NOT NULL,Initialpasswort BOOL NOT NULL,gesperrt BOOL NOT NULL,Kamerad_ID INTEGER NOT NULL,FOREIGN KEY(Kamerad_ID) REFERENCES Klassenkamerad(ID) ON DELETE CASCADE PRIMARY KEY(Kamerad_ID));\
       CREATE TABLE Hauptorganisator(Masterpasswort TEXT NOT NULL,Kamerad_ID INTEGER NOT NULL,FOREIGN KEY(Kamerad_ID) REFERENCES Klassenkamerad(ID) ON DELETE CASCADE PRIMARY KEY(Kamerad_ID));";

       // The SQLite driver executes only a single (the first) query in the QSqlQuery
       //  if the script contains more queries, it needs to be splitted.
       //QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');
       QStringList scriptQueries = string.split(";");

       foreach (QString queryTxt, scriptQueries)
       {
           //qDebug()<<queryTxt.toLocal8Bit().constData();
           if (queryTxt.trimmed().isEmpty()) {
               continue;
           }
           if (!query.exec(queryTxt))
           {
               qFatal("ERROR");
           }
           query.finish();
       }

   }
   if(query.exec("SELECT COUNT(*) FROM Klassenkamerad") && query.next()){
       if(query.value(0).toInt()==0){
           initial=true;
       }
   }
}



KlassenkameradDAO::~KlassenkameradDAO(){

}

/**
 * @brief KlassenkameradDAO::clean leert den kompletten Dateninhalt der Datenbank
 * @return true bei Erfolg, false bei Fehlschlag
 */
bool KlassenkameradDAO::clean(){
    QSqlQuery query;
    if(!query.exec("DELETE FROM Hauptorganisator")||!query.exec("DELETE FROM Organisator")||!query.exec("DELETE FROM Telefonnummer")||!query.exec("DELETE FROM Klassenkamerad_Datensatz")||!query.exec("DELETE FROM Klassenkamerad")){
        qFatal("Konnte die Datenbank nicht\"cleanen\"!");
        return false;
    }
    return true;
}

/**
 * @brief KlassenkameradDAO::test verwirft(falls vorhanden) alte Datenbank und baut die Datenbank mit Testdaten neu auf.
 * @return true bei Erfolg, false bei Fehlschlag
 */
bool KlassenkameradDAO::test(){
    //QString all=""
    //QFile scriptFile("./test_Aufruf.txt");
    QSqlQuery query;
    /*
    if (scriptFile.open(QIODevice::ReadOnly))
    {
        // The SQLite driver executes only a single (the first) query in the QSqlQuery
        //  if the script contains more queries, it needs to be splitted.

    }
*/
    QString string="DROP TABLE IF EXISTS Hauptorganisator;DROP TABLE IF EXISTS Organisator;DROP TABLE IF EXISTS Telefonnummer;DROP TABLE IF EXISTS Klassenkamerad_Datensatz;DROP TABLE IF EXISTS Klassenkamerad;PRAGMA foreign_keys = ON;CREATE TABLE Klassenkamerad(ID INTEGER PRIMARY KEY AUTOINCREMENT);CREATE TABLE Klassenkamerad_Datensatz(ID INTEGER PRIMARY KEY AUTOINCREMENT,Vorname TEXT NOT NULL,Nachname TEXT NOT NULL,Nachname2 TEXT,EMail TEXT NOT NULL,Strasse Text NOT NULL,Hausnummer Text NOT NULL,Ort Text NOT NULL,PLZ Text NOT NULL,Zeit TIMESTAMP NOT NULL,Tag Date NOT NULL,Organisator INTEGER NOT NULL,Kamerad_ID INTEGER NOT NULL,FOREIGN KEY(Kamerad_ID) REFERENCES Klassenkamerad(ID) ON DELETE CASCADE);CREATE TABLE Telefonnummer(Telefonnummer TEXT,Datensatz_ID INTEGER NOT NULL,FOREIGN KEY(Datensatz_ID) REFERENCES Klassenkamerad_Datensatz(ID) ON DELETE CASCADE,PRIMARY KEY(Telefonnummer,Datensatz_ID));CREATE TABLE Organisator(Passwort TEXT NOT NULL,Initialpasswort BOOL NOT NULL,gesperrt BOOL NOT NULL,Kamerad_ID INTEGER NOT NULL\
,FOREIGN KEY(Kamerad_ID) REFERENCES Klassenkamerad(ID) ON DELETE CASCADE \
PRIMARY KEY(Kamerad_ID)\
);\
CREATE TABLE Hauptorganisator(\
Masterpasswort TEXT NOT NULL,\
Kamerad_ID INTEGER NOT NULL,\
FOREIGN KEY(Kamerad_ID) REFERENCES Klassenkamerad(ID) ON DELETE CASCADE \
PRIMARY KEY(Kamerad_ID)\
);\
INSERT INTO Klassenkamerad(ID) VALUES(0);\
INSERT INTO Organisator(Passwort,Initialpasswort,gesperrt,Kamerad_ID) VALUES('RD',True,False,0);\
INSERT INTO Hauptorganisator(Masterpasswort,Kamerad_ID) VALUES('RD',0);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Roland','Dietrich','RolandDietrich@gmx.de','AdminStrasse','14b','Aminien','4269',time('now'),date('now'),0,0);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=0),'07363/71321');\
INSERT INTO Klassenkamerad(ID) VALUES(1);\
INSERT INTO Organisator(Passwort,Initialpasswort,gesperrt,Kamerad_ID) VALUES('MM',True,False,1);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Max','Mustermann','MaxMustermann@gmx.de','OrganisatorStrasse','13','Germania','1',time('now'),date('now'),0,1);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=1),'8880001');\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=1),'8880002');\
INSERT INTO Klassenkamerad(ID) VALUES(2);\
INSERT INTO Organisator(Passwort,Initialpasswort,gesperrt,Kamerad_ID) VALUES('KM',True,False,2);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Klara','Musterfrau','KlaraMusterfrau@gmx.de','OrganisatorinnenStrasse','4','Berg','8866',time('now'),date('now'),0,2);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=2),'+431552200');\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=2),'+4988855621');\
INSERT INTO Klassenkamerad(ID) VALUES(3);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Roman','Dietenmeier','Robert@student.de','Aalener Weide','12','Laupberg','78988',time('now'),date('now'),1,3);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=3),'+49125528962');\
INSERT INTO Klassenkamerad(ID) VALUES(4);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Eric','Schuh','Erik@schlaeft.de','Aalener Heide','3','Wasseralfingen','73433',time('now'),date('now'),2,4);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=4),'+49125528963');\
INSERT INTO Klassenkamerad(ID) VALUES(5);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Patrick','Vogel','PEPE@maimai.de','Aalener Fluchtweg','131','Aalen','73433',time('now'),date('now'),0,5);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=5),'+49125528963');\
INSERT INTO Klassenkamerad(ID) VALUES(6);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Dommenic','Berger','derLehrer@Rotterburg.de','Gipfelstrasse','5','Gipfelberg','666777',time('now'),date('now'),0,6);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=6),'+49000111222');\
INSERT INTO Klassenkamerad(ID) VALUES(7);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Maximilian','Babo','derAllwissende@CProfi.de','Strebende Strasse','2','Geniusburg','888',time('now'),date('now'),0,7);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=7),'+49000111223');\
INSERT INTO Klassenkamerad(ID) VALUES(8);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Moritz','Werner','Werner@Werner.de','Schlossweg','1','Herzogen','1111142',time('now'),date('now'),0,8);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=8),'+491722226666');\
INSERT INTO Klassenkamerad(ID) VALUES(9);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Tider','Tiger','Timooo@coolerTyp.de','Erikastrasse','4','Düben','1111342',time('now'),date('now'),0,9);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=9),'+49170005556');\
INSERT INTO Klassenkamerad(ID) VALUES(10);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Scooby','Snacks','sindTeuer@guenstig.de','Space Strasse','12','Cartoonhausen','1111323',time('now'),date('now'),0,10);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=10),'+4917000666');\
INSERT INTO Klassenkamerad(ID) VALUES(11);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Catleya','Otter','istSchoen@web.de','Nette Strasse','13','ShipIt','1111356',time('now'),date('now'),0,11);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=11),'+4917000777');\
INSERT INTO Klassenkamerad(ID) VALUES(12);\
INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES('Fabioso','Walter','gegenGewalt@Carsten.de','Schlaeger Strasse','7','ShipIt','1111356',time('now'),date('now'),0,12);\
INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=12),'+4917005777');";
    QStringList scriptQueries = string.split(';');
    //QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');

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

    return true;
}



/**
 * @brief KlassenkameradDAO::aktualisieren legt einen neuen Datensatz an für ein bestehendes Klassenmitglied.
 * @param daten Der Datensatz mit den neuen Dateien. Bei diesem wird der Zeitpunkt mit der Ausführung aktualisiert.
 * @param akteurID Der Organisator der die Änderung vornimmt.
 * @return true bei Erfolg, false bei Fehlschlag
 */
bool KlassenkameradDAO::aktualisieren(KlassenkameradDatensatz* daten,string akteurID){
    QSqlQuery query;
    query.prepare("INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,Nachname2,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES(:vorname,:nachname,:nachname2,:email,:strasse,:hnr,:ort,:plz,time('now'),date('now'),:organisator,:id)");
    query.bindValue(":vorname",daten->vorname.c_str());
    query.bindValue(":nachname",daten->nachname[0].c_str());
    query.bindValue(":nachname2",daten->nachname[1].c_str());
    query.bindValue(":email",daten->eMail.c_str());
    query.bindValue(":strasse",daten->adresse.strasse.c_str());
    query.bindValue(":hnr",daten->adresse.hausnummer.c_str());
    query.bindValue(":ort",daten->adresse.ort.c_str());
    query.bindValue(":plz",daten->adresse.plz.c_str());
    query.bindValue(":organisator",akteurID.c_str());    
    query.bindValue(":id",daten->klassenkameradID.c_str());
    if(!query.exec()){
        qFatal("Konnte keinen Datensatz anlegen!");
        return false;
    }
    query.prepare("SELECT ID FROM Klassenkamerad_Datensatz WHERE ID=(SELECT MAX(ID)FROM Klassenkamerad_Datensatz WHERE Klassenkamerad_Datensatz.Kamerad_ID=:id)");
    query.bindValue(":id",daten->klassenkameradID.c_str());
    if(!query.exec()|| !query.next()){
        qFatal("Konnte Datensatz Id nicht herausfinden!");
    }
    QString id=query.value(0).toString();
    //qDebug()<<id;
    for(unsigned long long i=0;i<daten->telefonnummer.size();i++){
        query.prepare("INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES (:id,:tele)");
        query.bindValue(":id",id);
        query.bindValue(":tele",daten->telefonnummer[i].c_str());
        if(!query.exec()){
            qFatal("Konnte Telefonnummer nicht hinterlegen!");
            return false;
        }
    }
    //Zeitpunkt aktualisieren!
    query.prepare("SELECT Zeit,Tag FROM Klassenkamerad_Datensatz WHERE ID=:id");
    query.bindValue(":id",id);
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
        daten->zeitpunkt=zp;
    }
    return true;
}
/**
 * @brief KlassenkameradDAO::aenderungshistorieLaden Zeigt die Änderungshistorie eines Eintrags
 * @param kd Vektor mit den Datensätzen
 * @param klassenkameradID Die Id des Klassenkameradens, von dem die Historie angeschaut wird.
 * @return true bei Erfolg, ansonsten false
 */
bool KlassenkameradDAO::aenderungshistorieLaden(vector<KlassenkameradDatensatz*> &kd,string klassenkameradID){
    //SELECT * FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz as kd ON (Klassenkamerad.ID=kd.Kamerad_ID) WHERE Klassenkamerad.ID=14 AND kd.ID<(SELECT MAX(ID)FROM Klassenkamerad_Datensatz WHERE Klassenkamerad_Datensatz.Kamerad_ID=kd.Kamerad_ID)
    QSqlQuery query;
    query.prepare("SELECT * FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz as kd ON (Klassenkamerad.ID=kd.Kamerad_ID) WHERE Klassenkamerad.ID=:id AND kd.ID<(SELECT MAX(ID)FROM Klassenkamerad_Datensatz WHERE Klassenkamerad_Datensatz.Kamerad_ID=kd.Kamerad_ID)");
    query.bindValue(":id",klassenkameradID.c_str());
    if(!query.exec()){
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
login_ret KlassenkameradDAO::anmeldedatenPruefen(string eMail, string passwort){
    QSqlQuery query;
    //SELECT Klassenkamerad.ID,Organisator.Passwort,Organisator.gesperrt,Organisator.Initialpasswort,Hauptorganisator.Masterpasswort FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz AS KD ON(Klassenkamerad.ID=kd.Kamerad_ID)LEFT JOIN Organisator ON(Klassenkamerad.ID=Organisator.Kamerad_ID) LEFT JOIN Hauptorganisator ON (Klassenkamerad.ID=Hauptorganisator.Kamerad_ID) WHERE kd.EMail=:email
    query.prepare("SELECT Klassenkamerad.ID,Organisator.Passwort,Organisator.gesperrt,Organisator.Initialpasswort,Hauptorganisator.Masterpasswort FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz AS KD ON(Klassenkamerad.ID=kd.Kamerad_ID)LEFT JOIN Organisator ON(Klassenkamerad.ID=Organisator.Kamerad_ID) LEFT JOIN Hauptorganisator ON (Klassenkamerad.ID=Hauptorganisator.Kamerad_ID) WHERE kd.EMail=:email");
    query.bindValue(":email",eMail.c_str());
    if(!query.exec() || !query.next()|| query.value(3).isNull() ){
        return {"-1",false};
    }
    if(((0!=query.value(1).toString().toStdString().compare(passwort) )&&(0!=query.value(4).toString().toStdString().compare(passwort)))||
           ((0==query.value(1).toString().toStdString().compare(passwort) &&query.value(2).toBool() )&&(0!=query.value(4).toString().toStdString().compare(passwort))) ){
        return {"-1",false};
    }
    login_ret ret;
    ret.id=query.value(0).toString().toStdString();
    ret.initial_login=query.value(3).toBool();
    return ret;
}
/**
 * @brief KlassenkameradDAO::einfuegen Fügt einen neuen Klassenkameraden der Datenbank hinzu.
 * @param daten Die Daten des neuen Kameraden. Der Zeitpunkt wird mit ausführung der Methode aktualisiert.
 * @param akteurID Der Organisator der den Klassenkameraden einfügt.
 * @return
 */
bool KlassenkameradDAO::einfuegen(KlassenkameradDatensatz* daten,string akteurID){
    QSqlQuery query;
    if(!query.exec("INSERT INTO Klassenkamerad DEFAULT VALUES") || !query.exec("SELECT MAX(ID) FROM Klassenkamerad")|| !query.next()){
        qFatal("Konnte keinen neuen Kameraden erstellen!");
        return false;
    }
    std::string id=query.value(0).toString().toLocal8Bit().constData();
    daten->klassenkameradID=id;
    //qDebug()<<id.c_str();
    query.prepare("INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,Nachname2,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES(:vorname,:nachname,:nachname2,:email,:strasse,:hnr,:ort,:plz,time('now'),date('now'),:organisator,:id)");
    query.bindValue(":vorname",daten->vorname.c_str());
    query.bindValue(":nachname",daten->nachname[0].c_str());
    query.bindValue(":nachname2",daten->nachname[1].c_str());
    query.bindValue(":email",daten->eMail.c_str());
    query.bindValue(":strasse",daten->adresse.strasse.c_str());
    query.bindValue(":hnr",daten->adresse.hausnummer.c_str());
    query.bindValue(":ort",daten->adresse.ort.c_str());
    query.bindValue(":plz",daten->adresse.plz.c_str());
    query.bindValue(":organisator",akteurID.c_str());
    query.bindValue(":id",id.c_str());
    if(!query.exec()){
        qFatal("Konnte keinen Datensatz anlegen!");
        return false;
    }
    //qDebug()<<daten.telefonnummer.size();
    for(unsigned long long i=0;i<daten->telefonnummer.size();i++){
        query.prepare("INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=:id),:tele)");
        query.bindValue(":id",id.c_str());
        query.bindValue(":tele",daten->telefonnummer[i].c_str());
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
        daten->zeitpunkt=zp;
    }
    //daten.printToConsole();
    return true;
}
/**
 * @brief KlassenkameradDAO::passwortAendern ändert das Passwort eines Organisators.
 * @param passwort das neue Passwort.
 * @param akteurID der Organisator, dessen Passwort geändert wird.
 * @return
 */
bool KlassenkameradDAO::passwortAendern(string passwort, string akteurID){
    //UPDATE Organisator SET Passwort='AA' ,Initialpasswort=false WHERE Kamerad_ID=0
    QSqlQuery query;
    query.prepare("UPDATE Organisator SET Passwort=:pw ,Initialpasswort=false WHERE Kamerad_ID=:id");
    query.bindValue(":pw",passwort.c_str());
    query.bindValue(":id",akteurID.c_str());
    if(!query.exec()){
        return false;
    }
    return true;
}
/**
 * @brief KlassenkameradDAO::klassenkameradenLaden Lädt alle aktuellen Klassenkameraden Datensätze
 * @param kd Vector zu dem die Klassenkameraden hinzugefügt werden sollen
 * @return true bei Erfolg, oder false bei Abbruch
 */
bool KlassenkameradDAO::klassenkameradenLaden(std::vector<KlassenkameradDatensatz*> &kd){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz as kd ON (Klassenkamerad.ID=kd.Kamerad_ID) LEFT JOIN Organisator ON (Klassenkamerad.ID=Organisator.Kamerad_ID) LEFT JOIN Hauptorganisator ON(Klassenkamerad.ID=Hauptorganisator.Kamerad_ID )WHERE kd.ID=(SELECT MAX(ID)FROM Klassenkamerad_Datensatz WHERE Klassenkamerad_Datensatz.Kamerad_ID=kd.Kamerad_ID)")){
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

        if(query.value(19).isNull()){
            if(query.value(17).isNull()){
                z_kd->typ=Kamerad;
            }else{
                z_kd->typ=Oragnisator;
            }
        }else{
            z_kd->typ=Hauptorganisator;
        }
        if(!query.value(16).isNull()){
            z_kd->gespert=query.value(16).toBool();
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
/**
 * @brief KlassenkameradDAO::loeschen löscht alle Einträge in Bezug auf den Kameraden mit der übergebenen ID-
 * @param ID Die Id des zu löschenden Klassenkameraden.
 * @return true bei Erfolg, false bei Fehlschlag
 */
bool KlassenkameradDAO::loeschen(string ID){
    QSqlQuery query;
    query.prepare("DELETE FROM Klassenkamerad WHERE Klassenkamerad.ID=:id");
    query.bindValue(":id",ID.c_str());
    if(!query.exec()){
        qDebug()<<query.lastError();
        qFatal("Konnte die Lösch-Query nicht ausführen!");
        return false;
    }
    return true;
}
/**
 * @brief KlassenkameradDAO::organisatorEntSperren Entsperrt einen Organisator
 * @param ID Die Id des gesperrten Organisator
 * @param initialPasswort das neue Initialpasswort des Organisators
 * @return true bei Erfolg, false bei Fehlschlag
 */
bool KlassenkameradDAO::organisatorEntSperren(string ID,string initialPasswort){
    QSqlQuery query;
    query.prepare("UPDATE Organisator SET gesperrt=false, Passwort=:pw, Initialpasswort=false WHERE Organisator.Kamerad_ID=:id");
    query.bindValue(":id",ID.c_str());
    query.bindValue(":pw",initialPasswort.c_str());
    if(!query.exec()){
        return false;
    }
    return true;
}
/**
 * @brief KlassenkameradDAO::organisatorSperren Sperrt einen organisator
 * @param eMail Die E-Mail des zu sperrenden Organisators
 * @return true bei Erfolg, ansonsten false
 */
bool KlassenkameradDAO::organisatorSperren(string eMail){
    QSqlQuery query;
    query.prepare("SELECT Klassenkamerad.ID FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz AS KD ON(Klassenkamerad.ID=kd.Kamerad_ID)LEFT JOIN Organisator ON(Klassenkamerad.ID=Organisator.Kamerad_ID) WHERE kd.EMail=:email");
    query.bindValue(":email",eMail.c_str());
    if(!query.exec()||!query.next()){
        return false;
    }
    QSqlQuery query2;
    query2.prepare("UPDATE Organisator SET gesperrt=true WHERE Organisator.Kamerad_ID=:id");
    query2.bindValue(":id",query.value(0).toString());
    if(!query2.exec()) return false;
    //UPDATE Organisator SET gesperrt=true WHERE Organisator.Kamerad_ID=0
    /*QSqlQuery query;
    query.prepare("UPDATE Organisator SET Passwort=:pw ,Initialpasswort=false WHERE Kamerad_ID=:id");
    query.bindValue(":pw",passwort.c_str());
    query.bindValue(":id",akteurID.c_str());
    if(!query.exec()){
        return false;
    }
    return true;*/
    return true;
}
/**
 * @brief KlassenkameradDAO::removeOrganisator Entfernt einen Organisator (Rechte entzogen)
 * @param ID Die Id des Organisators
 * @return true bei Erfolg, ansonsten False
 */
bool KlassenkameradDAO::removeOrganisator(string ID){
    QSqlQuery query;
    query.prepare("DELETE FROM Organisator WHERE Organisator.Kamerad_ID=:id");
    query.bindValue(":id",ID.c_str());
    if(!query.exec()){
        qDebug()<<query.lastError();
        qFatal("Konnte die Lösch-Query nicht ausführen!");
        return false;
    }
    return true;
    }
/**
 * @brief KlassenkameradDAO::setOrganisator
 * @param ID
 * @param initialPasswort
 * @return true bei Erfolg, ansonsten False
 */
bool KlassenkameradDAO::setOrganisator(string ID,string initialPasswort){
    QSqlQuery query;
    query.prepare("INSERT INTO Organisator (Passwort,Initialpasswort,gesperrt,Kamerad_ID) VALUES (:pw,true,false,:id)");
    query.bindValue(":id",ID.c_str());
    query.bindValue(":pw",initialPasswort.c_str());
    if(!query.exec()){
        return false;
    }
    return true;
}
/**
 * @brief KlassenkameradDAO::einfuegen_HauptO Fügt einen Hauptorganisator hinzu (beim ersten Start)
 * @param daten Der verwendete Datensatz
 * @param passwort Das Passwort des HOs
 * @param master_passwort Das Masterpasswort des HOs
 * @return true bei Erfolg, ansonsten False
 */
bool KlassenkameradDAO::einfuegen_HauptO(KlassenkameradDatensatz* daten,string passwort,string master_passwort){
    QSqlQuery query;
    if(!query.exec("INSERT INTO Klassenkamerad(ID) VALUES(0)"))return false;
    query.prepare("INSERT INTO Organisator(Passwort,Initialpasswort,gesperrt,Kamerad_ID) VALUES(:pw,False,False,0)");
    query.bindValue(":pw",passwort.c_str());
    if(!query.exec())return false;
    query.prepare("INSERT INTO Hauptorganisator(Masterpasswort,Kamerad_ID) VALUES(:pw,0)");
    query.bindValue(":pw",master_passwort.c_str());
    if(!query.exec())return false;

    query.prepare("INSERT INTO Klassenkamerad_Datensatz (Vorname,Nachname,Nachname2,EMail,Strasse,Hausnummer,Ort,PLZ,Zeit,Tag,Organisator,Kamerad_ID) VALUES(:vorname,:nachname,:nachname2,:email,:strasse,:hnr,:ort,:plz,time('now'),date('now'),:organisator,0)");
    query.bindValue(":vorname",daten->vorname.c_str());
    query.bindValue(":nachname",daten->nachname[0].c_str());
    query.bindValue(":nachname2",daten->nachname[1].c_str());
    query.bindValue(":email",daten->eMail.c_str());
    query.bindValue(":strasse",daten->adresse.strasse.c_str());
    query.bindValue(":hnr",daten->adresse.hausnummer.c_str());
    query.bindValue(":ort",daten->adresse.ort.c_str());
    query.bindValue(":plz",daten->adresse.plz.c_str());
    query.bindValue(":organisator","0");
    if(!query.exec()){
        qFatal("Konnte keinen Datensatz anlegen!");
        return false;
    }
    //qDebug()<<daten.telefonnummer.size();
    for(unsigned long long i=0;i<daten->telefonnummer.size();i++){
        query.prepare("INSERT INTO Telefonnummer (Datensatz_ID,Telefonnummer) VALUES ((SELECT MAX(ID) FROM Klassenkamerad_Datensatz WHERE Kamerad_ID=0),:tele)");
        query.bindValue(":tele",daten->telefonnummer[i].c_str());
        if(!query.exec()){
            qFatal("Konnte keine Telefonnummer hinterlegen!");
            return false;
        }
    }
    query.prepare("SELECT Zeit,Tag FROM Klassenkamerad_Datensatz WHERE Klassenkamerad_Datensatz.Kamerad_ID=0");
    if(!query.exec() ||!query.next()){
        qFatal("Kann nicht den Zeitpunkt abrufen!");
        return false;
    }
    return true;
}
