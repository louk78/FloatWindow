



class CFloatCtrl :public CWnd
{
public:
	CFloatCtrl();
	~CFloatCtrl();
public:
	virtual BOOL Create(RECT rect,HWND hWndParent);
	virtual BOOL UpdateDisplay(Image *image,int imageWidth,int imageHeight,int transparent=100);
public:
	HDC m_pMemDC;
	BLENDFUNCTION m_Blend;




DECLARE_MESSAGE_MAP();
afx_msg void OnPaint();
afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};