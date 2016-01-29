// Bill_DemoDlg.h : header file
//

#include "RS232.h"


#if !defined(AFX_BILL_DEMODLG_H__BF5F561A_AAB3_432E_9C06_521031EB8BC3__INCLUDED_)
#define AFX_BILL_DEMODLG_H__BF5F561A_AAB3_432E_9C06_521031EB8BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBill_DemoDlg dialog




class CBill_DemoDlg : public CDialog
{
// Construction
public:
	unsigned char CheckRXData;
	unsigned char SendInterval;
	unsigned char AutoStack;
	unsigned char AutoMode;
	void NoEventTXService();
	unsigned char ErrorStatus;
	unsigned char bAuto;
	unsigned int BillCount1, BillCount10, BillCount5, BillCount50;
	void DisplayActive(unsigned char data1, unsigned char data2);
	void SendPacket(unsigned char data1, unsigned char data2, unsigned char data3);
	CString PortNumber;
	unsigned char ActStatus;
	void DisplayBill(unsigned char BillKind);
	CRS232	Serial;
	unsigned char Serial_RBuffer[6];
	unsigned char RecevDataSerial();
	CBill_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBill_DemoDlg)
	enum { IDD = IDD_BILL_DEMO_DIALOG };
	CButton	m_auto;
	CButton	m_Inhibit;
	CComboBox	m_Port;
	CStatic	m_PIC5Won;
	CStatic	m_PIC10Won;
	CStatic	m_PIC1Won;
	CButton	m_UseEvent;
	CButton	m_Use5Won;
	CButton	m_Use50Won;
	CButton	m_Use1Won;
	CButton	m_Use10Won;
	CButton	m_AutoStack;
	CString	m_Ver;
	CString	m_RX;
	CString	m_TX;
	CString	m_StatusMSG;
	CString	m_BillCount1;
	CString	m_BillCount10;
	CString	m_BillCount5;
	CString	m_BillCount50;
	//CString	m_AutoMode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBill_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBill_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRDStatus();
	afx_msg void OnRDConfig();
	afx_msg void OnSetConfig();
	afx_msg void OnCon();
	afx_msg void OnRDVersion();
	afx_msg void OnInsertAmount();
	afx_msg void OnInhibit();
	afx_msg void OnStack();
	afx_msg void OnReturn();
	afx_msg void On9600bps();
	afx_msg void On4800bps();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChgport();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnAuto();
	afx_msg void OnReadErr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILL_DEMODLG_H__BF5F561A_AAB3_432E_9C06_521031EB8BC3__INCLUDED_)
