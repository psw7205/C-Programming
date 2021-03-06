
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplicationEX2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	str = _T("VISUAL C++ FINAL");
	color = RGB(255, 0, 0);
	dlg.editRed = 255;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	int size = rect.Height()*(double)rect.Width() / 1000;

	CFont font;
	font.CreatePointFont(size, _T("Arial"));
	dc.SelectObject(font);

	dc.SetTextColor(color);

	dc.DrawTextW(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	dlg.editStr = str;
	dlg.DoModal();
	str = dlg.editStr;
	color = RGB(dlg.editRed, dlg.editGreen, dlg.editBlue);
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}
