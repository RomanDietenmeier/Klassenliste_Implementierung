///////////////////////////////////////////////////////////
//  KlassenkameradDatensatz.h
//  Implementation of the Class KlassenkameradDatensatz
//  Created on:      26-Mai-2021 15:45:18
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_F5D400D7_D52C_494c_9398_3316C29B30BA__INCLUDED_)
#define EA_F5D400D7_D52C_494c_9398_3316C29B30BA__INCLUDED_

#include "Verwaltung.h"

class KlassenkameradDatensatz
{

public:
	KlassenkameradDatensatz();
	virtual ~KlassenkameradDatensatz();
	adresse adresse;
	string e-mail;
	string klassenkameradID;
	string nachname;
	string telefonnummer;
	string vorname;
	zeitpunkt zeitpunkt;
	Verwaltung *m_Verwaltung;

};
#endif // !defined(EA_F5D400D7_D52C_494c_9398_3316C29B30BA__INCLUDED_)
