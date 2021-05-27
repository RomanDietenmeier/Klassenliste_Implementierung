///////////////////////////////////////////////////////////
//  KlassenkameradDatensatz.cpp
//  Implementation of the Class KlassenkameradDatensatz
//  Created on:      26-Mai-2021 15:45:18
//  Original author: Domenic
///////////////////////////////////////////////////////////

#include "KlassenkameradDatensatz.h"
#include<iostream>


KlassenkameradDatensatz::KlassenkameradDatensatz(){

}



KlassenkameradDatensatz::~KlassenkameradDatensatz(){

}

void KlassenkameradDatensatz::printToConsole(){

    std::cout<<klassenkameradID<<" | "<<vorname<<" | "<<nachname[0]<<" | "<<nachname[1]<<" | "<<eMail<<std::endl<<adresse.strasse<<" | "<<adresse.hausnummer<<" | "<<adresse.plz<<" | "<<adresse.ort<<std::endl;
    std::cout<<zeitpunkt.tag<<" | "<<zeitpunkt.monat<<" | "<<zeitpunkt.jahr<<std::endl;
    std::cout<<zeitpunkt.stunde<<" | "<<zeitpunkt.minute<<" | "<<zeitpunkt.sekunde<<std::endl;
}
