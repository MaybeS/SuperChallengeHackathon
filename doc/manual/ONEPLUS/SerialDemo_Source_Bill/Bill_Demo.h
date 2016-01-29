// Bill_Demo.h : main header file for the BILL_DEMO application
//

#if !defined(AFX_BILL_DEMO_H__73FE30BB_777D_4F0C_8E49_F7D2E091E8CE__INCLUDED_)
#define AFX_BILL_DEMO_H__73FE30BB_777D_4F0C_8E49_F7D2E091E8CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "RS232.h"

/////////////////////////////////////////////////////////////////////////////
// CBill_DemoApp:
// See Bill_Demo.cpp for the implementation of this class
//

class CBill_DemoApp : public CWinApp
{
public:
	CBill_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBill_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBill_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILL_DEMO_H__73FE30BB_777D_4F0C_8E49_F7D2E091E8CE__INCLUDED_)
