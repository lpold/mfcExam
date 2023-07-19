// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "Project_01.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include "Project_01Dlg.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IAMGE, pParent)
{
	m_pMain = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

	init_image();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pMain)
		delete m_pMain;
}

void CDlgImage::init_image()
{
	if (!m_Image)
	{
		int nBpp = 8;
		m_Image.Create(IMAGE_WIDTH, -IMAGE_HEIGHT, nBpp);
		if (nBpp == 8)
		{
			static RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
			{
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			}
			m_Image.SetColorTable(0, 256, rgb);
		}
	}
	m_fm = (unsigned char*)m_Image.GetBits();
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	memset(m_fm, 0x00, nWidth * nHeight);

	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
	
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.


	if (m_Image)
		m_Image.Draw(dc, 0, 0);

	CString strRadius;
	theApp.m_pDlgMain->m_editRadius.GetWindowText(strRadius);
	int nRadius = _ttoi((LPCTSTR)strRadius);
	draw_circle(&dc, m_fm, theApp.m_pDlgMain->m_nCenterX, theApp.m_pDlgMain->m_nCenterY, nRadius);
	
}

void CDlgImage::draw_circle(CDC* pDC, unsigned char* fm, int centerX, int centerY, int radius)
{
	int nPitch = m_Image.GetPitch();

	static std::vector<int> vec_ncenterX;
	static std::vector<int> vec_ncenterY;
	static std::vector<int> vec_nRadius;

	vec_ncenterX.push_back(centerX);
	vec_ncenterY.push_back(centerY);
	vec_nRadius.push_back(radius);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	for (int i = 0; i < vec_nRadius.size(); i++)
	{
		CRect rect(vec_ncenterX[i] - vec_nRadius[i], vec_ncenterY[i] - vec_nRadius[i], vec_ncenterX[i] + vec_nRadius[i], vec_ncenterY[i] + vec_nRadius[i]);
		pDC->SelectObject(GetStockObject(NULL_BRUSH));
		pDC->Ellipse(rect);
	}

	pDC->SelectObject(pOldPen);
}