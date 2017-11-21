// bankerViewDlg.h : header file
//

#if !defined(AFX_BANKERVIEWDLG_H__20BA4380_2BE4_4EB3_A542_FE57505FD69F__INCLUDED_)
#define AFX_BANKERVIEWDLG_H__20BA4380_2BE4_4EB3_A542_FE57505FD69F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBankerViewDlg dialog

class CBankerViewDlg : public CDialog
{
// Construction
public:
	CBankerViewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBankerViewDlg)
	enum { IDD = IDD_BANKERVIEW_DIALOG };
	int		m_progessNum;
	int		m_request1;
	int		m_request2;
	int		m_request3;
	int		m_request4;
	int		m_bestrequest1;
	int		m_bestrequest2;
	int		m_bestrequest3;
	int		m_bestrequest4;
	CString	m_ansStr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankerViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBankerViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKERVIEWDLG_H__20BA4380_2BE4_4EB3_A542_FE57505FD69F__INCLUDED_)
