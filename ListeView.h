///////////////////////////////////////////////////////////
//  ListeView.h
//  Implementation of the Class ListeView
//  Created on:      26-Mai-2021 15:46:35
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_86366D34_CBEE_4fe6_874B_2A682AB1D442__INCLUDED_)
#define EA_86366D34_CBEE_4fe6_874B_2A682AB1D442__INCLUDED_

class Verwaltung;
#include "KlassenkameradDatensatz.h"
class ListeView
{

public:
	ListeView();
	virtual ~ListeView();
	Verwaltung *m_Verwaltung;

    void aktualisieren(KlassenkameradDatensatz &k);
    void aenderungshistorieLaden(KlassenkameradDatensatz &k);
    void hinzufuegen();
	void listeLaden();
    void loeschen(KlassenkameradDatensatz &k);
	void organisatorenVerwalten();
    void passwortAendern();
    void passwortAenderungBestaetigen();
	void speichern();

};
#endif // !defined(EA_86366D34_CBEE_4fe6_874B_2A682AB1D442__INCLUDED_)
