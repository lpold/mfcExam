#pragma once
#include "afxdialogex.h"

#include <vector>

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CWnd* m_pMain;
	CImage m_Image;
	unsigned char* m_fm;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IAMGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	void init_image();
	afx_msg void OnPaint();
	void draw_circle(CDC* pDC, unsigned char* fm, int centerX, int centerY, int radius);
};
