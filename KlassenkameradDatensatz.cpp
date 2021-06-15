///////////////////////////////////////////////////////////
//  KlassenkameradDatensatz.cpp
//  Implementation of the Class KlassenkameradDatensatz
//  Created on:      26-Mai-2021 15:45:18
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "KlassenkameradDatensatz.h"
#include<iostream>

using namespace std;

KlassenkameradDatensatz::KlassenkameradDatensatz(){
    adresse.hausnummer="";
    adresse.ort="";
    adresse.plz="";
    adresse.strasse="";
    eMail="";
    klassenkameradID="";
    nachname[0]="";
    nachname[1]="";
    vorname="";
    zeitpunkt.jahr=-1;
    zeitpunkt.minute=-1;
    zeitpunkt.monat=-1;
    zeitpunkt.sekunde=-1;
    zeitpunkt.stunde=-1;
    zeitpunkt.tag=-1;
}



KlassenkameradDatensatz::~KlassenkameradDatensatz(){

}
/**
 * @brief KlassenkameradDatensatz::getGesperrte Gibt neuen Vektor zurück mit nur gesperrten Datensätze
 * @param vector Übergibt Vektor mit Datensätzen
 * @return true bei Erfolg, ansonsten False
 */
vector<KlassenkameradDatensatz*> KlassenkameradDatensatz::getGesperrte(vector<KlassenkameradDatensatz*> vector){
    std::vector<KlassenkameradDatensatz*> ret;
    for(unsigned long long i=0;i<vector.size();i++){
        if(vector[i]->gespert==true){
            ret.push_back(vector[i]);
        }
    }
    return ret;
}
/**
 * @brief KlassenkameradDatensatz::getOrganisatoren Gibt neuen Vektor zurück mit nur Organisatoren Datensätze
 * @param vector Übergibt Vektor mit Datensätzen
 * @return true bei Erfolg, ansonsten False
 */
vector<KlassenkameradDatensatz*> KlassenkameradDatensatz::getOrganisatoren(vector<KlassenkameradDatensatz*> vector){
    std::vector<KlassenkameradDatensatz*> ret;
    for(unsigned long long i=0;i<vector.size();i++){
        if(vector[i]->typ==Oragnisator || vector[i]->typ==Hauptorganisator){
            ret.push_back(vector[i]);
        }
    }
    return ret;
}
/**
 * @brief KlassenkameradDatensatz::printToConsole Gitb die Daten in der Konsole aus
 */
void KlassenkameradDatensatz::printToConsole(){

    std::cout<<klassenkameradID<<" | "<<vorname<<" | "<<nachname[0]<<" | "<<nachname[1]<<" | "<<eMail<<std::endl;
    std::cout<<adresse.strasse<<" "<<adresse.hausnummer<<" | "<<adresse.plz<<" | "<<adresse.ort<<std::endl;
    std::cout<<zeitpunkt.tag<<" | "<<zeitpunkt.monat<<" | "<<zeitpunkt.jahr<<std::endl;
    std::cout<<zeitpunkt.stunde<<" | "<<zeitpunkt.minute<<" | "<<zeitpunkt.sekunde<<std::endl;
    for(int i=0;i<telefonnummer.size();i++){
        std::cout<<telefonnummer[i];
        if(i<telefonnummer.size()-1)
            std::cout<<" | ";
    }
    std::cout<<std::endl;
}
