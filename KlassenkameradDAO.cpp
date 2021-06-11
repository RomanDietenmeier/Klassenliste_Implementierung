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
                   qFatal("ERROR");
               }
               query.finish();
           }
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
    query.prepare("SELECT Klassenkamerad.ID,Organisator.Passwort,Organisator.gesperrt,Organisator.Initialpasswort FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz AS KD ON(Klassenkamerad.ID=kd.Kamerad_ID)LEFT JOIN Organisator ON(Klassenkamerad.ID=Organisator.Kamerad_ID) WHERE kd.EMail=:email");
    query.bindValue(":email",eMail.c_str());
    if(!query.exec() || !query.next()|| query.value(2).toBool()||(0!=query.value(1).toString().toStdString().compare(passwort)||query.value(3).isNull() )){
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
