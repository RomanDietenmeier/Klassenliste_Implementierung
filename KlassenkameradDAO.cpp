///////////////////////////////////////////////////////////
//  KlassenkameradDAO.cpp
//  Implementation of the Class KlassenkameradDAO
//  Created on:      26-Mai-2021 15:47:10
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "KlassenkameradDAO.h"
#include <QDebug>
#include <QSqlQuery>


KlassenkameradDAO::KlassenkameradDAO(){
   QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName("Robert.db");

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}



KlassenkameradDAO::~KlassenkameradDAO(){

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
bool KlassenkameradDAO::einfuegen(KlassenkameradDatensatz daten){
    return false;
}
bool KlassenkameradDAO::initialPasswortAendern(string passwort, string akteurID){
    return false;
}
bool KlassenkameradDAO::klassenkameradenLaden(std::vector<KlassenkameradDatensatz*> &kd){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM Klassenkamerad LEFT JOIN Klassenkamerad_Datensatz ON (Klassenkamerad.ID=Klassenkamerad_Datensatz.Kamerad_ID)")){
        return false;
    }
    while(query.next()){
        KlassenkameradDatensatz* z_kd=new KlassenkameradDatensatz();
        z_kd->vorname=query.value(2).toString().toLocal8Bit().constData();
        z_kd->nachname=query.value(3).toString().toLocal8Bit().constData();
        z_kd->klassenkameradID;
        kd.push_back(z_kd);
    }
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
