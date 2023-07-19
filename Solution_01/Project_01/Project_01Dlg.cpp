
// Project_01Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project_01.h"
#include "Project_01Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <iostream>

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CProject01Dlg 대화 상자



CProject01Dlg::CProject01Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_01_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pDlgImage = NULL;
}

void CProject01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RADIUS, m_editRadius);
}

BEGIN_MESSAGE_MAP(CProject01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CProject01Dlg::OnBnClickedButtonDraw)
END_MESSAGE_MAP()


// CProject01Dlg 메시지 처리기

BOOL CProject01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	theApp.m_pDlgMain = this;

	MoveWindow(0, 0, 1280, 720);

	init_child_dialog();

	m_editRadius.SetWindowText(_T("0"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProject01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProject01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProject01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProject01Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (m_pDlgImage)
		delete m_pDlgImage;
}


void CProject01Dlg::OnBnClickedButtonDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_pDlgImage->m_fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	int nRadius = 0;
	CString strRadius;

	m_editRadius.GetWindowText(strRadius);
	nRadius = atoi((LPSTR)(LPCTSTR)strRadius);

	draw_cross(m_pDlgImage->m_fm);

	m_pDlgImage->Invalidate();
}

void CProject01Dlg::init_child_dialog()
{
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_DIALOG_IAMGE, this);
	m_pDlgImage->MoveWindow(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
	m_pDlgImage->ShowWindow(SW_SHOW);
}

void CProject01Dlg::draw_cross(unsigned char* fm)
{
	int nCount = 0;
	int nCenterX = rand() % IMAGE_WIDTH;
	int nCenterY = rand() % IMAGE_HEIGHT;
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	for (int i = -4; i < 5; i++)
	{
		if(i + nCenterX > 0 && i + nCenterX < IMAGE_WIDTH)
			fm[nCenterY * nPitch + nCenterX + i] = 0xfe;
	}
	for (int i = -4; i < 5; i++)
	{
		if (i + nCenterY > 0 && i + nCenterY < IMAGE_HEIGHT)
			fm[(nCenterY + i) * nPitch + nCenterX] = 0xfe;
	}

	fm[nCenterY * nPitch + nCenterX] = 0xff;

	CClientDC dc(m_pDlgImage);
	m_pDlgImage->m_Image.Draw(dc, 0, 0);

	m_nCenterX = nCenterX;
	m_nCenterY = nCenterY;

	int nSumX = 0, nSumY = 0;
	int center_of_gravity_x = 0;
	int center_of_gravity_y = 0;
	for (int j = 0; j < IMAGE_HEIGHT; j++)
	{
		for (int i = 0; i < IMAGE_WIDTH; i++)
		{
			if (fm[j * nPitch + i] == 0xff)
			{
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	center_of_gravity_x = nSumX / nCount;
	center_of_gravity_y = nSumY / nCount;


	std::cout << "Center of gravity - " << "(" << center_of_gravity_x << " : " << center_of_gravity_y << ")" << std::endl;
}


void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

}
