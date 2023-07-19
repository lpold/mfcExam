
// Project_01Dlg.h: 헤더 파일
//
#pragma once
#include "CDlgImage.h"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

// CProject01Dlg 대화 상자
class CProject01Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProject01Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;
	int m_nCenterX;
	int m_nCenterY;
	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_01_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	CEdit m_editRadius;
	afx_msg void OnBnClickedButtonDraw();

	void init_child_dialog();
	void draw_cross(unsigned char* fm);	
	
};
