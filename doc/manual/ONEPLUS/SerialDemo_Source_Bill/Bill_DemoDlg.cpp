// Bill_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bill_Demo.h"
#include "Bill_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RESET_WAIT				0
#define WAIT					1
#define STARTWAIT				2
#define RECOGNITION_RETURN		3
#define RECOGNITION_WAIT		4
#define RECOGNITION_END			5
#define RETURN_START			6
#define RETURN_WAIT				7
#define RETURN_END				8
#define STACK_START				9
#define STACK_WAIT				10
#define STACK_END				11
#define ERROR_WAIT				12
#define INSERT_ENABLE			13
#define INSERT_DISABLE			14
#define COM_WAIT				15
#define STACK_OPENED			16
#define ForceStack_WAIT			17
#define ForceStack_END			18

//	"지폐식별기가  상태입니다.",
//	"지폐식별기가 입수금지 상태입니다.",
//	"지페식별기가 입수가능 상태입니다.",
//	"지페식별기가 입수가능 상태입니다.",

CString MSG_TABLE[20]={
	"Reset동작",		//0
	"입수금지",			//1
	"입수가능",			//2
	"인식중 반환",		//3
	"인식중",			//4
	"인식완료",			//5
	"반환시작",			//6
	"반환중",			//7
	"반환완료",			//8
	"저장시작중",		//9
	"저장중",			//10
	"저장완료",			//11
	"오류발생",			//12
	"STACK Open",		//13
	" ",				//14
	" ",				//15
	" ",				//16
	"강제입수동작중",	//17
	"강제입수완료",		//18
};

CString MSGError_TABLE[20]={
	"Error없음",				//0
	"Start Sensor Error",		//1
	"Shutter Sensor Error",		//2
	"End Sensor Error",			//3
	"이송 Motor Error",			//4
	"Stack 관련 Error",			//5
	" ",						//6~10
	" ",						//7
	" ",						//8
	" ",						//9
	" ",						//10
	"인식센서1 Error",			//11
	"인식센서2 Error",			//12
	"인식센서3 Error",			//13
	"인식센서4 Error",			//14
	"인식센서5 Error",			//15
	"인식센서6 Error",			//16
	"인식센서7 Error",			//17
	"인식센서8 Error",			//18
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBill_DemoDlg dialog

CBill_DemoDlg::CBill_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBill_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBill_DemoDlg)
	m_Ver = _T("");
	m_RX = _T("");
	m_TX = _T("");
	m_StatusMSG = _T("");
	m_BillCount1 = _T("");
	m_BillCount10 = _T("");
	m_BillCount5 = _T("");
	m_BillCount50 = _T("");
	//m_AutoMode = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBill_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBill_DemoDlg)
	DDX_Control(pDX, IDC_BUTTON6, m_auto);
	DDX_Control(pDX, IDC_INHIBIT, m_Inhibit);
	DDX_Control(pDX, IDC_COMBO1, m_Port);
	DDX_Control(pDX, IDC_WON5000, m_PIC5Won);
	DDX_Control(pDX, IDC_WON10000, m_PIC10Won);
	DDX_Control(pDX, IDC_WON1000, m_PIC1Won);
	DDX_Control(pDX, IDC_USEEVENT, m_UseEvent);
	DDX_Control(pDX, IDC_USE5WON, m_Use5Won);
	DDX_Control(pDX, IDC_USE50WON, m_Use50Won);
	DDX_Control(pDX, IDC_USE1WON, m_Use1Won);
	DDX_Control(pDX, IDC_USE10WON, m_Use10Won);
	DDX_Control(pDX, IDC_AUTOSTACK, m_AutoStack);
	DDX_Text(pDX, IDC_VERSION, m_Ver);
	DDX_Text(pDX, IDC_RX, m_RX);
	DDX_Text(pDX, IDC_TX, m_TX);
	DDX_Text(pDX, IDC_STATUSMSG, m_StatusMSG);
	DDX_Text(pDX, IDC_BCNT1, m_BillCount1);
	DDX_Text(pDX, IDC_BCNT10, m_BillCount10);
	DDX_Text(pDX, IDC_BCNT5, m_BillCount5);
	DDX_Text(pDX, IDC_BCNT50, m_BillCount50);
	//DDX_Text(pDX, IDC_EDIT1, m_AutoMode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBill_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CBill_DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, OnRDStatus)
	ON_BN_CLICKED(IDC_BUTTON8, OnRDConfig)
	ON_BN_CLICKED(IDC_BUTTON7, OnSetConfig)
	ON_BN_CLICKED(IDC_BUTTON11, OnCon)
	ON_BN_CLICKED(IDC_BUTTON9, OnRDVersion)
	ON_BN_CLICKED(IDC_BUTTON3, OnInsertAmount)
	ON_BN_CLICKED(IDC_BUTTON5, OnInhibit)
	ON_BN_CLICKED(IDC_BUTTON1, OnStack)
	ON_BN_CLICKED(IDC_BUTTON2, OnReturn)
	ON_BN_CLICKED(IDC_9600BPS, On9600bps)
	ON_BN_CLICKED(IDC_4800BPS, On4800bps)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHGPORT, OnChgport)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON6, OnAuto)
	ON_BN_CLICKED(IDC_BUTTON12, OnReadErr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBill_DemoDlg message handlers

BOOL CBill_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Port.SetCurSel(0);
	CButton *pOption1 = (CButton*)GetDlgItem(IDC_9600BPS);
	CButton *pOption2 = (CButton*)GetDlgItem(IDC_4800BPS);
	pOption1->SetCheck(1);
	pOption2->SetCheck(0);

	PortNumber = "COM1";
	if(!Serial.OpenPort(PortNumber, 9600, 0 ) ){		//0
		AfxMessageBox("H/W Serial Port Not Found ", MB_OK | MB_APPLMODAL | MB_ICONSTOP, 0);
	}
	else SetTimer(0, 50, NULL);

	DisplayBill(0);

	m_BillCount1 = "";		//변수 초기화
	m_BillCount10 = "";
	m_BillCount5 = "";
	m_BillCount50 = "";
	BillCount1 = 0;
	BillCount10 = 0;
	BillCount5 = 0;
	BillCount50 = 0;
	bAuto = 0;
	AutoMode = 0;
	SetTimer(5, 100, NULL);
	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBill_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBill_DemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBill_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}






