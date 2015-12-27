
// LFP_Demo_Dialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLFP_Demo_DialogApp:
// See LFP_Demo_Dialog.cpp for the implementation of this class
//

class CLFP_Demo_DialogApp : public CWinAppEx
{
public:
	CLFP_Demo_DialogApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLFP_Demo_DialogApp theApp;