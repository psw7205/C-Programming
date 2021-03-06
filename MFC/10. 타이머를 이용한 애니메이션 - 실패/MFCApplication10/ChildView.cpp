
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication10.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_rect.SetRect(100, 100, 400, 400);
	m_n = 15;
	m_cnt = 0;
	m_play = 5;
	m_flag = 0;


	for (int i = 0; i < m_n*4; i++)
	{
		m_circle.AddTail(CMyCircle());
	}

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_BUTTON_PAUSE, &CChildView::OnButtonPause)
	ON_COMMAND(ID_BUTTON_START, &CChildView::OnButtonStart)
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
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);
	dc.Rectangle(m_rect);

	POSITION pos = m_circle.GetHeadPosition();

	int i = 0, j = 0, k = 0, m = 0;
	m_cnt = 1;

	while (pos)
	{
		m_circle.GetAt(pos).m_r = 1200 / (m_circle.GetSize()*2-2);

		if (m_cnt <= m_n)
		{
			m_circle.GetAt(pos).setCenter(100 + i, 100);
			i += m_circle.GetAt(pos).m_r * 2;
			m_circle.GetNext(pos).draw(&dc);
		}
		else if (m_cnt <= m_n * 2)
		{
			m_circle.GetAt(pos).setCenter(100 + i, 100 + j);
			j += m_circle.GetAt(pos).m_r * 2;
			m_circle.GetNext(pos).draw(&dc);
		}
		else if (m_cnt <= m_n * 3)
		{
			m_circle.GetAt(pos).setCenter(100 + i - k, 100 + j);
			k += m_circle.GetAt(pos).m_r * 2;
			m_circle.GetNext(pos).draw(&dc);
		}
		else
		{
			m_circle.GetAt(pos).setCenter(100 + i - k, 100 + j - m);
			m += m_circle.GetAt(pos).m_r * 2;
			m_circle.GetNext(pos).draw(&dc);
		}
		m_cnt++;
	}
}

void CChildView::OnButtonPause()
{
	m_flag = 0;
}


void CChildView::OnButtonStart()
{
	m_flag = 1;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TRACE(_T("%d"), nChar);

	if (nChar == VK_RIGHT)
	{
		m_n++;
		m_circle.AddTail(CMyCircle());
		m_circle.AddTail(CMyCircle());
		m_circle.AddTail(CMyCircle());
		m_circle.AddTail(CMyCircle());
	}

	if (nChar == VK_LEFT)
	{
		if (!m_circle.IsEmpty() && m_n > 2)
		{
			m_n--;
			m_circle.RemoveTail();
			m_circle.RemoveTail();
			m_circle.RemoveTail();
			m_circle.RemoveTail();
		}
	}

	Invalidate();

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 1000, NULL);


	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0 && m_flag == 1)
	{
		m_play++;
	}

	CWnd::OnTimer(nIDEvent);
}
