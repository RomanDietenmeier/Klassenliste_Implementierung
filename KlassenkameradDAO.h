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
#include <QMainWindow>
#include <stdexcept>

typedef struct{
    string id;
    bool initial_login;
} login_ret;


class KlassenkameradDAO
{
    QSqlDatabase m_db;

public:
    KlassenkameradDAO(std::string pfad);
	virtual ~KlassenkameradDAO();
	Verwaltung *m_Verwaltung;
    bool initial=false;

    bool test();
    bool clean();
    bool aktualisieren(KlassenkameradDatensatz* daten,string akteurID);
    bool aenderungshistorieLaden(vector<KlassenkameradDatensatz*> &kd,string klassenkameradID);
    login_ret anmeldedatenPruefen(string eMail, string passwort);
    bool einfuegen(KlassenkameradDatensatz* daten,string akteurID);
    bool einfuegen_HauptO(KlassenkameradDatensatz* daten,string passwort,string master_passwort);
    bool passwortAendern(string passwort, string akteurID);
    bool klassenkameradenLaden(std::vector<KlassenkameradDatensatz*> &kd);
    bool loeschen(string ID);
    bool organisatorSperren(string eMail);
    bool organisatorEntSperren(string ID,string initialPasswort);
    bool removeOrganisator(string ID);
    bool setOrganisator(string ID,string initialPasswort);

};
#endif // !defined(EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_)