////////////////////
// Button Service //
////////////////////
void CBill_DemoDlg::On9600bps() 
{
	CButton *pOption1 = (CButton*)GetDlgItem(IDC_9600BPS);
	CButton *pOption2 = (CButton*)GetDlgItem(IDC_4800BPS);
	pOption1->SetCheck(1);
	pOption2->SetCheck(0);
}

void CBill_DemoDlg::On4800bps() 
{
	CButton *pOption1 = (CButton*)GetDlgItem(IDC_9600BPS);
	CButton *pOption2 = (CButton*)GetDlgItem(IDC_4800BPS);
	pOption1->SetCheck(0);
	pOption2->SetCheck(1);
}

void CBill_DemoDlg::OnChgport() 
{
	UpdateData(TRUE);

	Serial.ClosePort();
	KillTimer(0);
	KillTimer(1);

	CButton *pOption1 = (CButton*)GetDlgItem(IDC_9600BPS);
	if(pOption1->GetCheck() == 1){
		if(!Serial.OpenPort(PortNumber, 9600, 0 ) ){		//0
			AfxMessageBox("H/W Serial Port Not Found ", MB_OK | MB_APPLMODAL | MB_ICONSTOP, 0);
		}
		else SetTimer(0, 50, NULL);
	}
	else{
		if(!Serial.OpenPort(PortNumber, 4800, 0 ) ){		//0
			AfxMessageBox("H/W Serial Port Not Found ", MB_OK | MB_APPLMODAL | MB_ICONSTOP, 0);
		}
		else SetTimer(0, 50, NULL);
	}
}

void CBill_DemoDlg::OnSelchangeCombo1() 
{
	m_Port.GetLBText( m_Port.GetCurSel(), PortNumber );	
}

void CBill_DemoDlg::OnCon() 
{
	SendPacket('H', 'i', '?');
}

void CBill_DemoDlg::OnRDVersion() 
{
	SendPacket('G', 'V', '?');
}

void CBill_DemoDlg::OnRDStatus() 
{
	SendPacket('G', 'A', '?');
}

void CBill_DemoDlg::OnRDConfig() 
{
	SendPacket('G', 'C', '?');
}

void CBill_DemoDlg::OnReturn() 
{
	SendPacket('S', 'A', 6);
}

void CBill_DemoDlg::OnInsertAmount() 
{
	SendPacket('G', 'B', '?');
}

void CBill_DemoDlg::OnReadErr() 
{
	SendPacket('G', 'E', '?');
}

