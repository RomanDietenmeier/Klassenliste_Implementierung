///////////////////////////////////////////////////////////
//  KlassenkameradDatensatz.h
//  Implementation of the Class KlassenkameradDatensatz
//  Created on:      26-Mai-2021 15:45:18
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_F5D400D7_D52C_494c_9398_3316C29B30BA__INCLUDED_)
#define EA_F5D400D7_D52C_494c_9398_3316C29B30BA__INCLUDED_

#include <string>
#include<vector>
using namespace std;

typedef enum{Kamerad,Oragnisator,Hauptorganisator} Typ;

typedef struct {
    string strasse;
    string hausnummer;
    string ort;
    string plz;
}adresse;

typedef struct{
    int tag;
    int monat;
    int jahr;
    int stunde;
    int minute;
    int sekunde;
}zeitpunkt ;


class KlassenkameradDatensatz
{

public:
	KlassenkameradDatensatz();
	virtual ~KlassenkameradDatensatz();
	adresse adresse;
    string eMail;
	string klassenkameradID;
    string nachname[2];
    vector<string> telefonnummer;
	string vorname;
	zeitpunkt zeitpunkt;
    void printToConsole();
    Typ typ;
    static vector<KlassenkameradDatensatz*> getOrganisatoren(vector<KlassenkameradDatensatz*> vector);

};
#endif // !defined(EA_F5D400D7_D52C_494c_9398_3316C29B30BA__INCLUDED_)
