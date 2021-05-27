///////////////////////////////////////////////////////////
//  KlassenkameradDAO.h
//  Implementation of the Class KlassenkameradDAO
//  Created on:      26-Mai-2021 15:47:10
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_)
#define EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_

class Verwaltung;
#include"KlassenkameradDatensatz.h"
#include <QSqlDatabase>
#include<vector>

class KlassenkameradDAO
{
    QSqlDatabase m_db;

public:
    KlassenkameradDAO(std::string pfad);
	virtual ~KlassenkameradDAO();
	Verwaltung *m_Verwaltung;

    bool aktualisieren(KlassenkameradDatensatz daten);
    KlassenkameradDatensatz* aenderungshistorieLaden(string klassenkameradID);
    string anmeldedatenPruefen(string eMail, string passwort);
    bool einfuegen(KlassenkameradDatensatz daten);
    bool initialPasswortAendern(string passwort, string akteurID);
    bool klassenkameradenLaden(std::vector<KlassenkameradDatensatz*> &kd);
    bool loeschen(KlassenkameradDatensatz k);
    bool organisatorSperren(string eMail);
    bool removeOrganisator(string ID);
    bool setOrganisator(string ID);

};
#endif // !defined(EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_)