void CBill_DemoDlg::OnStack() 
{
	SendPacket('S', 'A', 9);
}

void CBill_DemoDlg::OnSetConfig() 
{
	unsigned char data;

	UpdateData(TRUE);
	data = 0;
	if(m_Use1Won.GetCheck() == 1) data |= 0x01;
	if(m_Use5Won.GetCheck() == 1) data |= 0x02;
	if(m_Use10Won.GetCheck() == 1) data |= 0x04;
	if(m_Use50Won.GetCheck() == 1) data |= 0x08;
	if(m_AutoStack.GetCheck() == 1) data |= 0x10;
	if(m_UseEvent.GetCheck() == 1) data |= 0x20;

	SendPacket('S', 'C', data);
}

void CBill_DemoDlg::OnInhibit() 
{
	CString str;

	m_Inhibit.GetWindowText(str);
	if( str == "입수금지" ){
		SendPacket('S', 'A', 14);
		m_Inhibit.SetWindowText("입수가능");
	}
	else{
		SendPacket('S', 'A', 13);
		m_Inhibit.SetWindowText("입수금지");
	}
}

void CBill_DemoDlg::OnAuto() 
{
	// TODO: Add your control notification handler code here
	if( !bAuto ){
		bAuto = 1;

		m_auto.SetWindowText("Manual");
		m_BillCount1 = "";
		m_BillCount10 = "";
		m_BillCount5 = "";
		m_BillCount50 = "";
		BillCount1 = 0;
		BillCount10 = 0;
		BillCount5 = 0;
		BillCount50 = 0;
		UpdateData(false);

		SendPacket('G', 'C', '?');
	}
	else{
		bAuto = 0;
		AutoMode = 0;
		m_auto.SetWindowText("Auto");
	}
}








