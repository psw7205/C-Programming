
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication15.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_cnt = 1;
	m_t = 0;
	m_a = 5;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
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

	POSITION pos = m_circle.GetHeadPosition();

	while (pos)
	{
		m_circle.GetNext(pos).draw(&dc);
	}
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE)
	{

		CRect r;
		GetClientRect(&r);

		m_circle.AddTail(CMyCircle());
		m_cnt++;

 		POSITION pos = m_circle.GetHeadPosition();

		while (pos)
		{
			m_circle.GetNext(pos).m_v = 0;
		}

		int p = r.Width() / m_cnt;
		pos = m_circle.GetHeadPosition();

 		while(pos)
		{
			m_circle.GetAt(pos).m_center.x = p;
			m_circle.GetNext(pos).m_center.y = 100;
			p += r.Width() / m_cnt;
		}

		m_t = 0;
		Invalidate();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 40, NULL);

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	POSITION pos = m_circle.GetHeadPosition();
	CRect r;
	GetClientRect(&r);

	m_t++;

	int cnt = 0;

	while (pos)
	{
		if (m_t < 5 + cnt)
		{
			m_circle.GetAt(pos).m_v += m_a;
			m_circle.GetAt(pos).m_center.y += m_circle.GetAt(pos).m_v;

			if (m_circle.GetAt(pos).m_center.y + 30 > r.bottom)
			{
				m_circle.GetAt(pos).m_center.y = r.bottom - 30;
				m_circle.GetAt(pos).m_v = -m_circle.GetAt(pos).m_v * 0.8;
			}
			break;
		}
		else
		{
			m_circle.GetAt(pos).m_v += m_a;
			m_circle.GetAt(pos).m_center.y += m_circle.GetAt(pos).m_v;

			if (m_circle.GetAt(pos).m_center.y + 30 > r.bottom)
			{
				m_circle.GetAt(pos).m_center.y = r.bottom - 30;
				m_circle.GetAt(pos).m_v = -m_circle.GetAt(pos).m_v * 0.8;
			}
			m_circle.GetNext(pos);
		}
		cnt += 1;
	}

	Invalidate();

	CWnd::OnTimer(nIDEvent);
}
