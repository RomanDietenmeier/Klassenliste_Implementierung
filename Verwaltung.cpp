///////////////////////////////////////////////////////////
//  Verwaltung.cpp
//  Implementation of the Class Verwaltung
//  Created on:      26-Mai-2021 15:42:37
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "Verwaltung.h"
#include <QDebug>
#include "newpasswort.h"


Verwaltung::Verwaltung(string akteurID){
    Verwaltung();
    this->akteurID=akteurID;

}

Verwaltung::Verwaltung(){
    akteurID="";

    m_KlassenkameradDAO->klassenkameradenLaden(m_KlassenkameradDatensatz);
    m_ListeView = new ListeView();

}


Verwaltung::~Verwaltung(){

}

//Alle Objekte zerstören und neue loginview erzeugen? Implementierung gegen Ende
void Verwaltung::abmelden(){

}

string Verwaltung::getAkteuerID(){
    return akteurID;
}

//veruche
int Verwaltung::anmelden(string eMail, string passwort){
    this->passwort = passwort;
    login_ret log = m_KlassenkameradDAO->anmeldedatenPruefen(eMail,passwort);
    qDebug()<< "initialpasswort: "<< log.initial_login;
    qDebug()<< "akteur: "<< log.id.c_str();

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


bool Verwaltung::klassenkameradBearbeiten(KlassenkameradDatensatz* k){
    if(m_KlassenkameradDAO->aktualisieren(k,akteurID)==true)
        return true;
    else
        return false;
}


vector<KlassenkameradDatensatz*> Verwaltung::klassenkameradenAktuelleDatensaetze(){
   if(m_KlassenkameradDatensatz.empty())
       m_KlassenkameradDAO->klassenkameradenLaden(m_KlassenkameradDatensatz);
   return m_KlassenkameradDatensatz;
}


vector<KlassenkameradDatensatz*> Verwaltung::klassenkameradHistorie(string klassenkameradID){
    m_KlassenkameradDAO->aenderungshistorieLaden(m_KlassenkameradAenderungshistorie,klassenkameradID);
    return m_KlassenkameradAenderungshistorie;
}


bool Verwaltung::klassenkameradLoeschen(string klassenkameradID){
    return m_KlassenkameradDAO->loeschen(klassenkameradID);
}


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


bool Verwaltung::passwortAendern(string newPasswort){
    if(newPasswort.compare(this->passwort)!=0)
        return m_KlassenkameradDAO->passwortAendern(newPasswort,akteurID);
    return false;
}
