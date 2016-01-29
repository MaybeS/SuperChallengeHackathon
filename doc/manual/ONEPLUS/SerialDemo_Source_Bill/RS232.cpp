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

//포트 오픈 하고 쓰레드 시작 
BOOL CRS232::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID)
{
	

  cdmaBuffer = _T("");
  DCB PortDCB;
  COMMTIMEOUTS CommTimeouts;  

  // 포트 오픈 하기 
  m_hComm = CreateFile (sPortName, 
	                    GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
                        OPEN_EXISTING,
                        0,
                        NULL);

   
  // 오픈 실패하면 false 리턴 
  if ( m_hComm == INVALID_HANDLE_VALUE ) 
  {
	  return FALSE;
  }
  
  PortDCB.DCBlength = sizeof (DCB);     

  // 디폴트 포트 세팅 값 가져오기 
  GetCommState (m_hComm, &PortDCB);

  // PortDCB 세팅 값 변경 
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

  // 변경된 PortDCB 값 적용 
  if (!SetCommState (m_hComm, &PortDCB))
  {
   // AfxMessageBox(_T("시리얼 포트를 설정할수 없습니다."));
    return FALSE;
  }

  // 포트의 read write 타임아웃 시간 값을 가져옴 
  GetCommTimeouts (m_hComm, &CommTimeouts);

  // 타입아웃 스트럭쳐 값을 다시 세팅 함 
  CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
  CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
  CommTimeouts.ReadTotalTimeoutConstant = 0;    
  CommTimeouts.WriteTotalTimeoutMultiplier = 10;  
  CommTimeouts.WriteTotalTimeoutConstant = 1000;    

  // 타임아웃 값을 적용하기 
  if (!SetCommTimeouts (m_hComm, &CommTimeouts))
  {
    // AfxMessageBox(_T("시리얼 포트의 타임아웃 값을 설정할수 없습니다.")); 
    return FALSE;
  }

  
  EscapeCommFunction (m_hComm, SETDTR);
  EscapeCommFunction (m_hComm, SETRTS);

  m_bConnected = TRUE;

// 포트 감시 쓰레드 생성.
//	if(!RunThread()){
//		return FALSE;
//	}
	return TRUE;
}

// 포트에 pBuff의 내용을 nToWrite만큼 쓴다.
// 실제로 쓰여진 Byte수를 리턴한다.
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
		// write 에러 처리는 write한 바이트수로 판단한다. 	
	}
	else
	{
		//write 성공 
		ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	}

	return dwNumBytesWritten;
}
 
DWORD CRS232::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	
	DWORD dwBytesTransferred,dwErrorFlags;
	COMSTAT	comstat;
	dwBytesTransferred=0;

	if(!ReadFile (m_hComm,          // 포트 핸들 
			  pBuff,                // 읽은 데이타를 넣는 버퍼 
			  nToRead,              // 읽을 바이트 수 
              &dwBytesTransferred,  // 읽은 수 
			  NULL                  // Must be NULL for Windows CE
			  ))
	{
		// 리드에러 처리는 읽은 바이트수로 판단한다. 	
	}
	else
	{
		//리드 성공 
		ClearCommError( m_hComm, &dwErrorFlags, &comstat );
	}

	return dwBytesTransferred;
}

// 포트를 닫는다.
void CRS232::ClosePort()
{
	m_bConnected = FALSE;
	SetCommMask( m_hComm, 0);
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	CloseHandle(m_hComm);
}