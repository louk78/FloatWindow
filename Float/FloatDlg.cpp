
// FloatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Float.h"
#include "FloatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define TIMER_CHECK_CURSOR_LEAVE_NC 101
#define SPACE_TEXT_ICONBOTTOM 5
#define SPACE_ICON_VERTICAL  5
#define SPACE_ICON_HORIZONTAL 15
#define WIDTH_MAINICON_SHOW_AFTER_HIDE 10
#define LENGTH_MOVEPLAY_SHOW_EACHMOVE 5
#define LENGTH_MOVEPLAY_HIDE_EACHMOVE 8
#define WIDTH_OUTSCREEN 1


// CFloatDlg dialog
CFloatDlg::CFloatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFloatDlg::IDD, pParent),m_bShowCildIcon(FALSE),
	m_bShowTimeOver(TRUE),m_bMovePlaying(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bWndHide = FALSE;
	m_bCursorLeaveHeadReg = TRUE;
	m_MemDC = NULL;
}

BEGIN_MESSAGE_MAP(CFloatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCMOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CFloatDlg message handlers
int CFloatDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	Image *pImage;
	m_Blend.BlendOp = 0;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat =1;
	m_Blend.SourceConstantAlpha = 255;

	if(ImageFromResource(IDB_HEAD,L"PNG",pImage))
	{
		m_HeadIcon.pImage = pImage;
		m_HeadIcon.iIconWidth = pImage->GetWidth();
		m_HeadIcon.iIconHeight = pImage->GetHeight();
	}
	if(ImageFromResource(IDB_SITOUT,L"PNG",pImage))
	{
		m_SitIcon.pImage = pImage;
		m_SitIcon.iIconWidth = pImage->GetWidth();
		m_SitIcon.iIconHeight = pImage->GetHeight();
	}
	if(ImageFromResource(IDB_MAIL,L"PNG",pImage))
	{
		m_OneIcon.pImage = pImage;
		m_OneIcon.iIconWidth = pImage->GetWidth();
		m_OneIcon.iIconHeight = pImage->GetHeight();
	}
	if(ImageFromResource(IDB_CHART,L"PNG",pImage))
	{
		m_TwoIcon.pImage = pImage;
		m_TwoIcon.iIconWidth = pImage->GetWidth();
		m_TwoIcon.iIconHeight = pImage->GetHeight();
	}
	if(ImageFromResource(IDB_LAMP,L"PNG",pImage))
	{
		m_ThreeIcon.pImage = pImage;
		m_ThreeIcon.iIconWidth = pImage->GetWidth();
		m_ThreeIcon.iIconHeight = pImage->GetHeight();
	}
	if(ImageFromResource(IDB_CHAT,L"PNG",pImage))
	{
		m_FourIcon.pImage = pImage;
		m_FourIcon.iIconWidth = pImage->GetWidth();
		m_FourIcon.iIconHeight = pImage->GetHeight();
	}



	::SetWindowPos(m_hWnd,HWND_TOPMOST,10,10,0,0,SWP_NOSIZE);

	return 1;
}



