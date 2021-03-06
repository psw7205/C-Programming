
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "ChildView.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_pt.x = 100;
	m_pt.y = 100;
	m_flag = 0;
	m_dx = 10;
	m_dy = 10;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
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
	CBrush b(RGB(0, 0, 0));
	dc.SelectObject(b);
	GetClientRect(&m_client);

	dc.Rectangle(m_pt.x, m_pt.y, m_pt.x + 100, m_pt.y + 100);
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 1, NULL);

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0 && m_flag == 1)
	{
		m_pt.x += m_dx;
		m_pt.y += m_dy;

		if (m_pt.x + 100 > m_client.right)
		{
			m_pt.x = m_client.right - 100;
			m_dx = -m_dx;
		}
		
		if (m_pt.x < m_client.left)
		{
			m_pt.x = m_client.left;
			m_dx = -m_dx;
		}

		if (m_pt.y + 100 > m_client.bottom)
		{
			m_pt.y = m_client.bottom - 100;
			m_dy = -m_dy;
		}

		if (m_pt.y < m_client.top)
		{
			m_pt.y = m_client.top;
			m_dy = -m_dy;
		}
		
		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_flag = 1;

	CPoint tmp = m_pt;

	tmp.x += 50;
	tmp.y += 50;

	point = tmp - point;

	double r = sqrt(point.x*point.x + point.y*point.y);

	point.x = point.x / r * 10;
	point.y = point.y / r * 10;

	m_dx = -point.x;
	m_dy = -point.y;
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_flag = 1;

	switch (nChar)
	{
	case VK_UP:
		m_dx = 0; m_dy = -10;
		break;
	case VK_DOWN:
		m_dx = 0; m_dy = 10;
		break;
	case VK_LEFT:
		m_dx = -10; m_dy = 0;
		break;
	case VK_RIGHT:
		m_dx = 10; m_dy = 0;
		break;
	default:
		break;
	}

	Invalidate();


	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
