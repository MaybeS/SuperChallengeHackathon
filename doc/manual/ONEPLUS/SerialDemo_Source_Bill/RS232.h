#if !defined(AFX_RS232_H__51D2BF5B_723F_4C34_8047_A9726EBA7D24__INCLUDED_)
#define AFX_RS232_H__51D2BF5B_723F_4C34_8047_A9726EBA7D24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RS232.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRS232 thread

class CRS232 : public CWinThread
{
	DECLARE_DYNCREATE(CRS232)
protected:
	    // protected constructor used by dynamic creation

// Attributes
public:
   CRS232(); 
	virtual ~CRS232();
// Operations
public:
	BOOL OpenPort(CString sPortName, DWORD dwBaud, WORD wParam);
	BOOL isProcessingOk;

	//--------- 환경 변수 -----------------------------------------//
	HANDLE		m_hComm;				// 통신 포트 파일 핸들
	CString		m_sPortName;			// 포트 이름 (COM1 ..)
	BOOL		m_bConnected;			// 포트가 열렸는지 유무를 나타냄.
	HANDLE		m_hThreadWatchComm;		// Watch함수 Thread 핸들.
	WORD		m_wPortID;				// WM_COMM_READ와 함께 보내는 인수.
	CString		cdmaBuffer;

	//--------- 외부 사용 함수 ------------------------------------//
	void	ClosePort();
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);

    //--------- 내부 사용 함수 ------------------------------------//
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRS232)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRS232)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS232_H__51D2BF5B_723F_4C34_8047_A9726EBA7D24__INCLUDED_)