BOOL CFloatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
	
	RECT rect;
	GetClientRect(&rect);
	m_MemDCSize.cx = rect.right;
	m_MemDCSize.cy = rect.bottom;
	LayoutWindow();

	DWORD dwExStyle = GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if((dwExStyle&0x80000)!=0x80000)
		dwExStyle = dwExStyle^0x80000;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle);
	



	SetTimer(TIMER_CHECK_CURSOR_LEAVE_NC,500,NULL);
	m_hShowTimeEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	OnlyShowMainIcon();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CFloatDlg::LayoutWindow()
{
	RECT clientRect;
	int iHeadLeft, iHeadTop;
	int iFistRowTop, iSecondRowTop;
	int iOneColumnLeft, iTwoColumnLeft, iThreeColumnLeft, iFourColumnLeft;
	int iSitTop,iSitLeft;
	int iWndWidth, iWndHeight;
	int iHeadIconWidth = m_HeadIcon.iIconWidth;
	int iHeadIconHeight = m_HeadIcon.iIconHeight;
	int iChildIconWidth = m_OneIcon.iIconWidth;
	int iChildIconHeith = m_OneIcon.iIconHeight;


	GetClientRect(&clientRect);
	iWndWidth = clientRect.right;
	iWndHeight = clientRect.bottom;


	//      #
	// #        #
	//    #  #
	iHeadLeft = (iWndWidth - iHeadIconWidth) / 2;
	iHeadTop = 10;
	//第一行高度
	iFistRowTop = iHeadTop + iHeadIconWidth / 2;
	//第二行高度
	iSecondRowTop = iFistRowTop + iChildIconHeith + SPACE_ICON_VERTICAL;

	iTwoColumnLeft = iWndWidth / 2 - iChildIconWidth-SPACE_ICON_HORIZONTAL;
	iThreeColumnLeft = iWndWidth / 2+SPACE_ICON_HORIZONTAL;
	iOneColumnLeft = iTwoColumnLeft - iChildIconWidth;
	iFourColumnLeft = iThreeColumnLeft + iChildIconWidth;

	iSitTop = iHeadTop +(iHeadIconHeight*3/4);
	iSitLeft = iHeadLeft + (iHeadIconHeight*3/4);


	m_HeadIcon.iconRect_W.SetRect(
		iHeadLeft,
		iHeadTop,
		iHeadLeft+iHeadIconWidth,
		iHeadTop+iHeadIconHeight
		);
	m_SitIcon.iconRect_W.SetRect(
		iSitLeft,
		iSitTop,
		iSitLeft+m_SitIcon.iIconWidth,
		iSitTop+m_SitIcon.iIconHeight
		);
	m_OneIcon.iconRect_W.SetRect(
		iOneColumnLeft,
		iFistRowTop,
		iOneColumnLeft+iChildIconWidth,
		iFistRowTop+iChildIconHeith
		);
	m_TwoIcon.iconRect_W.SetRect(
		iTwoColumnLeft,
		iSecondRowTop,
		iTwoColumnLeft+iChildIconWidth,
		iSecondRowTop+iChildIconHeith
		);
	m_ThreeIcon.iconRect_W.SetRect(
		iThreeColumnLeft,
		iSecondRowTop,
		iThreeColumnLeft+iChildIconWidth,
		iSecondRowTop+iChildIconHeith
		);
	m_FourIcon.iconRect_W.SetRect(
		iFourColumnLeft,
		iFistRowTop,
		iFourColumnLeft+iChildIconWidth,
		iFistRowTop+iChildIconHeith
		);

}


void CFloatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID,lParam);
}




// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFloatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CFloatDlg::ImageFromResource(UINT resourceID,LPCTSTR imgType,Image *&pImg)
{
	pImg = NULL;
	Status stat;
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(resourceID),imgType);
	if(hRsrc)
	{
		DWORD len = SizeofResource(hInst,hRsrc);
		BYTE* lpRsrc = (BYTE*)LoadResource(hInst,hRsrc);
		if(lpRsrc)
		{
			HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED,len);
			BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
			memcpy(pmem,lpRsrc,len);
			IStream* pstm;
			CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);

			pImg = Gdiplus::Image::FromStream(pstm);

			GlobalUnlock(m_hMem);
			pstm->Release();
			FreeResource(lpRsrc);

			stat = pImg->GetLastStatus();
			if(stat!=Ok)
			{
				GlobalFree(m_hMem);
				if(pImg)
				{
					delete pImg;
					pImg = NULL;
				}
				return FALSE;
					
			}
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CFloatDlg::GraphDrawImage(Image *image, int imageWidth, int imageHeight,CRect iconRect_W)
{
	BOOL bRet = FALSE;
	if (m_MemDC == NULL || image == NULL)return FALSE;

	Graphics graph(m_MemDC);
	graph.SetSmoothingMode(SmoothingModeAntiAlias);
	bRet = graph.DrawImage(image, iconRect_W.left,iconRect_W.top,imageWidth,imageHeight);
	graph.ReleaseHDC(m_MemDC);

	return bRet;
}

BOOL CFloatDlg::UpdateDisplay(int transparent)
{
	BOOL bRet = FALSE;

	if(this->m_hWnd==NULL)return FALSE;
	RECT ScreenRect;
	GetWindowRect(&ScreenRect);
	POINT dstPoint={ScreenRect.left,ScreenRect.top},srcPoint={0,0};
;
	if (transparent<0 || transparent>100)transparent = 100;
	m_Blend.SourceConstantAlpha = (int)(transparent*2.55);
	bRet = ::UpdateLayeredWindow(
		m_hWnd,
		::GetDC(m_hWnd),
		&dstPoint,
		&m_MemDCSize,
		m_MemDC,
		&srcPoint,
		0,
		&m_Blend,
		ULW_ALPHA
		);
	return bRet;	
}

