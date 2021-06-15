///////////////////////////////////////////////////////////
//  Verwaltung.h
//  Implementation of the Class Verwaltung
//  Created on:      26-Mai-2021 15:42:37
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_)
#define EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_

#include "KlassenkameradDatensatz.h"
#include "KlassenkameradDAO.h"
#include <vector>

typedef struct {
    string eMail;
    int versuche;
}anmeldung;


class Verwaltung
{

public:
    string akteurID;
    KlassenkameradDAO* m_KlassenkameradDAO;
    KlassenkameradDatensatz* akteur;


	Verwaltung();
    //für Testzwecke
    /**
     * @brief Verwaltung::Verwaltung ruft Klassenkameraden laden auf
     */
    Verwaltung(string akteurID);
    ~Verwaltung();
    void init();
	void abmelden();
    /**
     * @brief Verwaltung::anmelden anmelde Logik, bei noch aktuellen Initialpasswort wird ein neues gefordert, bei mehrmaligem falschanmelden wird gespert.
     * @param eMail
     * @param passwort
     * @return
     */
    int anmelden(string eMail, string Passwort);
    /**
     * @brief Verwaltung::klassenkameradBearbeiten aktualisiert den Entsprechenden Klassenkamerad
     * @param k
     * @return
     */
    bool klassenkameradBearbeiten(KlassenkameradDatensatz* k);
    /**
     * @brief Verwaltung::klassenkameradenAktuelleDatensaetze
     * @return
     */
    vector<KlassenkameradDatensatz*> klassenkameradenAktuelleDatensaetze();
    /**
     * @brief Verwaltung::klassenkameradHistorie Lädt änderungshistorie
     * @param klassenkameradID
     * @return
     */
    vector<KlassenkameradDatensatz*> klassenkameradHistorie(string klassenkameradID);
    /**
     * @brief Verwaltung::klassenkameradLoeschen Löscht klassenkamerad
     * @param klassenkameradID
     * @return
     */
    bool klassenkameradLoeschen(string klassenkameradID);
    /**
     * @brief Verwaltung::neuenKlassenkameradAnlegen legt neuen Klassenkamerad an
     * @param k
     * @return
     */
    bool neuenKlassenkameradAnlegen(KlassenkameradDatensatz* k);
    bool oranisatorRechteEntfernen(string ID);
    bool organisatorRechteVergeben(string ID);
    /**
     * @brief Verwaltung::passwortAendern
     * @param newPasswort
     * @return
     */
    bool passwortAendern(string Passwort);
    /**
     * @brief Verwaltung::getAkteuerID
     * @return
     */
    string getAkteuerID();

private:

    string passwort;
    vector<anmeldung*> anmeldeVersuche;
    vector<KlassenkameradDatensatz*> m_KlassenkameradDatensatz;
    vector<KlassenkameradDatensatz*> m_KlassenkameradAenderungshistorie;

};
#endif // !defined(EA_16A229CD_1BD2_4501_93CB_60391B7C0DEA__INCLUDED_)
