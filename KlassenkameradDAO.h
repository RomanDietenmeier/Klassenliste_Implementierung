///////////////////////////////////////////////////////////
//  KlassenkameradDAO.h
//  Implementation of the Class KlassenkameradDAO
//  Created on:      26-Mai-2021 15:47:10
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_)
#define EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_

#include "Verwaltung.h"

class KlassenkameradDAO
{

public:
	KlassenkameradDAO();
	virtual ~KlassenkameradDAO();
	Verwaltung *m_Verwaltung;

	boolean aktualisieren(KlassenkameradDatensatz daten);
	KlassenkameradDatensatz[] �nderungshistorieLaden(string klassenkameradID);
	string anmeldedatenPr�fen(string e-Mail, string passwort);
	boolean einf�gen(KlassenkameradDatensatz daten);
	boolean initialPasswort�ndern(string passwort, string akteurID);
	KlassenkameradDatensatz[] klassenkameradenLaden();
	boolean l�schen(Klassenkamerad k);
	boolean organisatorSperren(Klassenkamerad organisator);
	boolean removeOrganisator(string ID);
	boolean setOrganisator(string ID);

};
#endif // !defined(EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_)
