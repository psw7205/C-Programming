
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication7.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	rect1.SetRect(100, 50, 800, 300);
	rect2.SetRect(100, 350, 800, 600);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
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

	dc.TextOutW(0, 0, _T("16013093 박상우"));

	dc.DrawText(m_str[0], rect1, DT_LEFT);
	dc.DrawText(m_str[1], rect2, DT_LEFT);
	
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(rect1);
	dc.Rectangle(rect2);

	CPen p(PS_SOLID, 1,RGB(0, 255, 255));
	dc.SelectObject(p);
	

	if (m_flag == 0)
	{
		dc.Rectangle(rect1);
	}

	if (m_flag == 1) 
	{
		dc.Rectangle(rect2);
	}


}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);

	if (rect1.PtInRect(point))
	{
		m_flag = 0;
	}
	else if (rect2.PtInRect(point))
	{
		m_flag = 1;
	}
	else
	{
		m_flag = 3;
	}

	Invalidate();
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_flag == 0)
	{
		if (nChar == VK_BACK)
		{
			m_str[0].Delete(m_str[0].GetLength() - 1, 1);
		}
		else if (nChar == VK_RETURN)
		{
			m_str[0] += _T("\r\n");
		}
		else
			m_str[0] += TCHAR(nChar);
	}

	if (m_flag == 1)
	{
		if (nChar == VK_BACK)
		{
			m_str[1].Delete(m_str[0].GetLength() - 1, 1);
		}
		else if (nChar == VK_RETURN)
		{
			m_str[1] += _T("\r\n");
		}
		else
			m_str[1] += TCHAR(nChar);
	}

	Invalidate();

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
