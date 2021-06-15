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
    /**
     * @brief KlassenkameradDAO::KlassenkameradDAO öffnet die Datenbank falls vorhanden, oder baut die Struktur in einer neuen Datei auf
     * @param pfad Pfad zur SQLite Datei. Sollte keine existieren, so ist der Pfad der Ort an dem die Datei angelegt wird.
     */
    KlassenkameradDAO(std::string pfad);
	virtual ~KlassenkameradDAO();
	Verwaltung *m_Verwaltung;
    bool initial=false;
    /**
     * @brief KlassenkameradDAO::test verwirft(falls vorhanden) alte Datenbank und baut die Datenbank mit Testdaten neu auf.
     * @return true bei Erfolg, false bei Fehlschlag
     */
    bool test();
    /**
     * @brief KlassenkameradDAO::clean leert den kompletten Dateninhalt der Datenbank
     * @return true bei Erfolg, false bei Fehlschlag
     */
    bool clean();
    /**
     * @brief KlassenkameradDAO::aktualisieren legt einen neuen Datensatz an für ein bestehendes Klassenmitglied.
     * @param daten Der Datensatz mit den neuen Dateien. Bei diesem wird der Zeitpunkt mit der Ausführung aktualisiert.
     * @param akteurID Der Organisator der die Änderung vornimmt.
     * @return true bei Erfolg, false bei Fehlschlag
     */
    bool aktualisieren(KlassenkameradDatensatz* daten,string akteurID);
    /**
     * @brief KlassenkameradDAO::aenderungshistorieLaden Zeigt die Änderungshistorie eines Eintrags
     * @param kd Vektor mit den Datensätzen
     * @param klassenkameradID Die Id des Klassenkameradens, von dem die Historie angeschaut wird.
     * @return true bei Erfolg, ansonsten false
     */
    bool aenderungshistorieLaden(vector<KlassenkameradDatensatz*> &kd,string klassenkameradID);
    login_ret anmeldedatenPruefen(string eMail, string passwort);
    /**
     * @brief KlassenkameradDAO::einfuegen Fügt einen neuen Klassenkameraden der Datenbank hinzu.
     * @param daten Die Daten des neuen Kameraden. Der Zeitpunkt wird mit ausführung der Methode aktualisiert.
     * @param akteurID Der Organisator der den Klassenkameraden einfügt.
     * @return
     */
    bool einfuegen(KlassenkameradDatensatz* daten,string akteurID);
    /**
     * @brief KlassenkameradDAO::einfuegen_HauptO Fügt einen Hauptorganisator hinzu (beim ersten Start)
     * @param daten Der verwendete Datensatz
     * @param passwort Das Passwort des HOs
     * @param master_passwort Das Masterpasswort des HOs
     * @return true bei Erfolg, ansonsten False
     */
    bool einfuegen_HauptO(KlassenkameradDatensatz* daten,string passwort,string master_passwort);
    /**
     * @brief KlassenkameradDAO::passwortAendern ändert das Passwort eines Organisators.
     * @param passwort das neue Passwort.
     * @param akteurID der Organisator, dessen Passwort geändert wird.
     * @return
     */
    bool passwortAendern(string passwort, string akteurID);
    /**
     * @brief KlassenkameradDAO::klassenkameradenLaden Lädt alle aktuellen Klassenkameraden Datensätze
     * @param kd Vector zu dem die Klassenkameraden hinzugefügt werden sollen
     * @return true bei Erfolg, oder false bei Abbruch
     */
    bool klassenkameradenLaden(std::vector<KlassenkameradDatensatz*> &kd);
    /**
     * @brief KlassenkameradDAO::loeschen löscht alle Einträge in Bezug auf den Kameraden mit der übergebenen ID-
     * @param ID Die Id des zu löschenden Klassenkameraden.
     * @return true bei Erfolg, false bei Fehlschlag
     */
    bool loeschen(string ID);
    /**
     * @brief KlassenkameradDAO::organisatorSperren Sperrt einen organisator
     * @param eMail Die E-Mail des zu sperrenden Organisators
     * @return true bei Erfolg, ansonsten false
     */
    bool organisatorSperren(string eMail);
    /**
     * @brief KlassenkameradDAO::organisatorEntSperren Entsperrt einen Organisator
     * @param ID Die Id des gesperrten Organisator
     * @param initialPasswort das neue Initialpasswort des Organisators
     * @return true bei Erfolg, false bei Fehlschlag
     */
    bool organisatorEntSperren(string ID,string initialPasswort);
    /**
     * @brief KlassenkameradDAO::removeOrganisator Entfernt einen Organisator (Rechte entzogen)
     * @param ID Die Id des Organisators
     * @return true bei Erfolg, ansonsten False
     */
    bool removeOrganisator(string ID);
    /**
     * @brief KlassenkameradDAO::setOrganisator
     * @param ID
     * @param initialPasswort
     * @return true bei Erfolg, ansonsten False
     */
    bool setOrganisator(string ID,string initialPasswort);

};
#endif // !defined(EA_32BE42DF_F426_41ed_A28D_45636761C63D__INCLUDED_)