LRESULT CFloatDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	POINT point_W = point;
	LRESULT nHitTest = CDialogEx::OnNcHitTest(point);
	if(nHitTest == HTCLIENT)
	{
		ScreenToClient(&point_W);
		if(m_HeadIcon.iconRect_W.PtInRect(point_W))
		{
			nHitTest = HTCAPTION;	
		}
	}
	return nHitTest;
}



void CFloatDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call 
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	//隐藏窗口动画
	if(nIDEvent == TIMER_CHECK_CURSOR_LEAVE_NC&&m_bCursorLeaveHeadReg==FALSE)
	{
		ICONREG iconReg;
		POINT point;
		::GetCursorPos(&point);
		ScreenToClient(&point);
		CheckReg(point,&iconReg);
		if(iconReg==ICONREG_NONE&&!m_bWndHide)
		{
			m_bCursorLeaveHeadReg = TRUE;
			int iMoveLength,iFourIconRight_S,iHeadIconLeft_S;
			RECT MainWndRect_S;

			GetWindowRect(&MainWndRect_S);
			iFourIconRight_S = MainWndRect_S.left+m_FourIcon.iconRect_W.right;
			iHeadIconLeft_S = MainWndRect_S.left + m_HeadIcon.iconRect_W.left;
			if(iFourIconRight_S>iScreenWidth)
			{
				m_bMovePlaying = TRUE;
				OnlyShowMainIcon();
				iMoveLength = iScreenWidth-iHeadIconLeft_S-WIDTH_MAINICON_SHOW_AFTER_HIDE;
				int i;
				for(i =0;i<iMoveLength;i+=LENGTH_MOVEPLAY_HIDE_EACHMOVE)
				{
					Sleep(2);
					MoveWindow(
						MainWndRect_S.left+i,
						MainWndRect_S.top,
						MainWndRect_S.right-MainWndRect_S.left,
						MainWndRect_S.bottom-MainWndRect_S.top
						);
				}
				if(i-LENGTH_MOVEPLAY_HIDE_EACHMOVE<iMoveLength)
				{
					MoveWindow(
						MainWndRect_S.left+iMoveLength,
						MainWndRect_S.top,
						MainWndRect_S.right-MainWndRect_S.left,
						MainWndRect_S.bottom-MainWndRect_S.top
						);
				}
				m_bMovePlaying = FALSE;
				m_bWndHide = TRUE;
			}
		}
	}


}


void CFloatDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bShowTimeOver)
	{
		m_bCursorLeaveHeadReg = FALSE;
	}
	
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	RECT MainWndRect_S;
	int iMoveLength;
	int iFourIconRight_S,iHeadIconLeft_S;
	GetWindowRect(&MainWndRect_S);


	iFourIconRight_S = MainWndRect_S.left +m_FourIcon.iconRect_W.right;
	iHeadIconLeft_S = MainWndRect_S.left +m_HeadIcon.iconRect_W.left;

	//显示窗口动画
	if(iFourIconRight_S>=iScreenWidth&&m_bWndHide)
	{
		m_bMovePlaying = TRUE;
		iMoveLength = ((iFourIconRight_S-iHeadIconLeft_S)-WIDTH_MAINICON_SHOW_AFTER_HIDE)-WIDTH_OUTSCREEN;
		int i;
		for( i =0;i<iMoveLength;i+=LENGTH_MOVEPLAY_SHOW_EACHMOVE)
		{
			MoveWindow(
				MainWndRect_S.left-i,MainWndRect_S.top,
				MainWndRect_S.right-MainWndRect_S.left,
				MainWndRect_S.bottom-MainWndRect_S.top
				);
			Sleep(2);
		}
		if(i-LENGTH_MOVEPLAY_SHOW_EACHMOVE<iMoveLength)
		{
			MoveWindow(
				MainWndRect_S.left-iMoveLength,
				MainWndRect_S.top,
				MainWndRect_S.right-MainWndRect_S.left,
				MainWndRect_S.bottom-MainWndRect_S.top
				);
		}
		ShowChildIcon();
		m_bMovePlaying = FALSE;
		m_bWndHide = FALSE;
		ShowTimeBeforeRightHide(1300);
	}
	
	CDialogEx::OnNcMouseMove(nHitTest, point);
}


