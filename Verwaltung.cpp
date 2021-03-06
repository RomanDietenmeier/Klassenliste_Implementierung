///////////////////////////////////////////////////////////
//  Verwaltung.cpp
//  Implementation of the Class Verwaltung
//  Created on:      26-Mai-2021 15:42:37
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "Verwaltung.h"
#include <QDebug>
#include "newpasswort.h"

/**
 * @brief Verwaltung::Verwaltung
 * @param akteurID
 */
Verwaltung::Verwaltung(string akteurID){
    Verwaltung();
    this->akteurID=akteurID;

}

/**
 * @brief Verwaltung::Verwaltung ruft Klassenkameraden laden auf
 */
Verwaltung::Verwaltung(){
    akteurID="";
    m_KlassenkameradDAO->klassenkameradenLaden(m_KlassenkameradDatensatz);

}


Verwaltung::~Verwaltung(){

}


//Alle Objekte zerstören und neue loginview erzeugen? Implementierung gegen Ende
void Verwaltung::abmelden(){

}

/**
 * @brief Verwaltung::getAkteuerID
 * @return
 */
string Verwaltung::getAkteuerID(){
    return akteurID;
}

/**
 * @brief Verwaltung::anmelden anmelde Logik, bei noch aktuellen Initialpasswort wird ein neues gefordert, bei mehrmaligem falschanmelden wird gespert.
 * @param eMail
 * @param passwort
 * @return
 */
int Verwaltung::anmelden(string eMail, string passwort){
    this->passwort = passwort;
    login_ret log = m_KlassenkameradDAO->anmeldedatenPruefen(eMail,passwort);
    qDebug()<< "initialpasswort: "<< log.initial_login;
    qDebug()<< "akteur: "<< log.id.c_str();
    //this->akteurID=log.id;

    akteurID = log.id;
    if(akteurID.compare("-1")==0){
        for(anmeldung* a: anmeldeVersuche){
            if(a->eMail.compare(eMail)==0){
                if(a->versuche<3)
                    a->versuche++;
                else{
                    m_KlassenkameradDAO->organisatorSperren(eMail);
                    qDebug()<<"-2";
                    return -2;
                }
                return -1;
            }
        }
        anmeldung* versuch = new anmeldung();
        versuch->eMail = eMail;
        versuch->versuche = 1;
        anmeldeVersuche.push_back(versuch);
        return -1;
    }

    if(log.initial_login==true){
        return -3;
    }
    return 0;

}

/**
 * @brief Verwaltung::klassenkameradBearbeiten aktualisiert den Entsprechenden Klassenkamerad
 * @param k
 * @return
 */
bool Verwaltung::klassenkameradBearbeiten(KlassenkameradDatensatz* k){
    if(m_KlassenkameradDAO->aktualisieren(k,akteurID)==true)
        return true;
    else
        return false;
}

/**
 * @brief Verwaltung::klassenkameradenAktuelleDatensaetze
 * @return
 */
vector<KlassenkameradDatensatz*> Verwaltung::klassenkameradenAktuelleDatensaetze(){
   if(m_KlassenkameradDatensatz.empty())
       m_KlassenkameradDAO->klassenkameradenLaden(m_KlassenkameradDatensatz);
   return m_KlassenkameradDatensatz;
}

/**
 * @brief Verwaltung::klassenkameradHistorie Lädt änderungshistorie
 * @param klassenkameradID
 * @return
 */
vector<KlassenkameradDatensatz*> Verwaltung::klassenkameradHistorie(string klassenkameradID){
    m_KlassenkameradDAO->aenderungshistorieLaden(m_KlassenkameradAenderungshistorie,klassenkameradID);
    return m_KlassenkameradAenderungshistorie;
}

/**
 * @brief Verwaltung::klassenkameradLoeschen Löscht klassenkamerad
 * @param klassenkameradID
 * @return
 */
bool Verwaltung::klassenkameradLoeschen(string klassenkameradID){
    return m_KlassenkameradDAO->loeschen(klassenkameradID);
}

/**
 * @brief Verwaltung::neuenKlassenkameradAnlegen legt neuen Klassenkamerad an
 * @param k
 * @return
 */
bool Verwaltung::neuenKlassenkameradAnlegen(KlassenkameradDatensatz* k){
    if(m_KlassenkameradDAO->einfuegen(k,akteurID)){
        m_KlassenkameradDatensatz.push_back(k);
        return true;
    }
    return false;
}

//Gibt es extra Button für den Hauptorganisator?
bool Verwaltung::oranisatorRechteEntfernen(string ID){

    return  NULL;
}

//Gibt es extra Button für den Hauptorganisator?
bool Verwaltung::organisatorRechteVergeben(string ID){

    return  NULL;
}

/**
 * @brief Verwaltung::passwortAendern
 * @param newPasswort
 * @return
 */
bool Verwaltung::passwortAendern(string newPasswort){
    if(newPasswort.compare(this->passwort)!=0)
        return m_KlassenkameradDAO->passwortAendern(newPasswort,akteurID);
    return false;
}
