
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplicationEX1.h"
#include "ChildView.h"
#include <cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_flag = CIRCLE;
	dt = 0;
	r = 50;
	color = RGB(0, 0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BUTTON_CIRCLE, &CChildView::OnButtonCircle)
	ON_COMMAND(ID_BUTTON_DIV, &CChildView::OnButtonDiv)
	ON_COMMAND(ID_BUTTON_MERGE, &CChildView::OnButtonMerge)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CIRCLE, &CChildView::OnUpdateButtonCircle)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DIV, &CChildView::OnUpdateButtonDiv)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MERGE, &CChildView::OnUpdateButtonMerge)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
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

	CBrush brush(RGB(100, 150, 200));
	dc.SelectObject(brush);

	POSITION pos = m_rect.GetHeadPosition();

	while (pos)
	{
		CPoint st = m_rect.GetAt(pos).TopLeft();
		CPoint ed = m_rect.GetAt(pos).BottomRight();

		dc.Ellipse(st.x, st.y, ed.x, ed.y);
		
		m_rect.GetNext(pos);
	}
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_flag == CIRCLE)
	{
		m_rect.AddTail(CRect());
		m_rect.GetTail().SetRect(point.x - r, point.y - r, point.x + r, point.y + r);
		Invalidate();
	}
	
	if (m_flag == MERGE)
	{
		SetCapture();

		color = RGB(255, 0, 0);

		POSITION pos = m_rect.GetHeadPosition();

		while (pos)
		{
			if (m_rect.GetAt(pos).PtInRect(point))
			{
				CPoint st = m_rect.GetAt(pos).TopLeft();
				CPoint ed = m_rect.GetAt(pos).BottomRight();

				m_rect.GetAt(pos).SetRect(st, ed);
				m_pos = pos;
				m_mergeFlag = 1;
			}
			m_rect.GetNext(pos);
		}
	}

	if (m_flag == DIV)
	{
		POSITION pos = m_rect.GetHeadPosition();

		while (pos)
		{
			if (m_rect.GetAt(pos).PtInRect(point))
			{
				CPoint st = m_rect.GetAt(pos).TopLeft();
				CPoint ed = m_rect.GetAt(pos).BottomRight();
				CPoint cp = m_rect.GetAt(pos).CenterPoint();

				double r = (ed.x - st.x) / 4;

				m_rect.GetAt(pos).SetRect(cp.x-2*r,cp.y-r,cp.x,cp.y+r);
				m_rect.InsertAfter(pos, CRect(cp.x, cp.y - r, cp.x + 2 * r, cp.y + r));
				m_rect.GetNext(pos);
			}
			m_rect.GetNext(pos);
		}
		Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnButtonCircle()
{
	m_flag = CIRCLE;
}


void CChildView::OnButtonDiv()
{
	m_flag = DIV;
}


void CChildView::OnButtonMerge()
{
	m_flag = MERGE;
}


void CChildView::OnUpdateButtonCircle(CCmdUI *pCmdUI)
{
	if (m_flag == CIRCLE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateButtonDiv(CCmdUI *pCmdUI)
{
	if (m_flag == DIV)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateButtonMerge(CCmdUI *pCmdUI)
{
	if (m_flag == MERGE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_flag == MERGE && nFlags & MK_LBUTTON && m_mergeFlag )
	{
		CPoint st;
		CPoint ed;
		CPoint tmp = point - m_rect.GetAt(m_pos).CenterPoint();
		st = m_rect.GetAt(m_pos).TopLeft() + tmp;
		ed = m_rect.GetAt(m_pos).BottomRight() + tmp;

		m_rect.GetAt(m_pos).SetRect(st, ed);
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_flag == MERGE && m_mergeFlag)
	{
		color = RGB(0, 0, 0);

		m_mergeFlag = 0;

		CPoint st = m_rect.GetAt(m_pos).TopLeft();
		CPoint ed = m_rect.GetAt(m_pos).BottomRight();

		m_rect.GetAt(m_pos).SetRect(st, ed);

		POSITION pos = m_rect.GetHeadPosition();

		dt = 20;

		while (pos)
		{
			if (m_rect.GetAt(pos).PtInRect(point) && pos != m_pos)
			{
				if (m_rect.GetAt(m_pos).Height() > m_rect.GetAt(pos).Height())
				{
					CRect tmp = m_rect.GetAt(m_pos);
					m_rect.GetAt(pos).SetRect(tmp.TopLeft(), tmp.BottomRight());
				}

				CPoint st = m_rect.GetAt(pos).TopLeft();
				CPoint ed = m_rect.GetAt(pos).BottomRight();

				m_rect.GetAt(pos).SetRect(st.x - dt, st.y - dt, ed.x + dt, ed.y + dt);
				Invalidate();
				m_rect.RemoveAt(m_pos);
				break;
			}

			m_rect.GetNext(pos);
		}
		Invalidate();
	}

	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}
