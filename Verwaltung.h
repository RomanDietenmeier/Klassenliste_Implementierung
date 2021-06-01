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
#include <vector>

typedef struct {
    string eMail;
    int veruche;
}anmeldung;


class Verwaltung
{

public:
    vector<KlassenkameradDatensatz*> m_KlassenkameradDatensatz;
    vector<KlassenkameradDatensatz*> m_KlassenkameradAenderungshistorie;
    ListeView* m_ListeView;
    KlassenkameradDAO* m_KlassenkameradDAO;
    LoginView* m_LoginView;


	Verwaltung();
    ~Verwaltung();
    void init();
	void abmelden();
    bool anmelden(string eMail, string Passwort);
    bool klassenkameradBearbeiten(KlassenkameradDatensatz k);
    KlassenkameradDatensatz* klassenkameradenAktuelleDatensaetze();
    KlassenkameradDatensatz* klassenkameradHistorie(string klassenkameradID);
    bool klassenkameradLoeschen(string klassenkameradID);
    bool neuenKlassenkameradAnlegen(KlassenkameradDatensatz k);
    bool oranisatorRechteEntfernen(string ID);
    bool organisatorRechteVergeben(string ID);
    bool passwortAendern(string Passwort);

private:
    string akteurID;
    vector<anmeldung> anmeldeVersuche;

};
#endif // !defined(EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_)
