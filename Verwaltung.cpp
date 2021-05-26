///////////////////////////////////////////////////////////
//  Verwaltung.cpp
//  Implementation of the Class Verwaltung
//  Created on:      26-Mai-2021 15:42:37
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "Verwaltung.h"




Verwaltung::Verwaltung(){
    m_KlassenkameradDAO = new KlassenkameradDAO();
    m_KlassenkameradDatensatz = new KlassenkameradDatensatz();
}


Verwaltung::~Verwaltung(){

}


void Verwaltung::abmelden(){

}


bool Verwaltung::anmelden(string eMail, string Passwort){

	return  NULL;
}


bool Verwaltung::klassenkameradBearbeiten(KlassenkameradDatensatz k){

	return  NULL;
}


KlassenkameradDatensatz* Verwaltung::klassenkameradenAktuelleDatensaetze(){

	return  NULL;
}


KlassenkameradDatensatz* Verwaltung::klassenkameradHistorie(string klassenkameradID){

	return  NULL;
}


bool Verwaltung::klassenkameradLoeschen(string ID){

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
