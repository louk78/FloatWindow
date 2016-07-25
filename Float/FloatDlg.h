
// FloatDlg.h : header file
//

#pragma once
#include "FloatCtrl.h"
#include <string>
#ifdef _UNICODE
#define  tstring wstring
#else
#define tstring string
#endif

using namespace std;

// CFloatDlg dialog
class CFloatDlg : public CDialogEx
{
// Construction
private:
	typedef struct _ICON_INFO_
	{
		Image *pImage;
		CRect  iconRect_W;
		UINT  iIconWidth;
		UINT  iIconHeight;
		BOOL  bShow;
	}ICONINFO,PICONINFO;

public:
	CFloatDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FLOAT_DIALOG };

	enum ICONREG{ICONREG_NONE,ICONREG_HEAD,ICONREG_ONE,ICONREG_TWO,ICONREG_THREE,ICONREG_FOUR};

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnMove(int x, int y);

	void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	BOOL ImageFromResource(UINT resourceID,LPCTSTR imgType,Image *&pImg);
	BOOL UpdateDisplay(int transparent=100);
	void LayoutWindow();
	BOOL GraphDrawImage(Image *image, int imageWidth, int imageHeight,CRect iconRect_W);
	void CheckReg(POINT point,ICONREG *iconreg);
	BOOL CreateCompatibleMemDC(HWND hwnd,int width,int height,HDC &hMemDC);
	BOOL GraphDrawText(RectF rectf,tstring strText);
	BOOL DrawIconBottomText(CRect iconRect_W,tstring strText);
	BOOL ShowChildIcon();
	BOOL OnlyShowMainIcon();
	void ShowTimeBeforeRightHide(int iShowTime);
	BOOL GetWindowStatus();
	void SetWindowStatus();
	static DWORD WINAPI ShowTimeThread(LPVOID lpRaram);

public:
	HDC m_MemDC;
	BLENDFUNCTION m_Blend;
	BOOL  m_bWndHide;
	BOOL m_bShowCildIcon;
	BOOL m_bCursorLeaveHeadReg;
	BOOL m_bShowTimeOver;
	BOOL m_bMovePlaying;
	SIZE m_MemDCSize;
	HANDLE m_hShowTimeEvent;
	ICONINFO m_HeadIcon;
	ICONINFO m_SitIcon;
	ICONINFO m_OneIcon;
	ICONINFO m_TwoIcon;
	ICONINFO m_ThreeIcon;
	ICONINFO m_FourIcon;
	int m_iShowTime;
	
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};
