
// Labaratornya7.h : main header file for the Labaratornya7 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLabaratornya7App:
// See Labaratornya7.cpp for the implementation of this class
//

class CLabaratornya7App : public CWinApp
{
public:
	CString deffile;
	CLabaratornya7App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnChangeWidth();

	DECLARE_MESSAGE_MAP()
};

extern CLabaratornya7App theApp;
