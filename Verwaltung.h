///////////////////////////////////////////////////////////
//  Verwaltung.h
//  Implementation of the Class Verwaltung
//  Created on:      26-Mai-2021 15:42:37
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_)
#define EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_

#include "KlassenkameradDatensatz.h"
#include "ListeView.h"
#include "KlassenkameradDAO.h"
#include "LoginView.h"

class Verwaltung
{

public:
	KlassenkameradDatensatz *m_KlassenkameradDatensatz;
	ListeView *m_ListeView;
	KlassenkameradDAO *m_KlassenkameradDAO;
	LoginView *m_LoginView;

	Verwaltung();
	void ~Verwaltung();
	void abmelden();
	boolean anmelden(string E-mail, string Passwort);
	boolean klassenkameradBearbeiten(KlassenkameradDatensatz k);
	klassenkameradDatensatz klassenkameradenAktuelleDatensätze();
	klassenkameradDatensatz[] klassenkameradHistorie(string klassenkameradID);
	boolean klassenkameradLöschen(string ID);
	boolean neuenKlassenkameradAnlegen(KlassenkameradDatensatz k);
	boolean oranisatorRechteEntfernen(string ID);
	boolean organisatorRechteVergeben(string ID);
	boolean passwortÄndern(string Passwort);

private:
	string aktuerID;

};
#endif // !defined(EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_)
