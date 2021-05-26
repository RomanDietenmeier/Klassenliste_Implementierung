///////////////////////////////////////////////////////////
//  KlassenkameradDAO.cpp
//  Implementation of the Class KlassenkameradDAO
//  Created on:      26-Mai-2021 15:47:10
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "KlassenkameradDAO.h"


KlassenkameradDAO::KlassenkameradDAO(){

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
KlassenkameradDatensatz* KlassenkameradDAO::klassenkameradenLaden(){
    return NULL;
}
bool KlassenkameradDAO::loeschen(KlassenkameradDatensatz k){
    return false;
}
bool KlassenkameradDAO::organisatorSperren(KlassenkameradDatensatz organisator){
    return false;
}
bool KlassenkameradDAO::removeOrganisator(string ID){
    return false;
}
bool KlassenkameradDAO::setOrganisator(string ID){
    return false;
}
