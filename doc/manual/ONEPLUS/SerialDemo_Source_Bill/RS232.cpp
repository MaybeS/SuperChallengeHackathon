// RS232.cpp : implementation file
//

#include "stdafx.h"
#include "RS232.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRS232

IMPLEMENT_DYNCREATE(CRS232, CWinThread)

CRS232::CRS232()
{
	m_bConnected = FALSE;	
}

CRS232::~CRS232()
{
}

BOOL CRS232::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CRS232::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRS232, CWinThread)
	//{{AFX_MSG_MAP(CRS232)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRS232 message handlers

extern HWND hCommWnd;

//��Ʈ ���� �ϰ� ������ ���� 
BOOL CRS232::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID)
{
	

  cdmaBuffer = _T("");
  DCB PortDCB;
  COMMTIMEOUTS CommTimeouts;  

  // ��Ʈ ���� �ϱ� 
  m_hComm = CreateFile (sPortName, 
	                    GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

   
  // ���� �����ϸ� false ���� 
  if ( m_hComm == INVALID_HANDLE_VALUE ) 
  {
	  return FALSE;
  }
  
  PortDCB.DCBlength = sizeof (DCB);     

  // ����Ʈ ��Ʈ ���� �� �������� 
  GetCommState (m_hComm, &PortDCB);

  // PortDCB ���� �� ���� 
  PortDCB.BaudRate = dwBaud;              // Current baud 
  PortDCB.fBinary = TRUE;               // Binary mode; no EOF check 
  PortDCB.fParity = TRUE;               // Enable parity checking. 
  PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control 
  PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control 
//PortDCB.fDtrControl = DTR_CONTROL_ENABLE; 
  PortDCB.fDtrControl = DTR_CONTROL_DISABLE; 
                                        // DTR flow control type 
  PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity 
  PortDCB.fTXContinueOnXoff = TRUE;     // XOFF continues Tx 
  PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control 
  PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control 
  PortDCB.fErrorChar = FALSE;           // Disable error replacement. 
  PortDCB.fNull = FALSE;                // Disable null stripping. 
//  PortDCB.fRtsControl = RTS_CONTROL_ENABLE; 
  PortDCB.fRtsControl = RTS_CONTROL_DISABLE; 
                                        // RTS flow control 
  PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on 
                                        // error.
  PortDCB.ByteSize = 8;                 // Number of bits/bytes, 4-8 
  PortDCB.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space 
  PortDCB.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2 

  // ����� PortDCB �� ���� 
  if (!SetCommState (m_hComm, &PortDCB))
  {
   // AfxMessageBox(_T("�ø��� ��Ʈ�� �����Ҽ� �����ϴ�."));
    return FALSE;
  }

  // ��Ʈ�� read write Ÿ�Ӿƿ� �ð� ���� ������ 
  GetCommTimeouts (m_hComm, &CommTimeouts);

  // Ÿ�Ծƿ� ��Ʈ���� ���� �ٽ� ���� �� 
  CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
  CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
  CommTimeouts.ReadTotalTimeoutConstant = 0;    
  CommTimeouts.WriteTotalTimeoutMultiplier = 10;  
  CommTimeouts.WriteTotalTimeoutConstant = 1000;    

  // Ÿ�Ӿƿ� ���� �����ϱ� 
  if (!SetCommTimeouts (m_hComm, &CommTimeouts))
  {
    // AfxMessageBox(_T("�ø��� ��Ʈ�� Ÿ�Ӿƿ� ���� �����Ҽ� �����ϴ�.")); 
    return FALSE;
  }

  
  EscapeCommFunction (m_hComm, SETDTR);
  EscapeCommFunction (m_hComm, SETRTS);

  m_bConnected = TRUE;

// ��Ʈ ���� ������ ����.
//	if(!RunThread()){
//		return FALSE;
//	}
	return TRUE;
}

// ��Ʈ�� pBuff�� ������ nToWrite��ŭ ����.
// ������ ������ Byte���� �����Ѵ�.
DWORD CRS232::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD dwNumBytesWritten,dwErrorFlags;
	COMSTAT	comstat;

	if(!WriteFile (m_hComm,             
				   pBuff,              
				   nToWrite,
				   &dwNumBytesWritten,
				   NULL))

	{
		// write ���� ó���� write�� ����Ʈ���� �Ǵ��Ѵ�. 	
	}
	else
	{
		//write ���� 
		ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	}

	return dwNumBytesWritten;
}
 
DWORD CRS232::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	
	DWORD dwBytesTransferred,dwErrorFlags;
	COMSTAT	comstat;
	dwBytesTransferred=0;

	if(!ReadFile (m_hComm,          // ��Ʈ �ڵ� 
			  pBuff,                // ���� ����Ÿ�� �ִ� ���� 
			  nToRead,              // ���� ����Ʈ �� 
              &dwBytesTransferred,  // ���� �� 
			  NULL                  // Must be NULL for Windows CE
			  ))
	{
		// ���忡�� ó���� ���� ����Ʈ���� �Ǵ��Ѵ�. 	
	}
	else
	{
		//���� ���� 
		ClearCommError( m_hComm, &dwErrorFlags, &comstat );
	}

	return dwBytesTransferred;
}

// ��Ʈ�� �ݴ´�.
void CRS232::ClosePort()
{
	m_bConnected = FALSE;
	SetCommMask( m_hComm, 0);
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	CloseHandle(m_hComm);
}