DWORD WINAPI CFloatDlg::ShowTimeThread(LPVOID lpParam)
{
	CFloatDlg *This = (CFloatDlg *)lpParam;
	ResetEvent(This->m_hShowTimeEvent);
	WaitForSingleObject(This->m_hShowTimeEvent,This->m_iShowTime);
	This->m_bCursorLeaveHeadReg = FALSE;
	This->m_bShowTimeOver = TRUE;
	return 1;
}

void CFloatDlg::ShowTimeBeforeRightHide(int iShowTime)
{
	m_bCursorLeaveHeadReg = TRUE;
	m_bShowTimeOver = FALSE;
	m_iShowTime = iShowTime;
	HANDLE hThread = CreateThread(NULL,0,ShowTimeThread,(LPVOID)this,0,NULL);
	CloseHandle(hThread);
}

void CFloatDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
}

void CFloatDlg::CheckReg(POINT point,ICONREG *iconreg)
{
	*iconreg = ICONREG_NONE;

	
	if(m_HeadIcon.iconRect_W.PtInRect(point))
	{
		*iconreg = ICONREG_HEAD;
	}
	else if (m_OneIcon.iconRect_W.PtInRect(point))
	{
		*iconreg = ICONREG_ONE;

	}
	else if (m_TwoIcon.iconRect_W.PtInRect(point))
	{
		*iconreg = ICONREG_TWO;
	}
	else if (m_ThreeIcon.iconRect_W.PtInRect(point))
	{
		*iconreg = ICONREG_THREE;
	}
	else if (m_FourIcon.iconRect_W.PtInRect(point))
	{
		*iconreg = ICONREG_FOUR;
	}
}


BOOL CFloatDlg::CreateCompatibleMemDC(HWND hwnd,int width,int height,HDC &hMemDC)
{
	if(hwnd==NULL)return FALSE;
	HDC clientDC;
	HBITMAP hBitmap;

	clientDC = ::GetDC(hwnd);
	if(hMemDC!=NULL)
	{
		::ReleaseDC(hwnd,hMemDC);
		hMemDC = NULL;
	}
	hMemDC = ::CreateCompatibleDC(clientDC);
	hBitmap = ::CreateCompatibleBitmap(clientDC,width,height);
	::SelectObject(hMemDC,hBitmap);
	::DeleteObject(hBitmap);
	return TRUE;
}



void CFloatDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ICONREG iconreg;

	CheckReg(point,&iconreg);

	if (iconreg==ICONREG_ONE)
	{
		ShellExecute(NULL, _T("open"), _T("explorer.exe"), _T("http://mail.qq.com/"), NULL, SW_SHOW);
	}
	else if (iconreg == ICONREG_TWO)
	{
		ShellExecute(NULL, _T("open"), _T("explorer.exe"), _T("http://github.com"), NULL, SW_SHOW);
	}
	else if (iconreg == ICONREG_THREE)
	{
		ShellExecute(NULL, _T("open"), _T("notepad.exe"), NULL, NULL, SW_SHOW);
	}
	else if (iconreg == ICONREG_FOUR)
	{
		MessageBox(TEXT("Hey,I am Chat"), TEXT("Hello world"));
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CFloatDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bShowCildIcon)
	{
		ShowChildIcon();
	}

	CDialogEx::OnNcLButtonDown(nHitTest,point);
}


void CFloatDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bShowCildIcon)
	{
		OnlyShowMainIcon();
	}
}

BOOL CFloatDlg::GraphDrawText(RectF rectf,tstring strText)
{
	if(m_MemDC==NULL)return FALSE;
	int iRet;
	Graphics graph(m_MemDC);
	FontFamily *fontFamil;
	fontFamil =(FontFamily*) FontFamily::GenericSerif();
	Gdiplus::Font font(fontFamil,11,FontStyleRegular,UnitPoint);
	SolidBrush whiteBrush(Color(255,255,255,255));
	SolidBrush blackBrush(Color(255,0,0,0));
	Gdiplus::StringFormat format;
	GraphicsPath gpath;
	format.SetAlignment(StringAlignmentCenter);
	rectf.Height = font.GetHeight(&graph);


/*
	gpath.AddString(strText.c_str(),strText.size(),fontFamil,FontStyleRegular,14,
		rectf,&format);

	graph.FillPath(&blackBrush,&gpath);*/
	iRet = graph.DrawString(strText.c_str(),strText.size(),
		&font,rectf,&format,&whiteBrush);
	

	graph.ReleaseHDC(m_MemDC);

	return iRet;
}

