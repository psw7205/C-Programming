
// KeyboardAndTimer2.h : main header file for the KeyboardAndTimer2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKeyboardAndTimer2App:
// See KeyboardAndTimer2.cpp for the implementation of this class
//

class CKeyboardAndTimer2App : public CWinAppEx
{
public:
	CKeyboardAndTimer2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKeyboardAndTimer2App theApp;
