
// Float.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFloatApp:
// See Float.cpp for the implementation of this class
//

class CFloatApp : public CWinApp
{
public:
	CFloatApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	ULONG_PTR m_gdiplusToken;
	virtual int ExitInstance();
};

extern CFloatApp theApp;