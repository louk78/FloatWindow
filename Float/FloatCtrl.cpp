#include "stdafx.h"
#include "FloatCtrl.h"


BEGIN_MESSAGE_MAP(CFloatCtrl,CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



CFloatCtrl::CFloatCtrl()
{

}

CFloatCtrl::~CFloatCtrl()
{

}


BOOL CFloatCtrl::Create(RECT rect,HWND hWndParent)
{
	DWORD dwStyle;
	UINT uID = 0;

	dwStyle = WS_VISIBLE;
	BOOL bRet = CreateEx(
		NULL,
		AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW),
		NULL,
		dwStyle,
		rect.left,
		rect.top,
		rect.right-rect.left,
		rect.bottom-rect.top,
		NULL,
		(HMENU)uID
		);


	return bRet;
}


BOOL CFloatCtrl::UpdateDisplay(Image *image,int imageWidth,int imageHeight,int transparent)
{
	if(this->m_hWnd==NULL)return FALSE;
	HDC ClientDC;
	HBITMAP hBitmap;
	RECT rect;
	BOOL bRet = FALSE;

	ClientDC = ::GetDC(this->m_hWnd);
	m_pMemDC = CreateCompatibleDC(ClientDC);
	hBitmap  = CreateCompatibleBitmap(ClientDC,imageWidth,imageHeight);
	SelectObject(m_pMemDC,hBitmap);

	if(transparent<0||transparent>100)transparent = 100;
	m_Blend.SourceConstantAlpha = (int)(transparent*2.55);

	::GetWindowRect(this->m_hWnd,&rect);

	Graphics graph(m_pMemDC);
	Point ptArray[]={
		Point(0,0),
		Point(imageWidth,0),
		Point(0,imageHeight)
	};

	graph.DrawImage(image,ptArray,3);



	DWORD dwExStyle = GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if((dwExStyle&WS_EX_LAYERED)!=WS_EX_LAYERED)
		dwExStyle = dwExStyle^WS_EX_LAYERED;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle);

	POINT dstPoint={800,800},srcPoint={0,0};
	SIZE dstSize={imageWidth,imageHeight};
	bRet = ::UpdateLayeredWindow(
		NULL,
		ClientDC,
		&dstPoint,
		&dstSize,
		m_pMemDC,
		&srcPoint,
		0,
		&m_Blend,
		2
		);
	DWORD dwError;
	dwError = GetLastError();
	graph.ReleaseHDC(m_pMemDC);
	::ReleaseDC(m_hWnd,ClientDC);
	DeleteObject(hBitmap);
	DeleteObject(m_pMemDC);

	m_pMemDC = NULL;


	return bRet;
}



void CFloatCtrl::OnPaint()
{
	CPaintDC dc(this);

	//dc.TextOut(0,0,TEXT("helloworld"),_tcslen(TEXT("helloworld")));
}


int CFloatCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_Blend.BlendOp = 0;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = 1;
	m_Blend.SourceConstantAlpha = 255;
	DWORD style;
	return 0;
}
