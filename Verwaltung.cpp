///////////////////////////////////////////////////////////
//  Verwaltung.cpp
//  Implementation of the Class Verwaltung
//  Created on:      26-Mai-2021 15:42:37
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "Verwaltung.h"




Verwaltung::Verwaltung(){
    m_KlassenkameradDAO = new KlassenkameradDAO();
    m_LoginView = new LoginView();

    m_LoginView->einloggen();
    m_KlassenkameradDatensatz = m_KlassenkameradDAO->klassenkameradenLaden();
    m_ListeView = new ListeView();

}


Verwaltung::~Verwaltung(){

}


void Verwaltung::abmelden(){

}


bool Verwaltung::anmelden(string eMail, string Passwort){
    akteurID = m_KlassenkameradDAO->anmeldedatenPruefen(eMail,Passwort);
    if(akteurID.compare("-1")){
        for(anmeldung a: anmeldeVersuche){
            if(a.eMail.compare(eMail)==0){
                if(a.veruche<3)
                    a.veruche++;
                else{
                    m_KlassenkameradDAO->organisatorSperren(eMail);
                }
                return false;
            }
        }
        anmeldung versuch;
        versuch.eMail = eMail;
        versuch.veruche = 1;
        anmeldeVersuche.push_back(versuch);
        return false;
    }
    else if(akteurID.compare("2"))
        return false;
    return true;
}


bool Verwaltung::klassenkameradBearbeiten(KlassenkameradDatensatz k){
    if(m_KlassenkameradDAO->aktualisieren(k)==true)
        return true;
    else
        return false;
}


KlassenkameradDatensatz* Verwaltung::klassenkameradenAktuelleDatensaetze(){

	return  NULL;
}


KlassenkameradDatensatz* Verwaltung::klassenkameradHistorie(string klassenkameradID){

	return  NULL;
}


bool Verwaltung::klassenkameradLoeschen(string klassenkameradID){
    m_KlassenkameradDAO->loeschen(klassenkameradID);
	return  NULL;
}


bool Verwaltung::neuenKlassenkameradAnlegen(KlassenkameradDatensatz k){

	return  NULL;
}


bool Verwaltung::oranisatorRechteEntfernen(string ID){

	return  NULL;
}


bool Verwaltung::organisatorRechteVergeben(string ID){

	return  NULL;
}


bool Verwaltung::passwortAendern(string Passwort){

	return  NULL;
}
