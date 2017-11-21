// bankerView.h : main header file for the BANKERVIEW application
//

#if !defined(AFX_BANKERVIEW_H__D09007BD_5B94_4957_9170_F1A783AA9474__INCLUDED_)
#define AFX_BANKERVIEW_H__D09007BD_5B94_4957_9170_F1A783AA9474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBankerViewApp:
// See bankerView.cpp for the implementation of this class
//

class CBankerViewApp : public CWinApp
{
public:
	CBankerViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankerViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBankerViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKERVIEW_H__D09007BD_5B94_4957_9170_F1A783AA9474__INCLUDED_)
