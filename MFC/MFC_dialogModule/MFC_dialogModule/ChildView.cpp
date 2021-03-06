
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC_dialogModule.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_str = _T("세종대학교");
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
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

	dc.TextOutW(100, 100, m_str);
}

#include "CMyDlg.h"

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMyDlg dlg;
	
	dlg.m_editstr = m_str;
	
	if (dlg.DoModal() == IDOK)
	{
		m_str = dlg.m_editstr;
		Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_dlg.Create(IDD_DIALOG1);
	m_dlg.ShowWindow(true);

	return 0;
}