///////////////////
// Timer Service //
///////////////////
void CBill_DemoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//CString str;

	switch(nIDEvent){
	case 0:
		RecevDataSerial();
		break;
	case 5:
		NoEventTXService();
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

unsigned char CBill_DemoDlg::RecevDataSerial()
{
    unsigned char Buffer[1];
	unsigned char tmp, tmp1;
	CString str;

	while(Serial.ReadComm(Buffer, 1))
	{
		Serial_RBuffer[0] = Serial_RBuffer[1];
		Serial_RBuffer[1] = Serial_RBuffer[2];
		Serial_RBuffer[2] = Serial_RBuffer[3];
		Serial_RBuffer[3] = Serial_RBuffer[4];
		Serial_RBuffer[4] = Buffer[0];

		if( (Serial_RBuffer[0] == '$') && (Serial_RBuffer[4] == ((unsigned char)(Serial_RBuffer[1]+Serial_RBuffer[2]+Serial_RBuffer[3]))) ){
			str.Format("  0x%x,0x%x,0x%x,0x%x,0x%x ( %c %c %c %c %c )",
				Serial_RBuffer[0], Serial_RBuffer[1], Serial_RBuffer[2], Serial_RBuffer[3], Serial_RBuffer[4], 
				Serial_RBuffer[0], Serial_RBuffer[1], Serial_RBuffer[2], Serial_RBuffer[3], Serial_RBuffer[4]);
			m_RX = str;

			CheckRXData = 1;
			if( (Serial_RBuffer[1] == 'm') && (Serial_RBuffer[2] == 'e') ){
				str.Format(" 지폐식별기와   \r\n   정상적으로 통신을  \r\n    수행하였습니다.");
				m_StatusMSG = str;
			}

			if( Serial_RBuffer[1] == 'v' ){
				str.Format("Ver %d.%d", Serial_RBuffer[2], Serial_RBuffer[3]);
				m_Ver = str;
			}

			if( (Serial_RBuffer[1] == 'g') && (Serial_RBuffer[2] == 'b') ){
				DisplayBill(Serial_RBuffer[3]);

				if( (AutoMode == 0x16) && bAuto ){
					SendPacket('S', 'A', 13);
					AutoMode = 0x10;
				}
				DisplayActive(1, Serial_RBuffer[3]);
			}
			
			if( (Serial_RBuffer[1] == 'g') && (Serial_RBuffer[2] == 'c') ){
				tmp = Serial_RBuffer[3];
				if( (tmp & 0x01) == 0x01) m_Use1Won.SetCheck(1);
				else m_Use1Won.SetCheck(0);
				if( (tmp & 0x02) == 0x02) m_Use5Won.SetCheck(1);
				else m_Use5Won.SetCheck(0);
				if( (tmp & 0x04) == 0x04) m_Use10Won.SetCheck(1);
				else m_Use10Won.SetCheck(0);
				if( (tmp & 0x08) == 0x08) m_Use50Won.SetCheck(1);
				else m_Use50Won.SetCheck(0);
				if( (tmp & 0x10) == 0x10){
					AutoStack = 1;
					m_AutoStack.SetCheck(1);
				}
				else{
					AutoStack = 0;
					m_AutoStack.SetCheck(0);
				}
				if( (tmp & 0x20) == 0x20){
					tmp1 = 1;
					m_UseEvent.SetCheck(1);
				}
				else{
					tmp1 = 0;
					m_UseEvent.SetCheck(0);
				}
				if( bAuto ){
					SendPacket('S', 'A', 13);
					if( tmp1 == 0 ) AutoMode = 0x10;
					else AutoMode = 0;
				}
			}

			if( (Serial_RBuffer[1] == 'g') && (Serial_RBuffer[2] == 'a') ){
				DisplayActive(0, Serial_RBuffer[3]);
				if( Serial_RBuffer[3] == STARTWAIT ) m_Inhibit.SetWindowText("입수금지");
				else m_Inhibit.SetWindowText("입수가능");
				if( AutoMode != 0 ){
					if( AutoMode == 0x12 ){
						if( (Serial_RBuffer[3] == RESET_WAIT) && (Serial_RBuffer[3] == WAIT) ){
							SendPacket('S', 'A', 13);
							AutoMode = 0x11;
						}
						else{
							if( Serial_RBuffer[3] == RECOGNITION_END ){
								if( AutoStack != 1 ){
									SendPacket('S', 'A', 0x09);
									AutoMode = 0x14;
								}
							}
							else AutoMode = 0x11;
						}
					}
					else{
						if( AutoMode == 0x14 ){	
							if( Serial_RBuffer[3] == RECOGNITION_END ){
								if( AutoStack != 1 ) SendPacket('S', 'A', 0x09);
							}
						}
						else{
							if( AutoMode == 0x16 ){
								if( Serial_RBuffer[3] == STACK_END ){		//11
								}
								else AutoMode = 0x15;
							}
						}
					}
				}
				else{
					DisplayActive(0, Serial_RBuffer[3]);
					if( Serial_RBuffer[3] == STARTWAIT ) m_Inhibit.SetWindowText("입수금지");
					else m_Inhibit.SetWindowText("입수가능");
				}
			}

			if( (Serial_RBuffer[1] == 'g') && (Serial_RBuffer[2] == 'e') ){
				UpdateData(TRUE);
				ErrorStatus = Serial_RBuffer[3];
				str.Format("\r\n :  %s ", MSGError_TABLE[Serial_RBuffer[3]]);
				m_StatusMSG = m_StatusMSG + str;
			}


			if( (Serial_RBuffer[1] == 'E') && (Serial_RBuffer[2] == 'S') ){
				SendPacket('e', 's', Serial_RBuffer[3]);	
				ActStatus = Serial_RBuffer[3];
				DisplayActive(0, Serial_RBuffer[3]);
				if( (Serial_RBuffer[3] == STARTWAIT) || (Serial_RBuffer[3] == ForceStack_END) ) m_Inhibit.SetWindowText("입수금지");
				else m_Inhibit.SetWindowText("입수가능");
			}

			if( (Serial_RBuffer[1] == 'O') && (Serial_RBuffer[2] == 'K') ){
				if( Serial_RBuffer[3] == 'c' )
					str.Format(" 지폐식별기의  \r\n   Config Reg. 변경을 \r\n    성공하였습니다.");
				else{
					str.Format(" 지폐식별기가  \r\n   명령 수행을  \r\n    성공하였습니다.");
				}
				m_StatusMSG = str;
				if( bAuto ){
					if( AutoMode == 0x10 ){
						m_Inhibit.SetWindowText("입수금지");
						AutoMode = 0x11;
					}
					else{
						if( AutoMode == 0x14 ) AutoMode = 0x15;
					}
				}
			}

			if( (Serial_RBuffer[1] == 'N') && (Serial_RBuffer[2] == 'G') ){
				if( Serial_RBuffer[3] == 'c' ){
					str.Format(" 지폐식별기의  \r\n   Config Reg. 변경을 \r\n    실패하였습니다.");
					SendPacket('G', 'C', '?');
				}
				else{
					str.Format(" 지폐식별기가  \r\n   명령 수행을  \r\n    거절하였습니다.");
					SendPacket('G', 'A', '?');
				}
				m_StatusMSG = str;
			}

			UpdateData(FALSE);
			return 1;
		}
	}
	return 0;
}

void CBill_DemoDlg::NoEventTXService()
{
	switch(AutoMode){
	case 0x10:
		if( ++SendInterval > 5 ){
			SendPacket('S', 'A', 13);
		}		
		break;
	case 0x11:
		if( ++SendInterval > 2 ){
			SendPacket('G', 'A', '?');
			AutoMode = 0x12;
		}
		break;
	case 0x12:
		if( ++SendInterval > 12 ){		//1sec
			if( CheckRXData != 0 ){		//RX 확인 후 ..
				AutoMode = 0x11;
			}
			else{
				if( SendInterval > 20 ){	// 일정 시간 동안 RX가 없을 경우...
					AutoMode = 0x11;
				}
			}
		}
		break;
	case 0x13:
	case 0x14:
		break;
	case 0x15:
		if( ++SendInterval > 2 ){
			SendPacket('G', 'A', '?');
			AutoMode = 0x16;
		}
		break;
	case 0x16:
		break;
	}
}








/////////////////////
// Display Service //
/////////////////////
void CBill_DemoDlg::DisplayBill(unsigned char BillKind)
{
	m_PIC1Won.ShowWindow(false);
	m_PIC5Won.ShowWindow(false);
	m_PIC10Won.ShowWindow(false);
	switch(BillKind){
	case 1:
		m_PIC1Won.ShowWindow(true);
		break;
	case 5:
		m_PIC5Won.ShowWindow(true);
		break;
	case 10:
		m_PIC10Won.ShowWindow(true);
		break;
	}
}


void CBill_DemoDlg::DisplayActive(unsigned char data1, unsigned char data2)
{
	CString str, str1;

	if( data1 == 0 ){		// 지폐식별기의 동작상태
		if( data2 == 0x10 ) str.Format("지폐식별기 \r\n  Stack이 \r\n  Open되었습니다.");
		else str.Format(" 지폐식별기가 \r\n       %s \r\n\t 상태입니다.", MSG_TABLE[data2]);
		m_StatusMSG = str;
		if( bAuto ){
			if(data2 == 11){
				SendPacket('G', 'B', '?');
				ErrorStatus = 0;
			}
			else{
				if( (data2 == 1) || (data2 == 18) ){
					SendPacket('S', 'A', 13);
					ErrorStatus = 0;
				}
				else{
					if(data2 == 12){
						if( ErrorStatus == 0) SendPacket('G', 'B', '?');
						SendPacket('G', 'E', '?');
					}
				}
			}
		}
	}
	else{					// 입수된 지폐종류
		switch(data2){
			case 1:
				str1 = "1,000";
				if( bAuto ) BillCount1++;
				break;
			case 5:
				str1 = "5,000";
				if( bAuto ) BillCount5++;
				break;
			case 10:
				str1 = "10,000";
				if( bAuto ) BillCount10++;
				break;
			case 50:
				str1 = "50,000";
				if( bAuto ) BillCount50++;
				break;
			default:
				str1 = "0";
				break;
		}

		str.Format(" 입수된 지폐는 \r\n      %s원권 입니다.", str1);
		m_StatusMSG = str;

		if( bAuto ){
			str.Format("%d", BillCount1);
			m_BillCount1 = str;
			str.Format("%d", BillCount10);
			m_BillCount10 = str;
			str.Format("%d", BillCount5);
			m_BillCount5 = str;
			str.Format("%d", BillCount50);
			m_BillCount50 = str;
			SendPacket('S', 'A', 13);
		}
	}
	UpdateData(FALSE);
}





/////////////////
// 통신 Packet //
/////////////////
void CBill_DemoDlg::SendPacket(unsigned char data1, unsigned char data2, unsigned char data3)
{
	unsigned char command[10];
	CString str, str1, str2;

	command[0] = '$';			// tx
	command[1] = data1;
	command[2] = data2;
	command[3] = data3;
	command[4] =  (unsigned char)(data1+data2+data3);
	Serial.WriteComm(command,5);

	str.Format("  0x%x,0x%x,0x%x,0x%x,0x%x ( %c %c %c %c %c )",
		command[0], command[1], command[2], command[3], command[4], command[0], command[1], command[2], command[3], command[4]);
	m_TX = str;

	SendInterval = 0;
	CheckRXData = 0;
	UpdateData(FALSE);
}