BOOL CFloatDlg::DrawIconBottomText(CRect iconRect_W,tstring strText)
{
	int iTextRectWidth = 80;
	RectF rectf;
	rectf.X = (REAL)(iconRect_W.right-(iconRect_W.right-iconRect_W.left)/2)-iTextRectWidth/2;
	rectf.Y = (REAL)iconRect_W.bottom+ SPACE_TEXT_ICONBOTTOM;
	rectf.Width = (REAL)iTextRectWidth;
	return GraphDrawText(rectf,strText);
	
}


BOOL CFloatDlg::ShowChildIcon()
{
	int iChildIconWidth = 64;
	int iChildIconHeith = 64;

	GraphDrawImage(
		m_OneIcon.pImage, 
		m_OneIcon.iIconWidth,
		m_OneIcon.iIconHeight,
		m_OneIcon.iconRect_W
		);
	GraphDrawImage(
		m_TwoIcon.pImage, 
		m_TwoIcon.iIconWidth,
		m_TwoIcon.iIconHeight,
		m_TwoIcon.iconRect_W
		);
	GraphDrawImage(
		m_ThreeIcon.pImage, 
		m_ThreeIcon.iIconWidth,
		m_ThreeIcon.iIconHeight,
		m_ThreeIcon.iconRect_W
		);
	GraphDrawImage(
		m_FourIcon.pImage, 
		m_FourIcon.iIconWidth,
		m_FourIcon.iIconHeight,
		m_FourIcon.iconRect_W
		);


	DrawIconBottomText(m_OneIcon.iconRect_W,L"邮件协作");
	DrawIconBottomText(m_TwoIcon.iconRect_W,L"组织架构");
	DrawIconBottomText(m_ThreeIcon.iconRect_W,L"通知中心");
	DrawIconBottomText(m_FourIcon.iconRect_W,L"即时会话");
	UpdateDisplay();
	m_bShowCildIcon = TRUE;
	return TRUE;
}

BOOL CFloatDlg::OnlyShowMainIcon()
{
	CreateCompatibleMemDC(m_hWnd,m_MemDCSize.cx,m_MemDCSize.cy,m_MemDC);
	GraphDrawImage(
		m_HeadIcon.pImage, 
		m_HeadIcon.iIconWidth,
		m_HeadIcon.iIconHeight,
		m_HeadIcon.iconRect_W
		);
	GraphDrawImage(
		m_SitIcon.pImage,
		m_SitIcon.iIconWidth,
		m_SitIcon.iIconHeight
		,m_SitIcon.iconRect_W
		);
	UpdateDisplay();
	m_bShowCildIcon = FALSE;
	return TRUE;
}



void CFloatDlg::OnMove(int x, int y)
{

	
		CDialogEx::OnMove(x, y);
}


void CFloatDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{

	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int iFourIconRight_S, iHeadIconTop_S, iOneIconLeft_S;
	ICONREG iconReg;





	iFourIconRight_S = lpwndpos->x+ m_FourIcon.iconRect_W.right;
	iHeadIconTop_S = lpwndpos->y + m_HeadIcon.iconRect_W.top;
	iOneIconLeft_S = lpwndpos->x+ m_OneIcon.iconRect_W.left;

	if (iFourIconRight_S > iScreenWidth + WIDTH_OUTSCREEN)
	{
		POINT cursorPos;
		::GetCursorPos(&cursorPos);
		ScreenToClient(&cursorPos);

		CheckReg(cursorPos, &iconReg);
		TRACE("m_bWndHide = %d m_bMovePlaying = %d\n", m_bWndHide, m_bMovePlaying);
		if (!m_bWndHide&&!m_bMovePlaying)
		{
			lpwndpos->x = iScreenWidth + WIDTH_OUTSCREEN-m_FourIcon.iconRect_W.right;
			TRACE("lpwndpos->x = %d\n", lpwndpos->x);
		}


	}
	else if (iHeadIconTop_S < 0)
	{
		lpwndpos->y = -m_HeadIcon.iconRect_W.top;
	}
	else if (iOneIconLeft_S < 0)
	{
		lpwndpos->x = -m_OneIcon.iconRect_W.left;

	}

	CDialogEx::OnWindowPosChanging(lpwndpos);
	/*
	if (m_bShowTimeOver)
	{
	ShowTimeBeforeRightHide(2000);
	}*/
	TRACE("aaaaaa\n");

	// TODO: Add your message handler code here
}


void CFloatDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	TRACE("bbbbbbb\n");
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
}
