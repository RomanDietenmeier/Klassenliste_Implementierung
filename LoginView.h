///////////////////////////////////////////////////////////
//  LoginView.h
//  Implementation of the Class LoginView
//  Created on:      26-Mai-2021 15:46:55
//  Original author: Domenic
///////////////////////////////////////////////////////////

#if !defined(EA_597CE96B_430B_4a78_9483_6CD36C4808B4__INCLUDED_)
#define EA_597CE96B_430B_4a78_9483_6CD36C4808B4__INCLUDED_

class Verwaltung;

class LoginView
{

public:
	LoginView();
    ~LoginView();
    Verwaltung* m_Verwaltung;

    void einloggen();

};
#endif // !defined(EA_597CE96B_430B_4a78_9483_6CD36C4808B4__INCLUDED_)
